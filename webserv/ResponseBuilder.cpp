#include <ResponseBuilder.hpp>
namespace ft
{
	#pragma region Copilen
	ResponseBuilder::ResponseBuilder()
	{/*  Illegal */}
	ResponseBuilder::ResponseBuilder(IFileManager *mngr) : _fmngr(mngr)
	{}

	ResponseBuilder::~ResponseBuilder()
	{}

	ResponseBuilder::ResponseBuilder(const ResponseBuilder &ref)
	{
		(void)ref;
		throw std::runtime_error("Not implemented");
	}

	ResponseBuilder &ResponseBuilder::operator=(const ResponseBuilder &ref)
	{
		(void)ref;
		throw std::runtime_error("Not implemented");
		return (*this);
	}

	#pragma endregion

	IHeader				*ResponseBuilder::buildHeader(int ret_code, std::string descr, IBody *body)
	{
		std::stringstream ss;
		IHeader *res = new Header(response);
		
		ss << body->size();
		res->setCodeDescription(descr);
		res->setResponseCode(ret_code);
		res->setHTTPV("HTTP/1.1");
		res->setHeader(h_content_length,  ss.str());
		//std::string type = 
		return res;
	}
	int					ResponseBuilder::findIndexFile(std::list<std::string> &priority)
	{
		(void)priority;
		int fd = 0;
		throw std::runtime_error("Not implemented");
		return fd;
	}


	TextBody			*ResponseBuilder::buildTextBody(std::string const &filename)
	{
		//int					fd;
		//unsigned int		size;
		//char				*buff;
		//int					ret;
		TextBody			*res;
		std::stringstream	ss;
		std::string			str;
		std::ifstream		fin(_fmngr->getFullPath(filename), std::ios::binary);
		#ifdef DEBUG
			std::cout << "BODY FROM FILE: ["<< filename <<"]\n";
		#endif

		if (!fin.good())
			throw std::runtime_error("Cannot open file: " + filename);
		
		//fd = _fmngr->getFd(filename, 0);
		//size = _fmngr->getFileSize(filename);
		
		ss << fin.rdbuf();
		str = ss.str();

		#ifdef DEBUG
			std::cout << "SIZE:"<< str.size() <<"\n";
		#endif
		//buff = new char[size + 1];
		//ret = read(fd, buff, size);
		//buff[ret] = 0;

		res = new TextBody(str);
		//delete[] buff;
		fin.close();
		return (res);
	}

	FileBody			*ResponseBuilder::buildFileBody(std::string const &filename)
	{
		#ifdef DEBUG
			std::cout << "BUILDER: BUILD FILE BODY ["<< filename <<"]\n";
		#endif	
		FileBody *res = new FileBody(_fmngr->getFileSize(filename), _fmngr->getFd(filename), _fmngr->getFullPath(filename));
		#ifdef DEBUG
			std::cout << "BUILDER: BUILDING COMPLETED ["<<res->size() <<"] ["<< res->getFd() <<"] ["<< _fmngr->getFullPath(filename) <<"]\n";
		#endif
		return (res);
	}

	IBody				*ResponseBuilder::bodyFromFile(std::string const &filename)
	{
		std::string type;

		type = _fmngr->getContentType(filename);
		#ifdef DEBUG
			std::cout << "BUILDER: GOT FILE TYPE [" << type << "]\n";
		#endif
		if (type.find("text") != std::string::npos)
			return (buildTextBody(filename));
		else
			return (buildFileBody(filename));
	}

	IResponse			*ResponseBuilder::buildFromFile(std::string const &filename)
	{
		IResponse		*res;
		IBody			*body;
		IHeader			*header;
		
		#ifdef DEBUG
			std::cout << "BUILDER: BUILD FROM FILE: ["<< filename <<"]\n";
		#endif
		
		body = bodyFromFile(filename);
		header = buildHeader(200, "OK", body);
		
		//res = new TextResponse(header->to_string() + body->to_string());
		res = new TextResponse(header, body);
		//delete header;
		//delete body;
		return (res);
	}

	IResponse			*ResponseBuilder::buildAutoindex(IRequest *request)
	{
		(void)request;
		throw std::runtime_error("Not implemented");
		return (0);
	}

	IResponse			*ResponseBuilder::buildFromDir(IRequest *request)
	{
		(void)request;  // FIXME
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

	IResponse			*ResponseBuilder::buildResponse(IRequest	*request)
	{
		_fmngr->setRoot("resources/sites/particles");   // HARDCODED SERVER ROOT
		//_fmngr->setRoot("resources/sites/trump");   // HARDCODED SERVER ROOT
		IResponse	*res = 0;
		#ifdef DEBUG
			std::cout << "URI ::::::::::: ["<< request->getURI() <<"]\n";
		#endif

		if (_fmngr->isADirectory(request->getURI()))
			return (buildFromDir(request));

		if (_fmngr->isFileExisting(request->getURI()))
		{
			#ifdef DEBUG
			std::cout << "FILE EXISTS\n";
			#endif
			res = buildFromFile(request->getURI());

			return res;
		}
			#ifdef DEBUG
				std::cout << "FILE NOT EXISTS\n";
			#endif
		return (_e_pager.getErrorPage(404));
	}
}