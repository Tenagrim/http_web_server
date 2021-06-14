#pragma once
#include <map>
#include <IRequestReciever.hpp>
#include <sys/select.h> // For select
#include <queue>

//class Dispatcher;
namespace ft
{
class Server;
}
#include <src/core/Server.hpp>
#include <webserv.hpp>
#include <stack>
#include <RequestReceiver.hpp>
#include <src/core/DispatcherEventArgs.hpp>
#include <BodyReader.hpp>
#include <defines.hpp>

namespace ft
{
	class Dispatcher
	{
	private:
		typedef std::map<int, RequestReceiver *> fd_map;
		fd_map					_listener_map;
		fd_map					_client_map;

		std::list<int>			_socks_to_close;
		unsigned int 			_delay;
	//	td::map<int, Server *>			_listener_map;
	//	td::map<int, Server *>				_client_map;
		
		fd_set					_fd_set;
		fd_set					_reading_set;
		fd_set					_writing_set;
		struct timeval			_upd_delay;
		int						_events;
		unsigned int			_listening;
		int						_max_fd;
		Server					*_server;
		bool					_run;


		void					handleListeners();
		void					handleClients();
		void					handleClientsRead();
		void					handleClientsWrite();
		void					closeWhatNeed();
		void					reallyCloseSock(int sock);
		void 					wakeUp();
		void 					sleep();
		void 					killZombies();
		void 					initFdSets();
		void 					setMax(int sock);
		Dispatcher(const Dispatcher &ref);
	public:
		Dispatcher();
		~Dispatcher();
		Dispatcher		&operator=(const Dispatcher &ref);
/*
		void			addListener(ft::Server *serv);			// LEGACY SHIT
		void			addClient(ft::Server *serv, int sock);	// LEGACY SHIT

		void			addListener(int sock);
		void			addClient(int sock);
	*/	
		void			addListener(RequestReceiver *recv, int sock);
		void			addClient(RequestReceiver *recv, int sock);

		void			closeSock(int sock);
		void			updateEvents();
		void			handleEvents();

		void			connectToServer(Server *serv);

		void			start(void);
		void			stop(void);

	};


}