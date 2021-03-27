#pragma once
#include <IRequestReciever.hpp>
#include <Request.hpp>
#include <exception>
#include <string>
#include <sstream>

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib>		// For exit() and EXIT_FAILURE
#include <iostream>		// For cout
#include <unistd.h>		// For read
#include <sys/select.h> // For select

#include <errno.h> // may be FORBIDDEN

#define DEBUG 1

namespace ft
{

	#define DEFAULT_PORT			83
	#define DEFAULT_HOST			"localhost"
	#define DEFAULT_CONN_QUEUE		10
	#define READ_BUFF_SIZE			2048
	#define DEFAULT_CLIENT_DELAY	1000 * 1000 * 5
	#define CHECK_SOCKET_DELAY		100

	class RequestReciever : public IRequestReciever
	{
	private:
		int					_id;
		int					_main_socket;
		sockaddr_in			_sockaddr;
		std::string			_host;
		int					_port;
		int 				_queue;				// only default
		int					_client_fd;
		bool				_client_connected;

		void				open_main_socket();
		void				init_sockaddr();
		void				bind_main_socket();
		void				listen_main_socket();
		std::string			read_client_fd();

	public:
		RequestReciever();
		RequestReciever(std::string const &host, int port);
		virtual ~RequestReciever();
		RequestReciever(const RequestReciever &ref);

		RequestReciever 		&operator=(const RequestReciever &ref);
		IRequest				*getRequest();
		int						getId();
		bool					is_client_data(unsigned int delay);
		void					accept_connection();
		void					close_connection();
		long					getListenFd();
		
		static bool				is_data_in_socket(int sock);
		void					start(void);
	};

}