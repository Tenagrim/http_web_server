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

	int					ResponseBuilder::findIndexFile(std::list<std::string> &priority)
	{
		(void)priority;
		int fd = 0;
		return fd;
	}

	IResponse			*ResponseBuilder::buildFromDir(IRequest *request)
	{

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