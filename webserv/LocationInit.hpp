#pragma once
#include <iostream>
#include <list>
#include <string>
#include <Utils.hpp>
#include <map>
#include <algorithm>
#include <runtime_error.hpp>

namespace ft
{

	static const char *LocationsKeyWord[] = {
			"alias", "proxy_pass", "limit_except", "client_max_body_size", "error_page", "autoindex", "index",
			"auth_basic", "fastcgi_pass"
	};

	class LocationInit
	{
	private:
		typedef std::list<std::string>							str_list;
		typedef std::list<std::string>::iterator 				str_list_it;
		typedef std::list<std::string>::reverse_iterator 		str_list_reit;
		typedef	std::map<std::string, std::string>				argument_map;
		typedef argument_map::iterator 				iterator_map;

		unsigned int	_id;
		std::string 	_path;
		argument_map 	_locations_arguments;

		void pathParse(std::list<std::string> &list);

		bool openBracket(std::list<std::string> &list);

		bool argumentParse(std::list<std::string> &list);

		bool findKeyWord(std::list<std::string> &list);

		bool parseKeyWord(std::list<std::string> &list, std::list<std::string>::iterator &it);
	public:
		LocationInit(int id);
		~LocationInit();

		bool InitParse(std::list<std::string> &list);

//GETERS
		unsigned int getId() const;

		const std::string &getPath() const;

		const argument_map &getLocationsArguments();


	};
}

