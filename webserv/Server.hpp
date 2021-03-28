#pragma once
#include <IServer.hpp>
#include <IFileManager.hpp>
#include <ITimeMachine.hpp>
#include <ILogger.hpp>
#include <RequestReciever.hpp>

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

namespace ft
{
	class Dispatcher;
}
#include <Dispatcher.hpp>
namespace ft
{
//class Server;

	static const char webpage_header[] =
		"HTTP/1.1 200 OK\r\n"
		"Connection: keep-alive\r\n"
		"Content-Length: 636\r\n" // 614
		"Content-Type: text/html; charset=UTF-8\r\n\r\n";

	static const char webpage_body[] =
		"<!DOCTYPE html>"
		"<html>"
		"<head>"
		"<title>Welcome to myNGINX!</title>"
		"<style>"
		"    body {"
		"        width: 35em;"
		"        margin: 0 auto;"
		"        font-family: Tahoma, Verdana, Arial, sans-serif;"
		"    }"
		"</style>"
		"</head>"
		"<body>"
		"<h1>Welcome to myNGINX!</h1>"
		"<p>If you see this page, the nginx web server is successfully installed and "
		"working. Further configuration is required.</p>"

		"<p>For online documentation and support please refer to"
		"<a href=\"http://nginx.org/\">nginx.org</a>.<br/>"
		"Commercial support is available at "
		"<a href=\"http://nginx.com/\">nginx.com</a>.</p>"

		"<p><em>Thank you for using nginx.</em></p>"
		"<img src=\"trump.gif\">"
		"<img src=\"baiden.gif\">"
		"</body>"
		"</html>";

	static const char webpage2[] =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n"
		"<!DOCTYPE html>"
		"<html>"
		"<head>"
		"<title>Welcome to myNGINX!</title>"
		"<style>"
		"    body {"
		"        width: 35em;"
		"        margin: 0 auto;"
		"        font-family: Tahoma, Verdana, Arial, sans-serif;"
		"    }"
		"</style>"
		"</head>"
		"<body>"
		"<h1>Welcome to myNGINX!</h1>"
		"<p>If you see this page, the nginx web server is successfully installed and "
		"working. Further configuration is required.</p>"

		"<p>For online documentation and support please refer to"
		"<a href=\"http://nginx.org/\">nginx.org</a>.<br/>"
		"Commercial support is available at "
		"<a href=\"http://nginx.com/\">nginx.com</a>.</p>"

		"<p><em>Thank you for using nginx.</em></p>"
		"</body>"
		"</html>\r\n\r\n";

	static const char default_hostname[] = "localhost";

	class Server
	{
	private:
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

		IFileManager			*_f_manager;
		ILogger					*_logger;
		ITimeMachine			*_t_machine;
		//IRequestValidator		*_req_validator;
	
	public:
		Server();
		Server(Dispatcher *disp);
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
		void			close_sockets(void);

		void			gotEvent(Dispatcher_event_args args);
		void			readEvent(long socket);
		void			writeEvent(long socket);
		long			getListenFd(void);

		//void			run(void);
		void			start(void);
	};
}