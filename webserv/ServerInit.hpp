#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <list>
#include <map>

//#include <Utils.hpp>

namespace ft {
	static std::string tagsPool[] = {
			"listen",
			"server_name",
			"location"
	};

	class ServerInit {
	private:
		typedef std::string							string;
		typedef std::list<std::string>::iterator	iterator;
		typedef std::list<int>::iterator			iterator_num;
		typedef std::list<std::string>				list;
		typedef std::list<int>						list_num;

		unsigned int			_id;
		list_num				_listen;
		list					_server_name;
//		std::list<LocationInit *> _locations;


		bool findServerName(list *tmp);
		bool findListen(list *tmp);

	public:
		ServerInit();
		~ServerInit();

		unsigned int getId() const;
		void setId(unsigned int id);

		bool parseInServer(std::list<std::string> tmp);
		iterator is_backSpace(iterator it);
		iterator findInList(list *_list,std::string const &string);


		void getConf(void);
		iterator is_Space(iterator it);
		bool is_digit(string const &str);

		bool findLocations(list *tmp);
		std::list<std::string> copyContent(list &tmp,iterator it, std::string const &stop);

	};
}