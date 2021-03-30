#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <list>

namespace ft {
	class ServerInit {
	private:
		unsigned int			_id;
		std::list<std::string>	_listen;
		std::list<std::string>	_server_name;
//		std::list<LocationInit *> _locations;

		typedef std::list<std::string>::iterator iterator;
	public:
		ServerInit();
		~ServerInit();

		unsigned int getId() const;
		void setId(unsigned int id);

		bool parseInServer(std::list<std::string> tmp);
		iterator is_backSpace(iterator it);
	};
}