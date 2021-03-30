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
	
	IResponse			*ResponseBuilder::buildResponse(IRequest	*request)
	{
		(void)request;
		(void)_fmngr;
		return new TextResponse(std::string(webpage_header) + std::string (webpage_body));
	}
}