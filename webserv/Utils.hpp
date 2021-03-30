#pragma once
#include <string>
#include <list>
#include <map>

namespace ft
{
		typedef std::string			value;
		typedef std::list<value>	list;
		typedef std::list<value>::iterator iterator;
		list *listCutter(list _list, iterator _begin, iterator _end);
		iterator findInList(list _list, iterator _begin, const std::string &str);
}