#include <ABuildPolicy.hpp>

namespace ft
{
	

	ABuildPolicy::ABuildPolicy()
	{/* Illegal */}

	ABuildPolicy::~ABuildPolicy()
	{}

	ABuildPolicy::ABuildPolicy(const ABuildPolicy &ref)
	{ (void)ref; /* Illegal */}

	ABuildPolicy::ABuildPolicy(IFileManager *mngr, ITimeMachine *machine) : _fmngr(mngr), _t_machine(machine)
	{}
	ABuildPolicy &ABuildPolicy::operator=(const ABuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IHeader *ABuildPolicy::buildHeader(int ret_code, std::string descr, IBody *body)
	{
		//std::stringstream ss;
		IHeader *res = new Header(response);

		//ss << body->size();
		res->setCodeDescription(descr);
		res->setResponseCode(ret_code);
		res->setHTTPV("HTTP/1.1");
		res->setHeader(h_content_length, ft::to_string(body->size()));
		res->setHeader(h_date, _t_machine->getTimestamp());
//		res->setHeader(h_connec, "keep-alive");
		res->setHeader(h_content_type, body->getContentType());
		res->setHeader(h_server, DEFAULT_SERVER_HEADER);

		//std::string type =
		return res;
	}
	int ABuildPolicy::findIndexFile(std::list<std::string> &priority)
	{
		(void)priority;
		int fd = 0;
		throw ft::runtime_error("Not implemented");
		return fd;
	}

	TextBody *ABuildPolicy::buildTextBody(std::string const &filename)
	{
		//int					fd;
		//unsigned int		size;
		//char				*buff;
		//int					ret;
		TextBody *res;
		std::stringstream ss;
		std::string str;
		std::ifstream fin(_fmngr->getFullPath(filename), std::ios::binary);
#ifdef DEBUG
		std::cout << "BODY FROM FILE: [" << filename << "]\n";
#endif

		if (!fin.good())
			throw ft::runtime_error("Cannot open file: " + filename);

		//fd = _fmngr->getFd(filename, 0);
		//size = _fmngr->getFileSize(filename);

		ss << fin.rdbuf();
		str = ss.str();

#ifdef DEBUG
		std::cout << "SIZE:" << str.size() << "\n";
#endif
		//buff = new char[size + 1];
		//ret = read(fd, buff, size);
		//buff[ret] = 0;

		res = new TextBody(str);
		//delete[] buff;
		fin.close();
		return (res);
	}

	FileBody *ABuildPolicy::buildFileBody(std::string const &filename)
	{
#ifdef DEBUG
		std::cout << "BUILDER: BUILD FILE BODY [" << filename << "]\n";
#endif
		FileBody *res = new FileBody(_fmngr->getFileSize(filename), _fmngr->getFd(filename, 0), _fmngr->getFullPath(filename));
#ifdef DEBUG
		std::cout << "BUILDER: BUILDING COMPLETED [" << res->size() << "] [" << res->getFd() << "] [" << _fmngr->getFullPath(filename) << "]\n";
#endif
		return (res);
	}

	IBody *ABuildPolicy::bodyFromFile(std::string const &filename)
	{
		std::string type;
		IBody *res;

		type = _fmngr->getContentType(filename);
#ifdef DEBUG
		std::cout << "BUILDER: GOT FILE TYPE [" << type << "]\n";
#endif
		if (type.find("text") != std::string::npos)
			res = buildTextBody(filename);
		else
			res = buildFileBody(filename);
		res->setContentType(type);
		return (res);
	}

	IResponse *ABuildPolicy::buildFromFile(std::string const &filename)
	{
		IResponse *res;
		IBody *body;
		IHeader *header;

#ifdef DEBUG
		std::cout << "BUILDER: BUILD FROM FILE: [" << filename << "]\n";
#endif

		body = bodyFromFile(filename);
		header = buildHeader(200, "OK", body);

		//res = new TextResponse(header->to_string() + body->to_string());
		res = new TextResponse(header, body);
		//delete header;
		//delete body;
		return (res);
	}

	IResponse *ABuildPolicy::buildAutoindex(IRequest *request)
	{
		(void)request;
		throw ft::runtime_error("Not implemented");
		return (0);
	}

	IResponse *ABuildPolicy::buildFromDir(IRequest *request)
	{
		(void)request; // FIXME
		//_fmngr->setRoot(request->getURI());
		if (_fmngr->isFileExisting("index.html"))
		{
#ifdef DEBUG
			std::cout << "FILE EXISTS\n";
#endif
			return buildFromFile("index.html");
		}
		return _e_pager.getErrorPage(404);
	}

	IResponse	*ABuildPolicy::buildErrorPage(int code)
	{
		return (_e_pager.getErrorPage(code));
	}
} // namespace ft