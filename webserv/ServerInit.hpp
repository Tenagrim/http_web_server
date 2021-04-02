#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <list>
#include <map>
#include <Utils.hpp>
#include <LocationInit.hpp>

namespace ft {
	class ServerInit {
	private:
		typedef std::string							string;
		typedef std::list<std::string>::iterator	iterator;
		typedef std::list<int>::iterator			iterator_num;
		typedef std::list<std::string>				list;
		typedef std::list<int>						list_num;

		unsigned int			_id;
		unsigned int			_location_count;
		list_num				_listen;
		list					_server_name;
		std::string				_root;
		std::list<LocationInit *> _locations;


		bool findServerName(list *tmp);
		bool findListen(list *tmp);
		bool findRoot(std::list<std::string> *tmp);

		iterator findInList(list *_list,std::string const &string);
		void getConf(std::list<std::string> &list);
		iterator is_Space(iterator it);
		bool is_digit(string const &str);
		bool findLocations(list *tmp);
	public:
		ServerInit(int id);
		~ServerInit();

		bool parseInServer(std::list<std::string> &tmp);


		void setId(unsigned int id);
		////// Sorry, i need getters /////////////
		unsigned int getId() const;
		unsigned int getLocationCount() const;
		std::list<int>					&getListenPorts(void);
		std::list<std::string>			&getServerNames(void);
		std::list<LocationInit *>		&getLocationInits(void);

		const string &getRoot() const;
	};
}