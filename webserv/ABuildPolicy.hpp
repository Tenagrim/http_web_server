#pragma once

#include <IFileManager.hpp>
#include <ITimeMachine.hpp>

#include <FakeTimeMachine.hpp>
#include <IRequest.hpp>
#include <FileManager.hpp>

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
#include <ServerInit.hpp>

#include <defines.hpp>
#include <list>
#include <runtime_error.hpp>

#include <Utils.hpp>

namespace ft
{
	class ABuildPolicy
	{
	protected:
		FileManager		_fmngr;
		ErrorPager		_e_pager;
		ITimeMachine	*_t_machine;
		ServerInit		*config;

		int findIndexFile(std::list<std::string> &priority);

		IResponse *buildFromDir(IRequest *request, LocationInit *location);
		IResponse *buildFromFile(IRequest *request, LocationInit *location);
		IResponse *buildFromFile(std::string const &filename);
		IResponse *buildAutoindex(IRequest *request);

		IHeader *buildHeader(IBody *body);
		IHeader *buildHeader(int ret_code, std::string descr, IBody *body);
		IBody *bodyFromFile(std::string const &filename);

		TextBody *buildTextBody(std::string const &filename);
		FileBody *buildFileBody(std::string const &filename);

		ABuildPolicy(const ABuildPolicy &ref);

	public:
		ABuildPolicy();
		virtual ~ABuildPolicy();
		ABuildPolicy &operator=(const ABuildPolicy &ref);
		virtual IResponse *buildResponse(IRequest *request) = 0;
		IResponse *buildErrorPage(int code);

		ServerInit *getConfig() const;
		void setConfig(ServerInit *config);
		LocationInit *getCorrectLocation(IRequest *request, ServerInit *server);
		LocationInit *getCorrectLocation(std::string const &URI, ServerInit *server);
		void applyConfig(ServerInit *server);
		LocationInit *getLocationFile(IRequest *request, ServerInit *server);
		bool ifCorrectMethod(IRequest *request, LocationInit* location);

	};

} // namespace ft
