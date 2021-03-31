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
			IResponse		*resp;
			IClient			*client;
			std::cout << "CLIENT NEEDS RESPONSE ["<< args._fd <<"]\n";
			client = _reciever->getClient(args._fd);
			if (client->getLastRequest() && client->getLastRequest()->getText().size() == 0)
			{
				std::cout << "FINISHING MESSAGE RECEIVED. CLOSING\n";
				_dispatcher->closeSock(client->getSock());
				return;
			}

			if (!client->getLastResponse())
			{
				resp = _resp_builder->buildResponse(client->getLastRequest());
				client->setLastResponse(resp);
			}
			else
				resp = client->getLastResponse();
			std::cout << "RESPONSE SENT: ================\n";
			_resp_sender->sendResponce(resp, client);
			//std::cout << resp->to_string() << "\n";
			std::cout << "RESP BODY SIZE: ["<< resp->getBody()->size() <<"]\n";
			std::cout << "RESP BODY STR SIZE: ["<< resp->getBody()->to_string().size() <<"]\n";
			if (client->requestReceived() && !client->needsResponce())
				_dispatcher->closeSock(client->getSock());


			std::cout << "WRITE EVENT END : " << client->getSock() << " ================\n";
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