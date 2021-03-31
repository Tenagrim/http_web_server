#pragma once
#include <IServer.hpp>
#include <IFileManager.hpp>
#include <ITimeMachine.hpp>
#include <ILogger.hpp>
#include <RequestReciever.hpp>
#include <IResponseSender.hpp>
#include <IResponseBuilder.hpp>
#include <ResponseBuilder.hpp>

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
#include <webserv.hpp>
#include <map>
namespace ft
{
	class Dispatcher;
}
#include <Dispatcher.hpp>
namespace ft
{
//class Server;


	static const char default_hostname[] = "localhost";

	class Server
	{
	private:
		typedef std::map<int, RequestReciever *>	listener_map;
		unsigned int			_id;
		unsigned int			_flags;
		struct sockaddr_in		serv_addr;
		struct hostent			*server;
		std::string				hostname;
		int sockfd,				port, rc, pid, err, status, client_fd;

		int					process();
		int 				ft_sendfile(int out_fd, std::string const &filename);
		unsigned int		get_file_size(std::string const &filename);

		Dispatcher				*_dispatcher;

		//IRequestReciever		*_reciever;

		RequestReciever			*_reciever;
		listener_map			_listener_map;


		IFileManager			*_f_manager;
		ILogger					*_logger;
		ITimeMachine			*_t_machine;
		IResponseSender			*_resp_sender;
		IResponseBuilder		*_resp_builder;
		
		void			close_sockets(void);
		void			listenerEvent(Dispatcher_event_args &args);
		void			clientEvent(Dispatcher_event_args &args);
		void			clientEventRead(Dispatcher_event_args &args);
		void			clientEventWrite(Dispatcher_event_args &args);
	
		Server();
	public:
		enum server_flags
		{
			is_running = 1
		};
		Server(Dispatcher *disp, IResponseSender *resp, IResponseBuilder *bulder);
		virtual ~Server();
		Server(const Server &ref);

		Server			&operator=(const Server &ref);
		bool			hasFlag(unsigned int flag);
		int				setFlag(unsigned int flag);
		int				switchFlag(unsigned int flag);
		IRequest		*getRequest(void);
		int				sendResponce(const IResponse &resp);
		int				acceptConnection();
		int				processConnection();

		void			gotEvent(Dispatcher_event_args args);
		//void			readEvent(long socket);
		//void			writeEvent(long socket);
		int				getListenSock(void);

		void			addListener(int port);

		//void			run(void);
		void			start(void);
		void			abort(void);
	};
}