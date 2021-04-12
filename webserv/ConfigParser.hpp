#include <__bit_reference>

#pragma once
#include <fstream>
#include <algorithm>
#include <exception>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <list>
#include <map>
#include <ServerInit.hpp>
#include <TokenPool.hpp>
#include <Utils.hpp>
#include <webserv.hpp>

namespace ft {
	class ConfigParser {
	private:
		TokenPool				_tokenPool;
		int			_server_count;
		std::list<std::string>	_confile;
		std::string				_conf;
		std::list<ServerInit *> _server_list;

		typedef std::list<std::string>::iterator iterator;
		typedef std::list<std::string>::reverse_iterator reverse_iterator;
		void openConfigFile(const char *config);
		bool initParsing(void);
		bool startParse(void);
		bool initServer(std::list<std::string> &tmp);
		bool findServer(std::list<std::string> &_list);
	public:
		ConfigParser();
		~ConfigParser();

		void firstStep (int ac, char *av[]);
		unsigned int getServerCount() const;
		const std::list<ServerInit *> &getServerList() const;
		bool checkConfig();

		int checkHostname(ServerInit *server);

		int checkPorts(ServerInit *server);

		void checkPortsOnUniq(std::list<int> *pList);

		void checkHostnameOnUniq(std::list<std::string> *pList);

	};
}
