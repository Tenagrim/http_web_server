#pragma once
#include <IResponseBuilder.hpp>
#include <IFileManager.hpp>

#include <TextResponse.hpp>
#include <webserv.hpp>
#include <iostream>

#include <list>

#define ERROR_PAGES_DIR nginx-error-pages

namespace ft
{
	class ResponseBuilder : public IResponseBuilder
	{
	private:
		IFileManager		*_fmngr;
		ResponseBuilder();
		//bool				isFile(std::string const & uri);
		int					findIndexFile(std::list<std::string> &priority);
		IResponse			*buildFromDir(IRequest *request);

		IResponse			*buildErrorPage(int code);
		IHeader				*buildHeader(IBody *body);
	public:
		ResponseBuilder(IFileManager	*mngr);
		virtual ~ResponseBuilder();
		ResponseBuilder(const ResponseBuilder &ref);
		ResponseBuilder		&operator=(const ResponseBuilder &ref);


		IResponse			*buildResponse(IRequest	*request);
	};

}
