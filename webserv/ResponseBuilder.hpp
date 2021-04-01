#pragma once
#include <IResponseBuilder.hpp>
#include <IFileManager.hpp>
#include <ITimeMachine.hpp>

#include <FakeTimeMachine.hpp>

#include <TextResponse.hpp>
#include <TextBody.hpp>
#include <webserv.hpp>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <Header.hpp>
#include <stdlib.h>
#include <FileBody.hpp>
#include <ErrorPager.hpp>

#include <list>

#include <defines.hpp>

namespace ft
{
	class ResponseBuilder : public IResponseBuilder
	{
	private:
		IFileManager		*_fmngr;
		ErrorPager			_e_pager;
		//static ITimeMachine const	&_t_machine;
		ITimeMachine		*_t_machine;
		
		int					findIndexFile(std::list<std::string> &priority);

		IResponse			*buildFromDir(IRequest *request);
		IResponse			*buildFromFile(IRequest *request);
		IResponse			*buildFromFile(std::string const &filename);
		IResponse			*buildAutoindex(IRequest *request);
		IResponse			*buildErrorPage(int code);
		

		IHeader				*buildHeader(IBody *body);
		IHeader				*buildHeader(int ret_code, std::string descr, IBody *body);
		IBody				*bodyFromFile(std::string const &filename);

		TextBody			*buildTextBody(std::string const &filename);
		FileBody			*buildFileBody(std::string const &filename);

		ResponseBuilder(const ResponseBuilder &ref);
		ResponseBuilder();
	public:
		ResponseBuilder(IFileManager	*mngr);
		virtual ~ResponseBuilder();
		ResponseBuilder		&operator=(const ResponseBuilder &ref);


		IResponse			*buildResponse(IRequest	*request);
	};

}
