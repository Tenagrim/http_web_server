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
		return res;
	}
	int					ResponseBuilder::findIndexFile(std::list<std::string> &priority)
	{
		(void)priority;
		int fd = 0;
		throw std::runtime_error("Not implemented");
		return fd;
	}

	IBody				*ResponseBuilder::bodyFromFile(std::string const &filename)
	{
		int				fd;
		unsigned int	size;
		char			*buff;
		int				ret;
		IBody			*res;
		
		fd = _fmngr->getFd(filename, 0);
		size = _fmngr->getFileSize(filename);
		buff = new char[size + 1];
		ret = read(fd, buff, size);
		buff[ret] = 0;
		res = new TextBody(std::string(buff, size));
		delete[] buff;
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
		IResponse	*res;

		(void)request;  // FIXME
		//_fmngr->setRoot(request->getURI());
		if (_fmngr->isFileExisting("index.html"))
		{
			std::cout << "FILE EXISTS\n";
			IBody		*body = bodyFromFile("index.html");
			IHeader		*header = buildHeader(200, "OK", body);
			res = new TextResponse(header->to_string() + body->to_string());
			delete header;
			delete body;
			return (res);
		}
		throw std::runtime_error("BUILD FROM DIR NOT FULLY IPLEENTED");
		return(0);
	}

	IResponse			*ResponseBuilder::buildResponse(IRequest	*request)
	{

		_fmngr->setRoot("resources");
		
		std::cout << "URI ::::::::::: ["<< request->getURI() <<"]\n";

		if (_fmngr->isADirectory(request->getURI()))
			return (buildFromDir(request));

		if (_fmngr->isFileExisting(request->getURI()))
			std::cout << "FILE EXISTS\n";
		else
			std::cout << "FILE NOT EXISTS\n";
		

		return new TextResponse(std::string(webpage_header) + std::string (webpage_body));
	}
}