#include <ServerInit.hpp>
//#include "ServerInit.hpp"

ft::ServerInit::ServerInit(int id): _id(id), _location_count(0) {
}

ft::ServerInit::~ServerInit() {
//	TODO; Double Free
	std::list<LocationInit *>::iterator it = _locations.begin();
	for (; it != _locations.end(); ++it) {
		delete *it;
	}
	_locations.clear();
}

bool ft::ServerInit::parseInServer(std::list<std::string> &tmp)
{
	bool state = false;
	ft::deleteCommit(tmp);
	state = findListen(&tmp);
	state = findServerName(&tmp);
	state = findRoot(&tmp);
	state = findLocations(&tmp);
	std::cout<<string(30, '*')<<std::endl;
	getConf(tmp);
	return state;
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

bool ft::ServerInit::findRoot(std::list<std::string> *tmp)
{
	bool state = false;
	iterator it = tmp->begin();
	it = std::find(it, tmp->end(), "root");
	if (*it != "root")
		throw std::runtime_error("No \"ROOT\" key-word");
	else{
		iterator end = std::find(it, tmp->end(), "\n");
		std::list<std::string> *root = new std::list<std::string>;
		root->splice(root->begin(), *tmp, it, end);
		root->pop_front();
		iterator rit = root->begin();
		rit = is_Space(rit);
		reverse_iterator rev_it = root->rbegin();
		rev_it = isSpace(rev_it);
		if (*(rev_it) != ";")
			throw std::runtime_error("no \";\" after key-word ROOT");
		_root = *rit;
		if (_root.empty() || _root == ";")
			throw std::runtime_error("nothing in root path");
		delete root;
	}
	return state;
}

void ft::ServerInit::getConf(std::list<string> &list)
{

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

bool ft::ServerInit::findLocations(std::list<std::string> *tmp)
{
	bool state = false;
	iterator start = tmp->begin();

	while (start != tmp->end()){
		start = std::find(tmp->begin(), tmp->end(), "location");
		if (*start != "location" && _location_count == 0) {
			throw std::runtime_error("No one LOCATION");
			break;
		}
		else if (start != tmp->end()){
			tmp->erase(start);
			iterator end = std::find(++start, tmp->end(), "location");
			std::list<std::string> *location = new std::list<std::string>;
			location->splice(location->begin(), *tmp, ++start, end);
			LocationInit *Location = new LocationInit(_location_count);
			_locations.push_back(Location);
			_location_count++;
			state =  Location->InitParse(*location);
		}
	}
	return state;
}

std::list<int>					&ft::ServerInit::getListenPorts(void)
{
	return _listen;
}

std::list<ft::LocationInit *>		&ft::ServerInit::getLocationInits(void)
{
	return _locations;
}
std::list<std::string>			&ft::ServerInit::getServerNames(void)
{
	return _server_name;
}

unsigned int ft::ServerInit::getId() const { return _id; }

void ft::ServerInit::setId(unsigned int id) { _id = id; }

unsigned int ft::ServerInit::getLocationCount() const
{
	return _location_count;
}

const std::string &ft::ServerInit::getRoot() const
{
	return _root;
}

