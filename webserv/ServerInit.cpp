#include <ServerInit.hpp>
#include "ServerInit.hpp"

ft::ServerInit::ServerInit(): _id(0) {
}

ft::ServerInit::~ServerInit() {
}

bool ft::ServerInit::parseInServer(std::list<std::string> tmp)
{
	bool state = false;
	iterator it = tmp.begin();
	ft::deleteCommit(tmp);
	std::cout<<"\n";
	state = findListen(&tmp);
	state = findServerName(&tmp);
	state = findLocations(&tmp);
	std::cout<<string(30, '*')<<std::endl;
	getConf();
	return state;
}

unsigned int ft::ServerInit::getId() const { return _id; }

void ft::ServerInit::setId(unsigned int id) { _id = id; }

ft::ServerInit::iterator ft::ServerInit::is_backSpace(ft::ServerInit::iterator it)
{
	while (*it == " " || *it == "\t" || *it == "\n" || *it == "\r")
		--it;
	return it;
}

ft::ServerInit::iterator ft::ServerInit::findInList(ft::ServerInit::list *_list,std::string const &string)
{
	iterator begin = _list->begin();
	iterator end = _list->end();
	for (; begin != end; ++begin) {
		if (*begin == string)
			return begin;
	}
	return end;
}

bool ft::ServerInit::findListen(ft::ServerInit::list *tmp)
{
	bool state = false;
	iterator it = tmp->begin();
	it = findInList(tmp,"listen");
	if (it == tmp->end())
		throw std::runtime_error("No key-word \"LISTEN\"");
	while (*it != ";" || it == tmp->end()) {
		if (*it == "\n") break;
		it = is_Space(++it);
		if (!is_digit(*it))
			throw std::runtime_error("Argument in LISTEN is not a digit...");
		int i = std::stoi(*it);
		_listen.push_back(i);
		++it;
	}
	if (*it != ";") {
		throw std::runtime_error("No \";\" after key-word LISTEN");
	} else
		state = true;
//	Удаление обработоанной строки
	*tmp = ft::findAndErase(*tmp, "listen", ";");
	return state;
}

void ft::ServerInit::getConf()
{
	if (!_listen.empty()) {
		for(iterator_num it = _listen.begin(); it != _listen.end(); ++it) {
			std::cout<<*it;
		}
		std::cout<<"\n";
	}
	if (!_server_name.empty()) {
		for (iterator it = _server_name.begin(); it != _server_name.end(); ++it) {
			std::cout<<*it;
		}
		std::cout<<"\n";
	}
}

ft::ServerInit::iterator ft::ServerInit::is_Space(iterator it)
{
	while (*it == " " || *it == "\t")
		++it;
	return it;
}

bool ft::ServerInit::is_digit(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

bool ft::ServerInit::findServerName(list *tmp)
{
	bool state = false;
	iterator it = tmp->begin();
	it = findInList(tmp,"server_name");
	if (it == tmp->end())
		throw std::runtime_error("No key-word \"SERVER_NAME\"");
	while (*it != ";" || it == tmp->end()) {
		if (*it == "\n") break;
		it = is_Space(++it);
		_server_name.push_back(*it);
		++it;
	}
	if (*it != ";") {
		throw std::runtime_error("No \";\" after key-word SERVER_NAME");
	} else
		state = true;
	//	Удаление обработоанной строки
	*tmp = ft::findAndErase(*tmp, "server_name", ";");
	return state;
}

bool ft::ServerInit::findLocations(ft::ServerInit::list *tmp)
{
	bool state = false;
	iterator it = tmp->begin();
	it  = findInList(tmp, "location");
	++it;
	if (it == tmp->end())
		throw std::runtime_error("No key-word \"LOCATIONS\"");
	list locations = copyContent(*tmp, it, "location");
	iterator loc_it = locations.begin();
	for (; loc_it != locations.end(); ++loc_it) {
		std::cout<<*loc_it;
	}
	std::cout<<"\n";
//	std::list<std::string> *location = ft::findAndCut(*tmp, "location");
//	iterator loc_it = location->begin();
//	for (; loc_it != location->end(); ++loc_it) {
//		std::cout<<*loc_it;
//	}
//	std::cout<<"\n";
	return true;
}

std::list<std::string> ft::ServerInit::copyContent(list &tmp, ft::ServerInit::iterator it, const std::string &stop)
{
	iterator start = it;
	while ((*it != stop) && (it != tmp.end()))
		++it;
	iterator end = it;
	std::list<std::string> content_list;
	content_list.assign(start, end);
	return content_list;
}

void ft::ServerInit::parseInfoLine(std::list<std::string> &tmp)
{
	iterator it = tmp.begin();
}
