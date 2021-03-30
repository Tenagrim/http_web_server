#pragma once
#include <IResponseBuilder.hpp>
#include <IFileManager.hpp>

#include <TextResponse.hpp>
#include <TextBody.hpp>
#include <webserv.hpp>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <Header.hpp>
#include <stdlib.h>

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
		IResponse			*buildFromFile(IRequest *request);
		IResponse			*buildFromFile(std::string const &filename);
		IResponse			*buildAutoindex(IRequest *request);
		IResponse			*buildErrorPage(int code);
		

		IHeader				*buildHeader(IBody *body);
		IHeader				*buildHeader(int ret_code, std::string descr, IBody *body);
		IBody				*bodyFromFile(std::string const &filename);

	public:
		ResponseBuilder(IFileManager	*mngr);
		virtual ~ResponseBuilder();
		ResponseBuilder(const ResponseBuilder &ref);
		ResponseBuilder		&operator=(const ResponseBuilder &ref);


		IResponse			*buildResponse(IRequest	*request);
	};

}
