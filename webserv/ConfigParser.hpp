#pragma once
#include <fstream>
#include <exception>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <list>
#include <map>
#include <ServerInit.hpp>

static char tokenPool[] = " {};/\t\n\r:";

namespace ft {
	class ConfigParser {
	private:
		unsigned int			_server_count;
		std::list<std::string> _confile;
		std::string		_conf;
		std::list<ServerInit *> _server_list;
		std::map<std::string, std::string>	_conf_param;
		typedef std::list<std::string>::iterator iterator;
	public:
		ConfigParser();
		~ConfigParser();

		void openConfigFile(void);
		bool initParsing(void);
		bool startParse(void);
		bool serverParse(iterator it);
		bool InitServer(iterator it);


		iterator is_Space(iterator it);
		std::list<std::string> copyContent(iterator it, std::string const &stop);
	};
}
