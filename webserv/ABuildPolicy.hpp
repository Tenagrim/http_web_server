#pragma once

#include <IFileManager.hpp>
#include <ITimeMachine.hpp>

#include <FakeTimeMachine.hpp>
#include <IRequest.hpp>

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

#include <defines.hpp>
#include <list>

namespace ft
{
	class ABuildPolicy
	{
	protected:
		IFileManager *_fmngr;
		ErrorPager _e_pager;
		ITimeMachine *_t_machine;

		int findIndexFile(std::list<std::string> &priority);

		IResponse *buildFromDir(IRequest *request);
		IResponse *buildFromFile(IRequest *request);
		IResponse *buildFromFile(std::string const &filename);
		IResponse *buildAutoindex(IRequest *request);

		IHeader *buildHeader(IBody *body);
		IHeader *buildHeader(int ret_code, std::string descr, IBody *body);
		IBody *bodyFromFile(std::string const &filename);

		TextBody *buildTextBody(std::string const &filename);
		FileBody *buildFileBody(std::string const &filename);

		ABuildPolicy();
		ABuildPolicy(const ABuildPolicy &ref);

	public:
		ABuildPolicy(IFileManager *mngr, ITimeMachine *machine);
		virtual ~ABuildPolicy();
		ABuildPolicy &operator=(const ABuildPolicy &ref);
		virtual IResponse *buildResponse(IRequest *request) = 0;
		IResponse *buildErrorPage(int code);
	};

} // namespace ft
