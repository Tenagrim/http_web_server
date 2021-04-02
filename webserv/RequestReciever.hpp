#pragma once
#include <IRequestReciever.hpp>
#include <IResponseSender.hpp>
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

#include <errno.h>
#include <cstring> // For strerror

//#include <TextResponse.hpp> // TEPORARILY

#include <defines.hpp>
#include <runtime_error.hpp>
#include <IRequestValidator.hpp>
#include <FakeFakeRequestValidator.hpp>

#include <BasicRequest.hpp>
#include "Header.hpp"

namespace ft
{

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
		fd_map				_clients;

		void				open_main_socket();
		void				init_sockaddr();
		void				bind_main_socket();
		void				listen_main_socket();

		typedef				std::string::size_type strPos;
		void				headerBuilder(const std::string &text, Header *header);

		RequestReciever();
		RequestReciever(const RequestReciever &ref);
	public:
		RequestReciever(std::string const &host, int port);
		virtual ~RequestReciever();

		RequestReciever 		&operator=(const RequestReciever &ref);

		IRequest				*getRequest(Client *client);
		IRequest				*getRequest(int sock);

		int						getId();
		int						accept_connection();
		void					close_connection(int sock);
		void					close_connections(void);
		int						getListenSock();
		IClient					*getClient(int sock);
		
		int						writeEvent(int sock);
		
		void					start(void);
		int						getPort(void);

		void readHeader(Client *client, char *buff);

		void readBody(Client *client, char *buff);
	};

}
