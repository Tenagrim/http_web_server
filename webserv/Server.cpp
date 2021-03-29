#include <Server.hpp>

namespace ft
{
	#pragma region Copilen

	Server::Server() : _reciever(new RequestReciever(DEFAULT_HOST, DEFAULT_PORT))
	{

	}

	Server::Server(Dispatcher *disp, IResponseSender *sender , IResponseBuilder *builder) : _reciever(new RequestReciever(DEFAULT_HOST, DEFAULT_PORT)), _resp_sender(sender), _resp_builder(builder)
	{
		_dispatcher = disp;
	}
	
	Server::~Server()
	{
		delete _reciever;
	}

	Server::Server(const Server &ref) : _reciever(new RequestReciever(DEFAULT_HOST, DEFAULT_PORT))
	{
		(void)ref;
		throw std::runtime_error("no implementation");
	}

	Server &Server::operator=(const Server &ref)
	{
		(void)ref;
		throw std::runtime_error("no implementation");
		return (*this);
	}

	#pragma endregion

	#pragma region Legacy trash
	/*
	{
		bool st = false;
		port = 80;

		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		
		if (sockfd < 0)
			throw std::runtime_error("Unable to sreate socket");

		memset(&serv_addr, 0, sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		//serv_addr.sin_port = port; // htons(port);  //FIXME ?
		serv_addr.sin_port = htons(port); //FIXME ?
		serv_addr.sin_addr.s_addr = INADDR_ANY;

		//std::cout << "htons port: " << htons(port) << "\n";

		do
		{
			if ((err = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
			{
				close(sockfd);
				throw std::runtime_error("Unable to bind socket");
				//printf("Unable to bind socket [%d]\n", err);
				//usleep(10 * 1000 * 1000);
			}
			else
				st = true;
		} while (!st);

		int enable = 1;

		//if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1)
		//	throw std::runtime_error("FCNTL NONBLOCK FAILED");

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
			throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");

		printf("========= Socket binded ======\n");
		if (listen(sockfd, 25) < 0)
		{
			printf("listen error\n");
			throw std::runtime_error("Unable to listen socket");
		}
	}
	*/

	int Server::process()
	{
		int n = 0;
		IRequest *req;

		req = getRequest();
		std::cout << "\nTEXT:\n"
				  << req->getText() << "\n";

		//std::cout << "URI: " << req->getURI() << " =================\n";

		if (req->getURI() == "/")
		{
			n = write(client_fd, webpage_header, sizeof(webpage_header) - 1);
			n = write(client_fd, webpage_body, sizeof(webpage_body) - 1);
		}
		else if (req->getURI() == "/favicon.ico")
			ft_sendfile(client_fd, "resources/favicon.ico");
		else if (req->getURI() == "/trump.gif")
			ft_sendfile(client_fd, "resources/trump.gif");
		else if (req->getURI() == "/trump_vid.mp4")
			ft_sendfile(client_fd, "resources/trump_vid.mp4");
		else if (req->getURI() == "/baiden.gif")
			ft_sendfile(client_fd, "resources/baiden.gif");

		std::cout << "WRITING COMPLETED\n";

		if (n < 0)
			throw std::runtime_error("ERROR writing to socket");
		printf("EXIT FROM PROCESS\n");
		delete req;
		return (1);
	}

	IRequest *Server::getRequest(void)
	{
		std::stringstream ss;
		int n;
		char buff[4048];

		printf("GET REQUEST\n");
		n = read(client_fd, buff, 2047);
		printf("GOT REQUEST [%d]\n", n);

		if (n == 0)
			throw std::runtime_error("Empty read");
		buff[n] = 0;
		if (n == -1)
			throw std::runtime_error("Cannot read client fd");
		ss << buff;
		dprintf(2, "reading finished\n");
		return new Request(ss.str());
	}

	int Server::processConnection()
	{
		bool cont = true;
		printf("PROCESS CONNECTION\n");
		do
		{
			//close(sockfd);
			try
			{
				process();
				//close(client_fd);
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
				cont = false;
			}

		} while (cont);
		close(client_fd);
		printf("EXIT CONNECTION\n");
		//exit(0);
		return (1);
	}

	unsigned int Server::get_file_size(std::string const &filename)
	{
		std::ifstream in_file(filename, std::ios::binary);

		in_file.seekg(0, std::ios::end);
		return (in_file.tellg());
	}

	int Server::ft_sendfile(int out_fd, std::string const &_name)
	{
		char buff[2048];
		const int buffsize = 2048;
		int fd, n;
		std::stringstream ss;
		std::string str;
		unsigned int file_size;
		const char *filename = _name.c_str();

		printf("SENDFILE: %s\n", filename);

		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			printf("file %s cannot be opened\n", filename);
			return (0);
		}

		file_size = get_file_size(std::string(filename));
		std::cout << "FILE SIZE: " << file_size << "\n";

		ss << "HTTP/1.1 200 OK\r\n";
		ss << "Connection: keep-alive\r\n";
		ss << "Accept-Ranges: bytes\r\n";
		ss << "Content-Length: " << file_size << "\r\n";
		//ss << "Content-Type: image\r\n";
		ss << "\r\n";

		str = ss.str();
		std::cout << "HEADER:\n";
		std::cout << "===============\n"
				  << str << "\n=========\n";
		std::cout << "WRITE HEADER\n";
		write(out_fd, str.c_str(), str.size());
		std::cout << "HEADER WRITTEN\n";

		while ((n = read(fd, buff, buffsize)) > 0)
		{
			//std::cout << "BEGIN ["<< n <<"]\n";
			write(out_fd, buff, n);
			//std::cout << "END\n";
		}
		close(fd);
		std::cout << "FILE SENDED\n";
		return (1);
	}

	void	Server::close_sockets(void)
	{
		close(this->client_fd);
		close(this->sockfd);	
	}

	#pragma endregion // Legacy trash

	int Server::acceptConnection()
	{
		_reciever->accept_connection();
		_dispatcher->addClient(this, _reciever->getListenSock());
		return (1);
	}

	int Server::sendResponce(const IResponse &resp)
	{
		(void)resp;
		throw std::runtime_error("No implementation");
		return (-1);
	}

	#pragma region  Flags operations

	bool Server::hasFlag(unsigned int flag)
	{
		if (_flags & flag)
			return (true);
		else
			return (false);
	}

	int Server::setFlag(unsigned int flag)
	{
		_flags |= flag;
		return (1);
	}

	int Server::switchFlag(unsigned int flag)
	{
		_flags ^= flag;
		return (1);
	}

	#pragma endregion

	int				Server::getListenSock(void)
	{
		return _reciever->getListenSock();
	}

	#pragma region Events operations

	void			Server::gotEvent(Dispatcher_event_args args)
	{	
		#ifdef DEBUG
			std::cout << "SERVER: GOT EVENT\n";
		#endif
		if (args._target == listener)
			listenerEvent(args);
		else if (args._target == client)
			clientEvent(args);
		else
			throw std::runtime_error("Wrong event type");
	}

	void			Server::listenerEvent(Dispatcher_event_args &args)
	{
		int sock;
		if (args._type == reading)
		{
			if (args._fd == _reciever->getListenSock())
			{		
				sock = _reciever->accept_connection();
				_dispatcher->addClient(this, sock);
			}
			else
				throw std::runtime_error("Got wrong listener sock");
		}
		else
			throw std::runtime_error("SERVER: LISTENER EVENT: Got wrong event target");
	}

	void			Server::clientEvent(Dispatcher_event_args &args)
	{
		if (args._type == reading)
			clientEventRead(args);
		else if (args._type == writing)
			clientEventWrite(args);
		else if (args._type == conn_close)
			_reciever->close_connection(args._fd);
		else
			throw std::runtime_error("Got wrong event target");
	}


	void			Server::clientEventRead(Dispatcher_event_args &args)
	{
			IRequest	*request = _reciever->getRequest(args._fd);
			std::cout << "GOT REQUEST: [" << args._fd << "] ===========================\n";
			std::cout << request->to_string() << "===========================\n";
	}

	void			Server::clientEventWrite(Dispatcher_event_args &args)
	{
			//std::cout << "CLIENT IS READY TO READ RESPONSE ["<< args._fd <<"]\n";

		if (_reciever->writeEvent(args._fd))
		{
			std::cout << "CLIENT NEEDS RESPONSE ["<< args._fd <<"]\n";
			//sendResponce(_clients[sock]);
			IClient	*client = _reciever->getClient(args._fd);

			IResponse	*resp = _resp_builder->buildResponse(client->getLastRequest()) ;
			std::cout << "RESPONSE SENT: ================\n";
			_resp_sender->sendResponce(resp, client);
			std::cout << resp->to_string() << "\n";
			_dispatcher->closeSock(client->getSock());
			std::cout << "SOCKET CLOSED: " << client->getSock() << " ================\n";
			delete resp;
		}
	}

	#pragma endregion

	void			Server::start(void)
	{
		_reciever->start();
		_dispatcher->addListener(this);
	}

	void			Server::abort(void)
	{
		delete _reciever;
	}
}