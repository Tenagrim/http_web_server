#include <Utils.hpp>

namespace ft {
	std::list<std::string> *findAndCut(std::list<std::string> &_list, std::string const &_str) {
		iterator it = ++_list.begin();
//	TODO:   make correct splice with last element
		iterator it_new = std::find(++it, _list.end(), _str);
		std::list<std::string> *tmp = new std::list<std::string>;
		tmp->splice(tmp->begin(), _list, ++it, it_new);
		return tmp;
	}

	std::list<std::string> &findAndErase(std::list<std::string> &_list,const std::string &_start,const std::string
	&_end) {
		iterator start = std::find(_list.begin(), _list.end(), _start);
		iterator end = std::find(start, _list.end(), _end);
		_list.erase(start, ++end);
		return _list;
	};

	void deleteCommit(std::list<std::string> &list) {
		bool res = true;
		while(res) {
			iterator it = std::find(list.begin(), list.end(), "#");
			if (*it == "#")
				ft::findAndErase(list, "#", "\n");
			else
				res = false;
		}
	};

	iterator &isSpace(iterator &it) {
		while (*it == " " || *it == "\t" || *it == "\n")
			++it;
		return it;
	};

	reverse_iterator &isSpace(reverse_iterator &it) {
		while (*it == " " || *it == "\t" || *it == "\n")
			++it;
		return it;
	};
}