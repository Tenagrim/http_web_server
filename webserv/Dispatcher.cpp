#include <Dispatcher.hpp>
#include <Server.hpp>

namespace ft
{
	Dispatcher::Dispatcher() : _listener_map()
	{
		_upd_delay.tv_usec = UPDATE_DELAY % 1000;
		_upd_delay.tv_sec = UPDATE_DELAY / 1000;
		_listening = 0;
		FD_ZERO(&_fd_set);
		_max_fd = 0;
	}

	Dispatcher::~Dispatcher()
	{
	}

	void Dispatcher::addListener(Server *serv)
	{
		int sock = serv->getListenFd();
		_listener_map[sock] = serv;
		if (sock > _max_fd)
			_max_fd = sock;
		FD_SET(sock, &_fd_set);
		_listening++;
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



	void			Dispatcher::updateFdSet()
	{

		_events = 0;
		if (_listening == 0)
			throw std::runtime_error("No have fd to dispatch");
		ft_memcpy(&_reading_set, &_fd_set, sizeof(_fd_set));
		FD_ZERO(&_writing_set);
		if (_client_map.size() == 0)
			_events = select(_max_fd, &_reading_set, NULL, NULL, &_upd_delay);
		else
			_events = select(_max_fd, &_reading_set, &_writing_set, NULL, &_upd_delay);

	}

	Dispatcher::Dispatcher(const Dispatcher &ref)
	{
		
	}

	Dispatcher &Dispatcher::operator=(const Dispatcher &ref)
	{
		return (*this);
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

		fd_map::iterator it;
		for(it = _client_map.begin();it != _client_map.end() ;it++)
		{
			if (FD_ISSET((*it).first, &_reading_set))
				(*it).second->readEvent((*it).first);
		}
		for(it = _client_map.begin();it != _client_map.end() ;it++)
		{
			if (FD_ISSET((*it).first, &_writing_set))
				(*it).second->writeEvent((*it).first);
		}
	}
} // namespace ft