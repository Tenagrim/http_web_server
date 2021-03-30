#include <RequestReciever.hpp>

namespace ft
{
	#pragma region Copilen

	RequestReciever::RequestReciever() : _host(DEFAULT_HOST), _port(DEFAULT_PORT)
	{
		throw std::runtime_error("No implementation");
	}

	RequestReciever::RequestReciever(std::string const &host, int port) : _host(host), _port(port), _queue(DEFAULT_CONN_QUEUE)
	{
		_client_max_id = 0;
	}

	RequestReciever::~RequestReciever()
	{
		close_connections();
		close(_main_socket);
	}

	RequestReciever::RequestReciever(const RequestReciever &ref) : _host(DEFAULT_HOST), _port(DEFAULT_PORT)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
	}

	RequestReciever &RequestReciever::operator=(const RequestReciever &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
		return (*this);
	}

	#pragma endregion

	#pragma region Initialize
	void			RequestReciever::start()
	{
			#ifdef DEBUG
				std::cout << "======== STARTING +++++++++++++=\n";
			#endif
		open_main_socket();
		init_sockaddr();
		bind_main_socket();
		listen_main_socket();
			#ifdef DEBUG
				std::cout << "======== STARTED +++++++++++++=\n";
			#endif
	}

	void			RequestReciever::open_main_socket(void)
	{
		_main_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_main_socket == -1)
			throw std::runtime_error("Failed to create socket");
			#ifdef DEBUG
				std::cout << "MAIN SOCKET OPENED\n";
			#endif
	}
	
	void			RequestReciever::init_sockaddr(void)
	{	
		_sockaddr.sin_family = AF_INET;
		_sockaddr.sin_addr.s_addr = INADDR_ANY;
		_sockaddr.sin_port = htons(_port);
	}

	void				RequestReciever::unlink_main_socket()
	{
		int ret;

		//ret = unlink
	}
	
	void			RequestReciever::bind_main_socket(void)
	{
		int ret;

		ret = bind(_main_socket, (struct sockaddr*)&_sockaddr, sizeof(_sockaddr));  // may be another sizeof
		if (ret == -1)
			throw std::runtime_error(std::string("\nUnable to bind socket: \n" + std::string(strerror(errno))));
			#ifdef DEBUG
				std::cout << "MAIN SOCKET BINDED\n";
			#endif
	}

	void				RequestReciever::listen_main_socket()
	{
		int ret;
		int enable = 1;

		if (fcntl(_main_socket, F_SETFL, O_NONBLOCK) == -1)
			throw std::runtime_error("FCNTL NONBLOCK FAILED");
			
			#ifdef DEBUG
				std::cout << "MAIN SOCKET SET TO NONBLOCKING\n";
			#endif
		
		ret = setsockopt(_main_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
		if (ret < 0)
			throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
			
			#ifdef DEBUG
				std::cout << "SETSOCKOPT TO MAIN SOCKET\n";
			#endif
			
		ret = listen(_main_socket, _queue);
		if (ret < 0)
			throw std::runtime_error(std::string("\nUnable to listen socket: \n" + std::string(strerror(errno))));
			
			#ifdef DEBUG
				std::cout << "MAIN SOCKET LISTENED\n";
			#endif
	}

	#pragma endregion // INITIALIZE

	#pragma region Getters
	int						RequestReciever::getId()
	{
		return(_id);
	}

	int						RequestReciever::getListenSock()
	{
		return _main_socket;
	}
	#pragma endregion

	#pragma region Connections

	int					RequestReciever::accept_connection()
	{
		unsigned int	addrlen;
		int				_client_fd;
			
			#ifdef DEBUG
				std::cout << "ATTEMPT TO ACCEPT CONNECTION\n";
			#endif
		
		/*
		if ( _client)
		{ 
			#ifdef DEBUG
				std::cout << "ALREADY CONNNECTED\n";
			#endif
			return 0;
		}
		*/

		addrlen = sizeof(_main_socket);
		_client_fd = accept(_main_socket, (struct sockaddr*)&_sockaddr, (socklen_t*)&addrlen);
		if (_client_fd < 0)
			throw std::runtime_error(std::string("\nUnable accept main socket: \n" + std::string(strerror(errno))));

		//_client = new Client(_client_max_id++, _client_fd);

		_clients[_client_fd] = new Client(_client_max_id++, _client_fd);

			#ifdef DEBUG
				std::cout << "CONNECTION ACCEPTED\n";
			#endif
		return _client_fd;
	}
	
	void					RequestReciever::close_connection(int sock)
	{
		if (!_clients.count(sock))
			throw std::runtime_error("Can t close: No such connection");

		delete	_clients[sock];
		_clients.erase(sock);
	}

	void					RequestReciever::close_connections(void)
	{
		fd_map::iterator	it;
		for(it = _clients.begin(); it != _clients.end(); it++)
			close_connection((*it).first);
	}

	#pragma endregion


	IRequest				*RequestReciever::getRequest(int sock)
	{
		//if (_client->getSock() != sock)
		//	throw std::runtime_error("No client with this sock");
		return getRequest(_clients[sock]);
	}

	IRequest				*RequestReciever::getRequest(Client *client)
	{
		char				buff[READ_BUFF_SIZE];
		std::stringstream	ss;
		int					n;
		IRequest			*request;

		n = recv(client->getSock(), buff, READ_BUFF_SIZE - 1, 0);
		buff[n] = 0;
		ss << buff;

		request = new Request(ss.str());

		client->setFlag(Client::state_flags, Client::need_response);
		client->setLastRequest(request);


		return (request);
	}

	void					RequestReciever::sendResponce(Client *client)
	{
		write(client->getSock(), webpage_header, sizeof(webpage_header));
		std::cout << "HEADER SEND ["<< client->getSock() <<"]\n";
		write(client->getSock(), webpage_body, sizeof(webpage_body));
		std::cout << "RESPONSE SEND ["<< client->getSock() <<"]\n";

	}


	int					RequestReciever::writeEvent(int sock)
	{
		if (!_clients.count(sock))
			throw std::runtime_error("No such client");
		
		std::cout << "RECIEVER: WRITE EVENT\n";
		if (_clients[sock]->needsResponce())
		{
			_clients[sock]->unsetFlag(Client::state_flags, Client::need_response);
			return (1);
		}
		return (0);

	}
	IClient					*RequestReciever::getClient(int sock)
	{
		if (!_clients.count(sock))
			throw std::runtime_error("No such client");
		return(_clients[sock]);
	}

}