#pragma once
#include <map>
#include <IRequestReciever.hpp>
#include <sys/select.h> // For select

//class Dispatcher;
namespace ft
{
class Server;
}
#include <Server.hpp>
#include <webserv.hpp>

#define UPDATE_DELAY 1000

namespace ft
{


	struct Dispatcher_event_args
	{
		int					_fd;
		disp_event_type		_type;

		Dispatcher_event_args(int __fd, disp_event_type __type) : _fd(__fd), _type(__type){}
	};
	
	enum disp_event_type
	{
		reading,
		writing,
		timeout
	};

	class Dispatcher
	{
	private:
		typedef std::map<int, Server *>	fd_map;
		fd_map					_listener_map;
		fd_map					_client_map;
	//	td::map<int, Server *>			_listener_map;
	//	td::map<int, Server *>				_client_map;
		
		fd_set					_fd_set;
		fd_set					_reading_set;
		fd_set					_writing_set;
		struct timeval			_upd_delay;
		int						_events;
		unsigned int			_listening;
		int						_max_fd;

	public:
		Dispatcher();
		~Dispatcher();
		Dispatcher(const Dispatcher &ref);
		Dispatcher		&operator=(const Dispatcher &ref);
		void			addListener(ft::Server *serv);
		void			addClient(ft::Server *serv, int sock);
		void			removeSock(int sock);
		void			updateFdSet();
		void			handleEvents();
	};


}