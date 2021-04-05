#pragma once
#include <IServer.hpp>
#include <IFileManager.hpp>
#include <ITimeMachine.hpp>
#include <ILogger.hpp>
#include <RequestReceiver.hpp>
#include <IResponseSender.hpp>
#include <IResponseBuilder.hpp>
#include <ResponseBuilder.hpp>
#include <DispatcherEventArgs.hpp>
#include <Request.hpp>

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

#include <string>
#include <exception>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

#include <ResponseSender.hpp>
#include <ResponseBuilder.hpp>

#include <webserv.hpp>
#include <defines.hpp>
#include <runtime_error.hpp>
//#include <He>
namespace ft
{
	class Dispatcher;
}
#include <Dispatcher.hpp>
namespace ft
{
	class Server
	{
	private:
		typedef std::map<int, RequestReceiver *>	listener_map;
		unsigned int					_id;
		unsigned int					_flags;
		struct sockaddr_in				serv_addr;
		struct hostent					*server;
		std::string						hostname;

		Dispatcher						*_dispatcher;

		listener_map					_listener_map;
		std::list<RequestReceiver *>	_list_to_start;

		IFileManager					*_f_manager;
		ILogger							*_logger;
		ITimeMachine					*_t_machine;
		IResponseSender					*_resp_sender;
		IResponseBuilder				*_resp_builder;
		
		void							close_sockets(void);
		void							listenerEvent(Dispatcher_event_args &args);
		void							clientEvent(Dispatcher_event_args &args);
		void							clientEventRead(Dispatcher_event_args &args);
		void							clientEventWrite(Dispatcher_event_args &args);
		Server();
		Server(const Server &ref);
	public:
		enum server_flags
		{
			is_running = 1
		};

		Server(IResponseBuilder *bulder);
		virtual ~Server();

		Server							&operator=(const Server &ref);
		bool							hasFlag(unsigned int flag);
		int								setFlag(unsigned int flag);
		int								switchFlag(unsigned int flag);
		IRequest						*getRequest(void);
		int								sendResponce(const IResponse &resp);
		int								acceptConnection(int sock);
		int								processConnection();
		RequestReceiver					*getListener(int sock);

		void							gotEvent(Dispatcher_event_args args);

		void							addListener(int port);

		void							start(void);
		void							stop(void);
		void							abort(void);
	};
}