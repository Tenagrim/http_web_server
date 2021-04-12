#pragma once
#include <string>
#include <list>
#include <map>
#include <algorithm> // For std::find
#include <unistd.h> // For pipe;
#include <iostream>

namespace ft
{
		typedef std::string			value;
		typedef std::list<value>::iterator iterator;
		typedef std::list<std::string>::reverse_iterator reverse_iterator;

		std::list<std::string> *findAndCut(std::list<std::string> &_list, const std::string &_str);
		std::list<std::string> &findAndErase(std::list<std::string> &_list,const std::string &_start,const std::string
		&_end);
		void deleteCommit(std::list<std::string> &list);
		iterator &isSpace(iterator &it);
		reverse_iterator &isSpace(reverse_iterator &it);

		std::list <std::string> & isSpace(std::list <std::string> &it);
		std::list <std::string> & isSpaceRev(std::list <std::string> &it);

		int temporaryBody(std::string const &str);
}
