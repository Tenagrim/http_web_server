#include <RequestReciever.hpp>

#include <Header.hpp>
namespace ft {
#pragma region Copilen

	RequestReciever::RequestReciever() : _host(DEFAULT_HOST),
										 _port(DEFAULT_PORT) {
//		_validator = 0;
		throw ft::runtime_error("No implementation");
	}

	RequestReciever::RequestReciever(std::string const &host, int port) : _host(
			host), _port(port), _queue(DEFAULT_CONN_QUEUE) {
//		_validator = new FakeFakeRequestValidator();
		_client_max_id = 0;
	}

	RequestReciever::~RequestReciever() {
//		delete _validator;
		close_connections();
		close(_main_socket);
	}

	RequestReciever::RequestReciever(const RequestReciever &ref) : _host(
			DEFAULT_HOST), _port(DEFAULT_PORT) {
		(void) ref;
		throw ft::runtime_error("No implementation");
	}

	RequestReciever &RequestReciever::operator=(const RequestReciever &ref) {
		(void) ref;
		throw ft::runtime_error("No implementation");
		return (*this);
	}

#pragma endregion

#pragma region Initialize

	void RequestReciever::start() {
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

	void			RequestReciever::open_main_socket()
	{
		_main_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_main_socket == -1)
			throw ft::runtime_error("Failed to create socket");
			#ifdef DEBUG
				std::cout << "MAIN SOCKET OPENED\n";
			#endif
	}

	void			RequestReciever::init_sockaddr()
	{
		_sockaddr.sin_family = AF_INET;
		_sockaddr.sin_addr.s_addr = INADDR_ANY;
		_sockaddr.sin_port = htons(_port);
	}

	void			RequestReciever::bind_main_socket()
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

	void RequestReciever::listen_main_socket() {
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

	int RequestReciever::getId() {
		return (_id);
	}

	int RequestReciever::getListenSock() {
		return _main_socket;
	}

#pragma endregion

#pragma region Connections

	int RequestReciever::accept_connection() {
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

		//_client = new Client(_client_max_id++, _input_fd);

		_clients[_client_fd] = new Client(_client_max_id++, _client_fd);

#ifdef DEBUG
		std::cout << "CONNECTION ACCEPTED\n";
#endif
		return _client_fd;
	}

	void RequestReciever::close_connection(int sock) {
		if (!_clients.count(sock))
			throw ft::runtime_error("Can t close: No such connection");
		delete _clients[sock];
		_clients.erase(sock);
	}

	void RequestReciever::close_connections(void) {
		fd_map::iterator it;
		for (it = _clients.begin(); it != _clients.end(); it++)
			close_connection((*it).first);
	}

#pragma endregion


	IRequest *RequestReciever::getRequest(int sock) {
		return getRequest(_clients[sock]);
	}

	IRequest *RequestReciever::getRequest(Client *client) {
		char buff[READ_BUFF_SIZE];
		int n;

		if (client->getStates() == Client::s_not_begin)
			client->setLastRequest(new BasicRequest());

		client->setStates(Client::s_start_header_reading);
		client->setFlag(Client::read_flags, Client::r_begin);


		n = recv(client->getSock(), buff, READ_BUFF_SIZE - 1, 0);
		buff[n] = 0;


	//	if (client->getStates() == Client::s_header_readed)
	//		client->setFlag(Client::read_flags, Client::r_end);

		switch (client->getStates()) {
			case Client::s_start_header_reading: readHeader(client, buff); break;
			case Client::s_header_reading: readHeader(client, buff); break;
			case Client::s_header_readed: readBody(client, buff); break;
			//case Client::s_start_body_reading: readBody(client, buff); break;
			//case Client::s_body_reading: readBody(client, buff); break;
//			default: throw ft::runtime_error("" + __LINE__);
		}
//		TODO read body
		IBody *body;


		return (nullptr);
	}



	void RequestReciever::readHeader(Client *client, char *buff) {
		int end_pos;
		int ending;
		if (client->getStates() == Client::s_start_header_reading)
			client->getLastRequest()->setHeader(new Header(request));

		client->getReadBuff().append(buff);

		end_pos = client->getReadBuff().find("\r\n\r\n");
		ending = 4;
		if (end_pos == std::string::npos) {
			end_pos = client->getReadBuff().find("\n\n");
			ending = 2;
		}

		if (end_pos != std::string::npos)
		{
//			TODO write part of body to it's fd
//			null - terminate string
			headerBuilder(client->getReadBuff(),
						  client->getLastRequest()->getHeader(), client->getStates());

			if (!client->getLastRequest()->getHeader()->isValid()) {
				client->setStates(Client::s_end_reading);
				client->setFlag(Client::read_flags, Client::r_end);
			}
			client->setStates(Client::s_header_readed);

			/*
			if (client->getLastRequest()->getHeader()->isValid() &&
				methodNeedsBody(client->getLastRequest()->getHeader()->getMethod()))
			{
				std::cout<< "NEED BODY\n";
					client->setStates(Client::s_start_body_reading);

				//if(end_pos + ending == client->getReadBuff().size())
				//	client->setStates(Client::s_start_body_reading);
				//else
				client->setFlag(Client::read_flags, Client::r_end);
			}
			else
			 */
				client->setFlag(Client::read_flags, Client::r_end);

		}
		else
			client->setStates(Client::s_header_reading);
	}

	void RequestReciever::readBody(Client *client, char *buff) {
		std::string reqHeader;


	}

	int RequestReciever::writeEvent(int sock) {
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

	IClient *RequestReciever::getClient(int sock) {
		if (!_clients.count(sock))
			throw ft::runtime_error("No such client");
		return (_clients[sock]);
	}

	int RequestReciever::getPort() {
		return _port;
	}

	void
	RequestReciever::headerBuilder(const std::string &text, IHeader *header,
								Client::req_read_states &state) {
		std::string subLine;
		strPos pos1 = 0, pos2;



		while ((pos2 = text.find("\n", pos1)) != std::string::npos && header->isValid()) {
			subLine = text.substr(pos1, pos2 - pos1);
			subLine.erase(std::remove(subLine.begin(), subLine.end(), '\r'), subLine.end());
			pos1 = pos2 + 1;
			switch (state) {
				case Client::s_start_header_reading: firstLine(subLine, header,state); break;
				case Client::s_header_reading: fillHeader(subLine, header, state); break;
					break;
			}
		}
	}

	void RequestReciever::firstLine(std::string const &line, IHeader *header,
								 Client::req_read_states &state) {
		fillMethod(line, header);
		fillUrl(line, header);
		checkHttp(line, header);
		state = Client::s_header_reading;
	}

	void RequestReciever::fillMethod(const std::string &line, IHeader *header) {
		std::string method;
		int i = 0;
		methods_enum a;

		method = line.substr(0, line.find(' '));
		do {
			a = static_cast<methods_enum>(i);
			i++;
		}
		while (method != getMethodStr(a));
		header->setMethod(a);
	}

	void RequestReciever::fillUrl(const std::string &line, IHeader *header) {
		strPos a = line.find(' ') + 1;
		strPos b = line.rfind(' ');

		header->setURI(line.substr(a, b - a));
	}

	void RequestReciever::checkHttp(const std::string &line, IHeader *header) {
		std::string http;

		http = line.substr(line.rfind(' ') + 1, 8);
		if (http != "HTTP/1.1")
			//throw std::runtime_error("RequestValidator: invalid HTTP version");
			header->makeInvalid();
	}

	void RequestReciever::fillHeader(std::string subLine, IHeader *header,
								  Client::req_read_states &states) {
		int i = 0;
		header_keys a;
		std::string head;
		std::string key;

//		TODO
		head = subLine.substr(0, subLine.find(':'));
		do {
			a = static_cast<header_keys>(i);
			i++;
		}
		while (!(key = getHeaderKey(a)).empty() && key != head);
		if (key.empty())
			return ;
		if (header->isHeadAlreadyExist(a)) {
			header->makeInvalid();
			return ;
		}
		subLine = subLine.substr(subLine.find(':') + 1);
		while (subLine[0] == ' ') {
			subLine.erase(0, 1);
		}
		header->setHeader(a, subLine);
	}

	bool RequestReciever::methodNeedsBody(methods_enum method) {
		return (method == m_post || method == m_put);
	}

}