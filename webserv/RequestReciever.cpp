#include <RequestReciever.hpp>
namespace ft
{
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
	
	void				RequestReciever::accept_connection()
	{
		unsigned int	addrlen;
			
			#ifdef DEBUG
				std::cout << "ATTEMPT TO ACEPT CONNECTION\n";
			#endif

		addrlen = sizeof(_main_socket);
		_client_fd = accept(_main_socket, (struct sockaddr*)&_sockaddr, (socklen_t*)&addrlen);
		if (_client_fd < 0)
			throw std::runtime_error(std::string("\nUnable accept main socket: \n" + std::string(strerror(errno))));
		_client_connected = true;	
			#ifdef DEBUG
				std::cout << "CONNECTION ACCEPTED\n";
			#endif
	}

	bool				RequestReciever::is_data_in_socket(int sock)
	{
		struct timeval		timeout;
		int					sret;
		fd_set				fdset;

		timeout.tv_usec = CHECK_SOCKET_DELAY % 1000;
		timeout.tv_sec = CHECK_SOCKET_DELAY / 1000;
		FD_ZERO(&fdset);
		FD_SET(sock, &fdset);

		sret = select(1, &fdset, NULL, NULL, &timeout);

		if (sret)
		{
			#ifdef DEBUG
				std::cout << "READY TO READ " << sret << " BYTES OF DATA IN SOCKET\n";
			#endif
			return true;
		}
		else
		{
			#ifdef DEBUG
				std::cout << "NO DATA IN SOCKET\n";
			#endif
			return false;
		}
	}

	bool				RequestReciever::is_client_data(unsigned int delay)
	{
		struct timeval		timeout;
		int					sret;
		fd_set				fdset;

		if (!_client_connected)
		{
			#ifdef DEBUG
				std::cout << "NO CLIENT CONNECTED\n";
			#endif
			return false;
		}

		#pragma region save some usecs
		if (delay <= 1000)
		{
			timeout.tv_usec = delay;
			timeout.tv_sec = 0;
		}
		else
		{
			timeout.tv_usec = delay % 1000;
			timeout.tv_sec = delay / 1000;
		}
		#pragma endregion
		
		FD_ZERO(&fdset);
		FD_SET(_client_fd, &fdset);

		sret = select(1, &fdset, NULL, NULL, &timeout);
		//            ^num of fds
		//                  ^read fds
		//                        ^write fds
		//                              ^err fds
		//                                    ^delay
		return (sret);	
		/*
		if (sret)
		{
			#ifdef DEBUG
				std::cout << "READY TO READ " << sret << " BYTES OF DATA\n";
			#endif
			return true;
		}
		else
		{
			#ifdef DEBUG
				std::cout << "NO CLIENT DATA HERE\n";
			#endif
			return false;
		}
		*/
	}

	std::string			RequestReciever::read_client_fd()
	{
		std::stringstream	ss;
		char				buff[READ_BUFF_SIZE];
		int					readed;
			
			#ifdef DEBUG
				std::cout << "READING CLIENT FD\n";
			#endif

		while (is_client_data(CHECK_SOCKET_DELAY)) 
		{
			readed = read(_client_fd, buff, READ_BUFF_SIZE - 1);
			if (readed == - 1)
				throw std::runtime_error(std::string("\nUnable read client socket: \n" + std::string(strerror(errno))));
			ss << buff;
		}
			#ifdef DEBUG
				std::cout << "CLIENT FD READED\n";
			#endif
		return(ss.str());
	}
	
	void					RequestReciever::close_connection()
	{
		if (_client_connected)
		{
			close(_client_fd);
			_client_connected = false;
		}
	}


	IRequest				*RequestReciever::getRequest()
	{
		if (!_client_connected)
			throw std::runtime_error("No Client Connected");
		if (!is_client_data(CHECK_SOCKET_DELAY))
			throw std::runtime_error("No Client Data to read");
		
		std::string		text = read_client_fd();
		return new Request(text);
	}

	RequestReciever::RequestReciever() : _host(DEFAULT_HOST), _port(DEFAULT_PORT)
	{
		throw std::runtime_error("No implementation");
	}

	RequestReciever::RequestReciever(std::string const &host, int port) : _host(host), _port(port), _queue(DEFAULT_CONN_QUEUE),  _client_connected(false)
	{
	}

	RequestReciever::~RequestReciever()
	{
		close_connection();
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

	int						RequestReciever::getId()
	{
		return(_id);
	}

	long					RequestReciever::getListenFd()
	{
		return _main_socket;
	}
}