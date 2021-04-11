#include <RequestReceiver.hpp>
#include <webserv.hpp>
#include <Header.hpp>
#include <HeaderMaker.hpp>

namespace ft {
#pragma region Copilen

	RequestReceiver::RequestReceiver() : _host(DEFAULT_HOST),
										 _port(DEFAULT_PORT) {
//		_validator = 0;
		throw ft::runtime_error("No implementation");
	}

	RequestReceiver::RequestReceiver(std::string const &host, int port) : _host(
			host), _port(port), _queue(DEFAULT_CONN_QUEUE) {
//		_validator = new FakeFakeRequestValidator();
		_client_max_id = 0;
	}

	RequestReceiver::~RequestReceiver() {
//		delete _validator;
		close_connections();
		ft_close(_main_socket);
	}

	RequestReceiver::RequestReceiver(const RequestReceiver &ref) : _host(
			DEFAULT_HOST), _port(DEFAULT_PORT) {
		(void) ref;
		throw ft::runtime_error("No implementation");
	}

	RequestReceiver &RequestReceiver::operator=(const RequestReceiver &ref) {
		(void) ref;
		throw ft::runtime_error("No implementation");
		return (*this);
	}

#pragma endregion

#pragma region Initialize

	void RequestReceiver::start() {
#ifdef DEBUG
		std::cout << "======== STARTING +++++++++++++=\n";
#endif
		open_main_socket();
		init_sockaddr();
		try {
			/* code */
			bind_main_socket();
		}
		catch (const ft::runtime_error &e)        // FIXME:   REMOVE THIS SHIT OUT HERE !!!!
		{
			std::cerr << e.what() << '\n';
			_port++;
			open_main_socket();
			init_sockaddr();
			bind_main_socket();
		}
		listen_main_socket();
#ifdef DEBUG
		std::cout << "======== STARTED +++++++++++++=\n";
#endif
	}

	void			RequestReceiver::open_main_socket()
	{
		_main_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_main_socket == -1)
			throw ft::runtime_error("Failed to create socket");
			#ifdef DEBUG
				std::cout << "MAIN SOCKET OPENED\n";
			#endif
	}

	void			RequestReceiver::init_sockaddr()
	{
		_sockaddr.sin_family = AF_INET;
		_sockaddr.sin_addr.s_addr = INADDR_ANY;
		_sockaddr.sin_port = htons(_port);
	}

	void			RequestReceiver::bind_main_socket()
	{
		int ret;

		ret = bind(_main_socket, (struct sockaddr *) &_sockaddr,
				   sizeof(_sockaddr));  // may be another sizeof
		if (ret == -1)
			throw ft::runtime_error(std::string("\nUnable to bind socket: \n" +
												std::string(strerror(errno))));
#ifdef DEBUG
		std::cout << "MAIN SOCKET BINDED\n";
#endif
	}

	void RequestReceiver::listen_main_socket() {
		int ret;
		int enable = 1;

		if (fcntl(_main_socket, F_SETFL, O_NONBLOCK) == -1)
			throw ft::runtime_error("FCNTL NONBLOCK FAILED");

#ifdef DEBUG
		std::cout << "MAIN SOCKET SET TO NONBLOCKING\n";
#endif

		ret = setsockopt(_main_socket, SOL_SOCKET, SO_REUSEADDR, &enable,
						 sizeof(int));
		if (ret < 0)
			throw ft::runtime_error("setsockopt(SO_REUSEADDR) failed");

#ifdef DEBUG
		std::cout << "SETSOCKOPT TO MAIN SOCKET\n";
#endif

		ret = listen(_main_socket, _queue);
		if (ret < 0)
			throw ft::runtime_error(std::string(
					"\nUnable to listen socket: \n" +
					std::string(strerror(errno))));

#ifdef DEBUG
		std::cout << "MAIN SOCKET LISTENED\n";
#endif
	}

#pragma endregion // INITIALIZE

#pragma region Getters

	int RequestReceiver::getId() {
		return (_id);
	}

	int RequestReceiver::getListenSock() {
		return _main_socket;
	}

#pragma endregion

#pragma region Connections

	int RequestReceiver::accept_connection() {
		unsigned int addrlen;
		int _client_fd;

#ifdef DEBUG
		std::cout << "ATTEMPT TO ACCEPT CONNECTION\n";
#endif

		addrlen = sizeof(_main_socket);
		_client_fd = accept(_main_socket, (struct sockaddr *) &_sockaddr,
							(socklen_t *) &addrlen);
		if (_client_fd < 0)
			throw ft::runtime_error(std::string(
					"\nUnable accept main socket: \n" +
					std::string(strerror(errno))));

		//_client = new Client(_client_max_id++, _client_fd);

		_clients[_client_fd] = new Client(_client_max_id++, _client_fd);

#ifdef DEBUG
		std::cout << "CONNECTION ACCEPTED\n";
#endif
		return _client_fd;
	}

	void RequestReceiver::close_connection(int sock) {
		if (!_clients.count(sock))
			throw ft::runtime_error("Can t ft_close: No such connection");
		delete _clients[sock];
		_clients.erase(sock);
	}

	void RequestReceiver::close_connections() {
		fd_map::iterator it;
		for (it = _clients.begin(); it != _clients.end(); it++)
			close_connection((*it).first);
	}

#pragma endregion

	int RequestReceiver::getRequest(int sock) {
		int ret;
		if (!_clients.count(sock))
			throw ft::runtime_error("No such client");
		ret =  getRequest(_clients[sock]);

		//if (ret == -1)
		//	close_connection(sock);
		return ret;
	}

	int RequestReceiver::getRequest(Client *client) {
		char buff[READ_BUFF_SIZE];
		int n;
		int bodyRet;
		std::string bodyPart;

		client->updateEventTime();

		if (client->getStates() == Client::s_not_begin) {
			client->setLastRequest(new BasicRequest());
			client->getLastRequest()->setPort(_port);
		}
		if (client->getStates() != Client::s_body_reading) {
			client->setStates(Client::s_start_header_reading);
			client->setFlag(Client::read_flags, Client::r_begin);
			n = recv(client->getSock(), buff, READ_BUFF_SIZE - 1, 0);
			std::cout << "READED: "<< n << " [ "<< client->getSock() << "]\n";
			if (n <= 0)
				return -1;
			buff[n] = 0;
		}
		switch (client->getStates()) {
			case Client::s_start_header_reading:
				bodyPart = HeaderMaker::readHeader(client, buff);
				break;
			case Client::s_header_reading:
				bodyPart = HeaderMaker::readHeader(client, buff);
				break;
			case Client::s_header_readed:
				HeaderMaker::validateHeader(client->getLastRequest()->getHeader());
				break;
		}
		if ((client->getStates() == Client::s_header_readed || client->getStates() == Client::s_body_reading) &&
			client->getLastRequest()->getHeader() &&
			client->getLastRequest()->getHeader()->isValid()
			) {
			//  TODO: if header fully readed
			client->getReadBuff().clear();
			if (HeaderMaker::methodNeedsBody(client->getLastRequest()->getHeader()->getMethod())) {
				if (!client->getBReader()) {
					int contLen = HeaderMaker::getContLen(*(client->getLastRequest()->getHeader()));
					client->setBReader(new BodyReader(client->getSock(), contLen, bodyPart));
				}
				client->getStates() = Client::s_body_reading;
				bodyRet = client->getBReader()->readBody();
				switch (bodyRet) {
					case 0:
						client->getLastRequest()->setBody(client->getBReader()->getBody());
						client->setFlag(Client::read_flags, Client::r_end);
						return 0;
					case 1:
						return 1;
					case -1:
						client->setFlag(Client::read_flags, Client::r_end);
						client->getLastRequest()->getHeader()->makeInvalid();
						return -1;
					case -2:
						client->setFlag(Client::read_flags, Client::r_end);
						return -1;
				}
			} else {
				client->setFlag(Client::read_flags, Client::r_end);
				return n;
			}
		}
	}

	int RequestReceiver::writeEvent(int sock) {
		if (!_clients.count(sock))
			throw ft::runtime_error("No such client");

#ifdef DEBUG
		std::cout << "RECIEVER: WRITE EVENT\n";
#endif
		if (_clients[sock]->needsResponce()) {
#ifdef DEBUG
			std::cout << "RECIEVER: NEED RESPONSE TO CLIENT\n";
#endif
			return (1);
		}
#ifdef DEBUG
		std::cout << "RECIEVER: NO NEED RESPONSE TO CLIENT\n";
#endif
		return (0);
	}

	IClient *RequestReceiver::getClient(int sock) {
		if (!_clients.count(sock))
			throw ft::runtime_error("No such client");
		return (_clients[sock]);
	}

	int RequestReceiver::getPort() {
		return _port;
	}

	std::map<int, Client *>::iterator RequestReceiver::begin() {
		return _clients.begin();
	}

	std::map<int, Client *>::iterator RequestReceiver::end() {
		return _clients.end();
	}

//	GET / HTTP/1.1\r\nHost: localhost:83\r\nUser-Agent: Go-http-client/1.1\r\nAccept-Encoding: gzip\r\n\r\n
//	POST / HTTP/1.1\r\nHost: localhost:83\r\nUser-Agent: Go-http-client/1.1\r\nTransfer-Encoding: chunked\r\nContent-Type: test/file\r\nAccept-Encoding: gzip\r\n\r\n0\r\n\r\n

}