#include <Utils.hpp>

namespace ft {
	list *listCutter(list _list, iterator _begin, iterator _end) {
		list *tmp = new list;
		iterator it = _begin;
		for (; it != _end; ++it) {
			tmp->push_back(*it);
		}
		_list.erase(_begin, _end);
		return tmp;
	};
	iterator findInList(list _list, iterator _begin, const std::string &str) {
		iterator end = _list.end();
		for (;_begin != _list.end(); ++_begin) {
			if (*_begin == str)
				return _begin;
		}
		return end;
	}
}