#include <Dispatcher.hpp>
#include <Server.hpp>

namespace ft
{
	#pragma region 	Copilen form
	Dispatcher::Dispatcher() : _listener_map()
	{
		_upd_delay.tv_usec = UPDATE_DELAY % 1000;
		_upd_delay.tv_sec = UPDATE_DELAY / 1000000;
		_listening = 0;
		FD_ZERO(&_fd_set);
		_max_fd = 0;
		_server = 0;
		_run = false;
		_delay = DISPATCHER_WAKE_DELAY;
	}

	Dispatcher::~Dispatcher()
	{}

	Dispatcher::Dispatcher(const Dispatcher &ref)
	{
		(void)ref;
		throw ft::runtime_error("Not implemented");
	}

	Dispatcher &Dispatcher::operator=(const Dispatcher &ref)
	{
		(void)ref;
		throw ft::runtime_error("Not implemented");
		return (*this);
	}
	#pragma endregion

	#pragma region Add_remove socks

	void			Dispatcher::addListener(RequestReceiver *recv, int sock)
	{
		#ifdef DEBUG
			std::cout << "ADD LISTENER[" << sock << "]\n";
		#endif
		_listener_map[sock] = recv;
		if (sock > _max_fd)
			_max_fd = sock;
		FD_SET(sock, &_fd_set);
		_listening++;
	}

	void			Dispatcher::addClient(RequestReceiver *recv, int sock)
	{
		#ifdef DEBUG
			std::cout << "ADD CLIENT[" << sock << "]\n";
		#endif
		_client_map[sock] = recv;
		if (sock > _max_fd)
			_max_fd = sock;
		FD_SET(sock, &_fd_set);
		_listening++;
	}

	void Dispatcher::closeSock(int sock)
	{
		if (std::find(_socks_to_close.begin(), _socks_to_close.end(), sock) == _socks_to_close.end())
		_socks_to_close.push_front(sock);
	}
	
	void Dispatcher::closeWhatNeed()
	{
		int sock;
		if (_socks_to_close.empty())
			return;
		#ifdef DEBUG
		std::cout << "CLOSING SOCKETS";
		#endif
		while (!_socks_to_close.empty())
		{
			sock = _socks_to_close.front();
			reallyCloseSock(sock);
			_socks_to_close.erase(_socks_to_close.begin());
		#ifdef DEBUG
			std::cout << " CLOSING[" << sock<< "]\n";
			for(fd_map::iterator it = _client_map.begin(); it != _client_map.end(); it++)
				std::cout << "[" << (*it).first << "] ";
			std::cout << "\n";
			std::cout << " ft_closeD[" << sock<< "]\n";
			std::cout << "MAX FD: ["<<_max_fd <<"]\n";
		#endif
		}
	}

	void Dispatcher::reallyCloseSock(int sock)
	{
		if (_listener_map.count(sock))
		{
			_server->gotEvent(Dispatcher_event_args(sock, conn_close, listener, _listener_map[sock]));
			_listener_map.erase(sock);
			if (sock == _max_fd)
				_max_fd = _listener_map.rbegin()->first;
		}
		else if (_client_map.count(sock))
		{
			_server->gotEvent(Dispatcher_event_args(sock, conn_close, client, _client_map[sock]));
			_client_map.erase(sock);
			if (sock == _max_fd)
			{
				if (!_client_map.empty())
					_max_fd = _client_map.rbegin()->first;
				else if (!_listener_map.empty())
					_max_fd = _listener_map.rbegin()->first;
				else
					_max_fd = 0;
			}
		}
		else {
			return;
			throw ft::runtime_error("requested sock not found to delete it");
		}
		//FD_CLR(sock, &_fd_set);
		_listening--;
	}

	#pragma endregion

	#pragma region Events

	void			Dispatcher::updateEvents()
	{
		//#undef DEBUG

			#ifdef DEBUG
		//		static int i;
			
			//	std::cout << "DISPATCHER: UPDATE EVENTS ["<< i++ <<"] max fd: "<< _max_fd <<"\n";
				std::cout << "CLIENTS: \n";
				fd_map::iterator it = _client_map.begin();
				for(; it != _client_map.end(); it++)
					std::cout << "[" << (*it).first << "] ";
				std::cout << "\n";

				std::cout << "CLIENTS: \n";
				it = _client_map.begin();
				for(; it != _client_map.end(); it++)
					std::cout << "[" << (*it).first << "] ";
				std::cout << "\n";

				std::cout << "LISTENERS: \n";
				it = _listener_map.begin();
				for(; it != _listener_map.end(); it++)
					std::cout << "[" << (*it).second->getListenSock() << "|" << (*it).second->getPort() << "] ";
				std::cout << "\n";
			#endif
		_events = 0;
		if (_listening == 0)
			throw ft::runtime_error("No have fd to dispatch");
		//ft_memcpy(&_reading_set, &_fd_set, sizeof(_fd_set));
		//ft_memcpy(&_writing_set, &_fd_set, sizeof(_fd_set));
		//FD_ZERO(&_writing_set);

		#ifdef DEBUG
		std::cout << "DISPATCHER: SELECTIN..." << " " << "\n";
		#endif

		initFdSets();

	//	if (_client_map.empty())
	//		_events = select(_max_fd + 1, &_reading_set, NULL, NULL, &_upd_delay);
	//	else
		_events = select(_max_fd + 1, &_reading_set, &_writing_set, NULL, &_upd_delay);

		if (!_events) {
			sleep();
			BodyReader::reset();
			CgiModule::reset();
		}
		else
			wakeUp();
			#ifdef DEBUG
				std::cout << "DISPATCHER: EVENTS UPDATET. GOT: " << _events << "\n";
			#endif

		//#define DEBUG
	}


	void					Dispatcher::handleListeners()
	{
		fd_map::iterator it;
		for(it = _listener_map.begin();it != _listener_map.end() ;it++)
		{	
			if (FD_ISSET((*it).first, &_reading_set))
				_server->gotEvent(Dispatcher_event_args((*it).first, reading, listener, (*it).second));
		}
	}

	void					Dispatcher::handleClientsRead()
	{
		fd_map::iterator it;
		for(it = _client_map.begin();it != _client_map.end() ;it++)
		{
			if (FD_ISSET((*it).first, &_reading_set)) {
			//	std::cout << "READING EVENT ON: "<< it->first <<" \n";
				_server->gotEvent(Dispatcher_event_args(it->first, reading, client, (*it).second));
			//	FD_CLR((*it).first, &_writing_set);
			}
		}
	}

	void					Dispatcher::handleClientsWrite()
	{
		fd_map::iterator it;
		unsigned long diff;
		for(it = _client_map.begin();it != _client_map.end() ;it++)
		{
			if (FD_ISSET((*it).first, &_writing_set)) {
			//	std::cout << "WRITING EVENT ON: "<< it->first <<" \n";
				_server->gotEvent(Dispatcher_event_args((*it).first, writing, client, (*it).second));
			}
		}
	}

	void Dispatcher::killZombies() {
		fd_map::iterator it;
		unsigned long diff;
		int sock;
		for(it = _client_map.begin();it != _client_map.end() ;it++) {
			diff = (*it).second->getClient((*it).first)->getUsecsFromLastEvent();
			sock = it->first;
			if (diff > CLIENT_TIMEOUT_MICROS)
				closeSock((*it).first);
			else if (diff > CLIENT_TIMEOUT_MICROS &&
					!FD_ISSET(sock, &_writing_set) &&
					!FD_ISSET(sock, &_reading_set))
				closeSock((*it).first);
		}
	}

	void					Dispatcher::handleClients()
	{
		handleClientsRead();
		handleClientsWrite();

	}

	void			Dispatcher::handleEvents()
	{
		if (_events == 0)
		{
		//	std::cout << "DISPATCHER: NO EVENTS\n";
			#ifdef DEBUG
				std::cout << "DISPATCHER: NO EVENTS\n";
			#endif
			return ;
		}

			#ifdef DEBUG
				std::cout << "DISPATCHER: HANDLING EVENTS\n";
			#endif

		handleListeners();
		handleClients();
	}
	#pragma endregion	

	void			Dispatcher::connectToServer(Server *serv)
	{
		_server = serv;
	}
	void			Dispatcher::start()
	{
		if (!_server)
			throw ft::runtime_error("Not connected to server");
		_run = true;

		unsigned int count;


		while (_run)
		{
			updateEvents();
			handleEvents();
			closeWhatNeed();
		//	count = GetBuildPolicy::getCount();
			//std::cout << " ============== GET RESPONSES BUILT: " << count << "\n";
			//killZombies();
			usleep(_delay);
		}
	}
	void			Dispatcher::stop()
	{
		_run = false;
	}

	void Dispatcher::wakeUp() {
		//std::cout<< "WAKING UP\n";
	_delay = DISPATCHER_WAKE_DELAY;
	}

	void Dispatcher::sleep() {
		//std::cout<< "SLEEPING\n";
		_delay = DISPATCHER_SLEEP_DELAY;
	}

	void Dispatcher::initFdSets() {
		Client	*client;
		FD_ZERO(&_reading_set);
		FD_ZERO(&_writing_set);
		_max_fd = 0;

		fd_map::iterator it = _listener_map.begin();
		for(; it != _listener_map.end(); it++) {
			FD_SET(it->first, &_reading_set);
			setMax(it->first);
		}
		it = _client_map.begin();
		for(; it != _client_map.end(); it++)
		{
			FD_SET(it->first, &_reading_set);
			setMax(it->first);
			client = dynamic_cast<Client *>(it->second->getClient(it->first));
			if (!client)
				throw ft::runtime_error("Unknown type after dynamic cast");
			if (client->hasFlag(Client::read_flags, Client::r_end))
				FD_SET(it->first, &_writing_set);
		}
		//_max_fd = _client_map.rbegin()->first;
	}

	void Dispatcher::setMax(int sock) {
		if (sock > _max_fd)
			_max_fd = sock;
	}


} // namespace ft
