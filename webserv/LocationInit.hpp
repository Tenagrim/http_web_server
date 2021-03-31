#pragma once
#include <iostream>
#include <list>
#include <string>
#include <Utils.hpp>
#include <map>

namespace ft
{

	static std::string LocationsKeyWord[] = {
			"alias",
			"limit_except",
			"client_max_body_size",
			"error_page",
			"autoindex",
			"index",
			"auth_basic"
	};

	class LocationInit
	{
	private:
		typedef std::list<std::string>							str_list;
		typedef std::list<std::string>::iterator 				str_list_it;
		typedef std::list<std::string>::reverse_iterator 		str_list_reit;
		typedef	std::map<std::string, std::list<std::string> >	argument_map;

		unsigned int	_id;
		std::string 	_path;
		argument_map 	_locations_arguments;
	public:
		LocationInit(int id);
		~LocationInit();

		bool InitParse(std::list<std::string> &list);

		void pathParse(std::list<std::string> &list);

		bool openBracket(std::list<std::string> &list);

		bool argumentParse(std::list<std::string> &list);


		unsigned int getId() const;

		const std::string &getPath() const;

		const argument_map &getLocationsArguments() const;

		bool findKeyWord(std::list<std::string> &list);
	};
}

