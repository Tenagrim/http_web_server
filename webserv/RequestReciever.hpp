#pragma once
#include <IRequestReciever.hpp>
#include <Request.hpp>
#include <Client.hpp>
#include <webserv.hpp>

#include <exception>
#include <string>
#include <sstream>

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib>		// For exit() and EXIT_FAILURE
#include <iostream>		// For cout
#include <unistd.h>		// For read
#include <sys/select.h> // For select
#include <fcntl.h>
#include <sstream>
#include <map>

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
		typedef				std::map<int, Client *> fd_map;
		
		int					_id;
		int					_client_max_id;
		int					_main_socket;
		sockaddr_in			_sockaddr;
		std::string			_host;
		int					_port;
		int 				_queue;				// only default
		//Client				*_client;
		fd_map				_clients;

		void				open_main_socket();
		void				init_sockaddr();
		void				bind_main_socket();
		void				listen_main_socket();
		
		RequestReciever();
	public:
		RequestReciever(std::string const &host, int port);
		virtual ~RequestReciever();
		RequestReciever(const RequestReciever &ref);

		RequestReciever 		&operator=(const RequestReciever &ref);
		IRequest				*getRequest(Client *client);
		IRequest				*getRequest(int sock);
		int						getId();
		int						accept_connection();
		void					close_connection(int sock);
		void					close_connections(void);
		int						getListenSock();
		
		void					writeEvent(int sock);
		
		void					sendResponce(Client *client); // REMOVE THIS LOGIC FROM HERE

		void					start(void);
	};

}