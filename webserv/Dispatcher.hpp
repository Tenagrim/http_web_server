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
#include <stack>
#include <RequestReceiver.hpp>
#include <DispatcherEventArgs.hpp>
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

		std::stack<int>			_socks_to_ft_close;
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


		void					handleListeners(void);
		void					handleClients(void);
		void					handleClientsRead(void);
		void					handleClientsWrite(void);
		void					ft_closeWhatNeed();
		void					reallyCloseSock(int sock);
		void 					wakeUp();
		void 					sleep();
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

		void			ft_closeSock(int sock);
		void			updateEvents();
		void			handleEvents();

		void			connectToServer(Server *serv);

		void			start(void);
		void			stop(void);

	};


}