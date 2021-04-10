#include <Server.hpp>
#include <runtime_error.hpp>
namespace ft
{
	#pragma region Copilen

	Server::Server()// : _reciever(new RequestReceiver(DEFAULT_HOST, DEFAULT_PORT))
	{/* Illegal */}

	Server::Server(IResponseBuilder *builder) : _resp_builder(builder)
	{
		_dispatcher = new Dispatcher();
		_dispatcher->connectToServer(this);
		_resp_sender = new ResponseSender(_dispatcher);
		_flags = 0;
	}
	
	Server::~Server()
	{
		abort();
		delete _dispatcher;
		delete _resp_sender;
	}

	Server::Server(const Server &ref) //: _reciever(new RequestReceiver(DEFAULT_HOST, DEFAULT_PORT))
	{
		(void)ref;
		throw ft::runtime_error("no implementation");
	}

	Server &Server::operator=(const Server &ref)
	{
		(void)ref;
		throw ft::runtime_error("no implementation");
		return (*this);
	}

	#pragma endregion

	int Server::acceptConnection(int sock)
	{
		int client_fd;
		RequestReceiver	*recv = getListener(sock);

		client_fd = _listener_map[sock]->accept_connection();
		_dispatcher->addClient(recv, client_fd);
		return (1);
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
/*
	int				Server::getListenSock(void)
	{
		return _reciever->getListenSock();
	}
*/
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
			throw ft::runtime_error("Wrong event type");
	}

	void			Server::listenerEvent(Dispatcher_event_args &args)
	{
		int sock;

		RequestReceiver	*_reciever = getListener(args._fd);
		if (args._type == reading)
		{
			if (args._fd == _reciever->getListenSock())
			{		
				sock = _reciever->accept_connection();
				_dispatcher->addClient(_reciever, sock);
			}
			else
				throw ft::runtime_error("Got wrong listener sock");
		}
		else
			throw ft::runtime_error("SERVER: LISTENER EVENT: Got wrong event target");
	}

	void			Server::clientEvent(Dispatcher_event_args &args)
	{
		RequestReceiver	*_reciever = args._reciever;
		if (args._type == reading)
			clientEventRead(args);
		else if (args._type == writing)
			clientEventWrite(args);
		else if (args._type == conn_close)
			_reciever->close_connection(args._fd);
		else
			throw ft::runtime_error("Got wrong event target");
	}


	void			Server::clientEventRead(Dispatcher_event_args &args)
	{
			args._reciever->getRequest(args._fd);

//			std::cout << "CLIENT IS WRITING. NEED TO READ\n";
			#ifdef DEBUG
			//	std::cout << "GOT REQUEST: [" << args._fd << "] ===========================\n";
			//	std::cout << request->to_string() << "===========================\n";
			#endif
	}

	void			Server::clientEventWrite(Dispatcher_event_args &args)
	{
			IResponse *resp = NULL;
			Client			*client;
		//	#ifdef DEBUG
		//		std::cout << "CLIENT NEEDS RESPONSE ["<< args._fd <<"]\n";
		//	#endif
			client = dynamic_cast<Client*>(args._reciever->getClient(args._fd));
			if (!client)
				throw ft::runtime_error("Unknown type of client");

		//RequestReciever	*_reciever = _listener_map[args._fd];
		if (args._reciever->writeEvent(args._fd))
		{
//			FIXME normal size check
			/*if (client->getLastRequest() && client->getLastRequest()->to_string().size() == 0)
			{
				#ifdef DEBUG
				std::cout << "FINISHING MESSAGE RECEIVED. CLOSING\n";
				#endif
				_dispatcher->ft_closeSock(client->getSock());
				return;
			}
*/
			if (client->getStates() == Client::s_start_body_reading) {
				client->setFlag(Client::read_flags, Client::r_end);
				return;
			}
			if (!client->getLastResponse())
			{
				resp = _resp_builder->buildResponse(client->getLastRequest());
				client->setLastResponse(resp);
			}
			else
				resp = client->getLastResponse();

			int ret;
			ret = _resp_sender->sendResponce(resp, client);

			if ((ret == 0 && (resp->getHeader()->isHeadAlreadyExist(h_connection)) &&
				resp->getHeader()->getHeader(h_connection) == "close") ||
					(resp->getHeader()->getResponseCode() == 400)
					)
				_dispatcher->ft_closeSock(client->getSock());

			if (ret == 0)
				client->reset();
			#ifdef DEBUG
				std::cout << "RESPONSE SENT: ================\n";	
				std::cout << "RESP BODY SIZE: ["<< resp->getBody()->size() <<"]\n";
				std::cout << "RESP BODY STR SIZE: ["<< resp->getBody()->to_string().size() <<"]\n";
			#endif

			#ifdef DEBUG
				std::cout << "WRITE EVENT END : " << client->getSock() << " ================\n";
			#endif
		}
		/*
		else
		{
			unsigned  long diff = client->getUsecsFromLastEvent();
//			std::cout << "CLIENT DIFF: " << diff <<"\n";
			if ( diff > CLIENT_TIMEOUT_MICROS) {
				//if (!client->getLastRequest())
				//	client->setLastRequest(new BasicRequest());
				//if (!client->getLastRequest()->getHeader())
				//	client->getLastRequest()->setHeader(new Header(request));
				//client->getLastRequest()->getHeader()->makeInvalid();
				//client->setFlag(Client::read_flags, Client::r_end);
				_dispatcher->ft_closeSock(client->getSock());
			}

		}
		*/
	}

	#pragma endregion

	void			Server::start()
	{
		//RequestReciever *recv;
		setFlag(is_running);

		std::cout << yellow << "SERVER: IS STARITING\nLISTENING:\n" << green;
		for(std::list<RequestReceiver*>::iterator it = _list_to_start.begin(); it != _list_to_start.end(); it++)
		{
			(*it)->start();
			_listener_map[(*it)->getListenSock()] = *it;
			_dispatcher->addListener((*it), (*it)->getListenSock());
			std::cout << "["<< (*it)->getListenSock() << "|"<< (*it)->getPort() <<"] ";
		}
		std::cout << reset << "\n";
		_list_to_start.clear();

		_dispatcher->start();
	}
	
	void							Server::stop()
	{
		if (!_dispatcher)
			throw ft::runtime_error("No connection to dispatcher");
		_dispatcher->stop();
	}
	void			Server::abort(void)
	{
		for (listener_map::iterator it = _listener_map.begin(); it != _listener_map.end(); it++)
			delete (*it).second;
	}
	
	void			Server::addListener(int port)
	{
		#ifdef DEBUG
			std::cout << "SERVER: ADD LISTENER";
		#endif
			if(hasFlag(is_running))
				throw ft::runtime_error("Cannot add new listener into running server");
			//_listener_map[port] = new RequestReceiver("localhost", port);
			for(std::list<RequestReceiver*>::iterator it = _list_to_start.begin(); it != _list_to_start.end(); it++)
				if ((*it)->getPort() == port)
					throw ft::runtime_error("Cannot add listener with same port:" + ft::to_string(port));
			_list_to_start.push_back(new RequestReceiver("localhost", port));

	}

	RequestReceiver		*Server::getListener(int sock)
	{
		if (!_listener_map.count(sock))
			throw ft::runtime_error("No such listener: " + ft::to_string(sock));
		return _listener_map[sock];
	}

}