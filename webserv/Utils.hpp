#pragma once
#include <string>
#include <list>
#include <map>
#include <algorithm> // For std::find
#include <unistd.h> // For pipe;
#include <iostream>

namespace ft
{
		typedef std::string							value;
		typedef std::list<value>					list;
		typedef std::list<value>::iterator			iterator;
		typedef std::list<value>::reverse_iterator	reverse_iterator;

		list				*findAndCut(list &_list, const value &_str);
		list				&findAndErase(list &_list, const value &_start, const value &_end);
		void				deleteCommit(std::list<value> &list);
		iterator			&isSpace(iterator &it);
		reverse_iterator	&isSpace(reverse_iterator &it);

		int					temporaryBody(value const &str);

		int					get_next_line(int fd, char **line);

}
