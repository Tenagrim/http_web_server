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
	}
	Dispatcher::~Dispatcher()
	{
	}

	Dispatcher::Dispatcher(const Dispatcher &ref)
	{
		(void)ref;
		throw std::runtime_error("Not implemented");
	}

	Dispatcher &Dispatcher::operator=(const Dispatcher &ref)
	{
		(void)ref;
		throw std::runtime_error("Not implemented");
		return (*this);
	}
	#pragma endregion

	#pragma region Add_remove socks
	void Dispatcher::addListener(Server *serv)
	{
		int sock = serv->getListenSock();
		_listener_map[sock] = serv;
		if (sock > _max_fd)
			_max_fd = sock;
		FD_SET(sock, &_fd_set);
		_listening++;
			//#ifdef DEBUG
			//	std::cout << "DISPATCHER: SELECTIN..." << " " << "\n";
			//#endif
	}

	void Dispatcher::addClient(Server *serv, int sock)
	{
		_client_map[sock] = serv;
		if (sock > _max_fd)
			_max_fd = sock;
		FD_SET(sock, &_fd_set);
		_listening++;
	}

	void Dispatcher::removeSock(int sock)
	{
		if (_listener_map.count(sock))
		{
			_listener_map.erase(sock);
			if (sock == _max_fd)
				_max_fd = (*(_listener_map.end())).first;
		}
		else if (_client_map.count(sock))
		{
			_client_map.erase(sock);
			if (sock == _max_fd)
				_max_fd = (*(_client_map.end())).first;
		}
		else
			throw std::runtime_error("requested sock not found to delete it");

		_listening--;
	}

	#pragma endregion

	#pragma region Events

	void			Dispatcher::updateEvents()
	{
		#undef DEBUG


			#ifdef DEBUG
				static int i;
			
				std::cout << "DISPATCHER: UPDATE EVENTS ["<< i++ <<"] max fd: "<< _max_fd <<"\n";
				std::cout << "CLIENTS: \n";
				fd_map::iterator it = _client_map.begin();
				for(; it != _client_map.end(); it++)
					std::cout << "[" << (*it).first << "] ";
				std::cout << "\n";
				std::cout << "LISTENERS: \n";
				it = _listener_map.begin();
				for(; it != _listener_map.end(); it++)
					std::cout << "[" << (*it).first << "] ";
				std::cout << "\n";
			#endif
		_events = 0;
		if (_listening == 0)
			throw std::runtime_error("No have fd to dispatch");
		ft_memcpy(&_reading_set, &_fd_set, sizeof(_fd_set));
		ft_memcpy(&_writing_set, &_fd_set, sizeof(_fd_set));
		//FD_ZERO(&_writing_set);


			#ifdef DEBUG
				std::cout << "DISPATCHER: SELECTIN..." << " " << "\n";
			#endif
		if (_client_map.size() == 0)
			_events = select(_max_fd + 1, &_reading_set, NULL, NULL, &_upd_delay);
		else
			_events = select(_max_fd + 1, &_reading_set, &_writing_set, NULL, &_upd_delay);
			
			#ifdef DEBUG
				std::cout << "DISPATCHER: EVENTS UPDATET. GOT: " << _events << "\n";
			#endif

		#define DEBUG
	}


	void					Dispatcher::handleListeners(void)
	{
		fd_map::iterator it;
		for(it = _listener_map.begin();it != _listener_map.end() ;it++)
		{	
			if (FD_ISSET((*it).first, &_reading_set))
				(*it).second->gotEvent(Dispatcher_event_args((*it).first, reading, listener));
		}
	}

	void					Dispatcher::handleClientsRead(void)
	{
		fd_map::iterator it;
		for(it = _client_map.begin();it != _client_map.end() ;it++)
		{
			if (FD_ISSET((*it).first, &_reading_set))
				(*it).second->gotEvent(Dispatcher_event_args((*it).first, reading, client));
		}
	}

	void					Dispatcher::handleClientsWrite(void)
	{
		fd_map::iterator it;
		for(it = _client_map.begin();it != _client_map.end() ;it++)
		{
			if (FD_ISSET((*it).first, &_writing_set))
				(*it).second->gotEvent(Dispatcher_event_args((*it).first, writing, client));
		}
	}

	void					Dispatcher::handleClients(void)
	{
		handleClientsRead();
		handleClientsWrite();
	}

	void			Dispatcher::handleEvents()
	{
		if (_events == 0)
		{
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
} // namespace ft