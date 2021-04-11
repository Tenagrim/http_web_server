#include <ConfigParser.hpp>

ft::ConfigParser::ConfigParser(): _tokenPool(), _server_count(0), _confile(), _conf() {

	openConfigFile();
	if (!initParsing())
		throw ft::runtime_error("Can't Read Config File ... ");
	if (!startParse())
		throw ft::runtime_error("Mistake in config file...");
	if (!checkConfig())
		throw ft::runtime_error("In config file you have duplicate construct...");
}

ft::ConfigParser::~ConfigParser() {
	if (!_confile.empty()){
		_confile.clear();
	}
	std::list<ServerInit *>::iterator it = _server_list.begin();
	for (; it != _server_list.end(); ++it) {
		delete *it;
	}
	_server_list.clear();
}

bool ft::ConfigParser::initParsing(void) {
	bool state = false;
	std::string line = " ";
	std::string::iterator it = _conf.begin();
	for (; it != _conf.end(); ++it) {
		if(_tokenPool.checkInPool(*it)) {
			if (!line.empty()){
				_confile.push_back(line);
				line.clear();
			}
			line.push_back(*it);
		} else {
			if (_tokenPool.checkInPool(*(line.begin()))) {
				_confile.push_back(line);
				line.clear();
			}
			line.push_back(*it);
		}
	}
	line.clear();
	if (it == _conf.end()) {
		state = true;
	}
	_confile.unique();
	return state;
}

void ft::ConfigParser::openConfigFile(void)
{
	std::ifstream fin("./conf/mywebserv.conf");
	if (!fin.is_open())
		throw ft::runtime_error("Can not open file ....");
	std::getline(fin, _conf, '\0');
}

bool ft::ConfigParser::startParse(void)
{
	bool state = false;
	iterator start = _confile.begin();

	while (start != _confile.end()){
		start = std::find(_confile.begin(), _confile.end(), "server");
		if (*start != "server" && _server_count == 0) {
			throw std::runtime_error("No one Server");
			break;
		}
		else if (start != _confile.end()){
			iterator it = _confile.begin();
			it = isSpace(it);
			_confile.erase(start);
			state = findServer(_confile, ++start);
			_server_count++;
		}
	}
	return state;
}

bool ft::ConfigParser::initServer(std::list<std::string> *tmp)
{
	bool state = false;
	ServerInit *newServer = new ServerInit(_server_count);
	_server_list.push_back(newServer);
	newServer->setId(_server_count);
	state = newServer->parseInServer(*tmp);
	return state;
}

bool ft::ConfigParser::findServer(std::list<std::string> &_list, iterator &start)
{
	bool state = false;

	std::list<std::string> *tmp = new std::list<std::string>;
	iterator end = std::find(start, _list.end(), "server");
	if (*end != "server") {
		reverse_iterator r_end = std::find(_list.rbegin(), _list.rend(), "}");
		++r_end;
		r_end = std::find(_list.rbegin(), _list.rend(), "}");
		end = r_end.base();
	}
	tmp->splice(tmp->begin(), _list, start, end);
	state = initServer(tmp);
	iterator count = tmp->begin();
	reverse_iterator recount = tmp->rbegin();
	count = isSpace(count);
	recount = isSpace(recount);
	if (*count != "{")
		throw std::runtime_error("No Open Bracket after SERVER key word...");
	if (*recount != "}")
		throw std::runtime_error("No ft_close Bracket ...");
	delete tmp;
	return state;
}

unsigned int ft::ConfigParser::getServerCount() const
{
	return _server_count;
}

const std::list<ft::ServerInit *> &ft::ConfigParser::getServerList() const
{
	return _server_list;
}

bool ft::ConfigParser::checkConfig()
{
	bool res = false;
	std::list<ServerInit *>::iterator it = _server_list.begin();
	while (it != _server_list.end()) {
		ServerInit *server = it.operator*();
		int i = checkHostname(server);
		int y = checkPorts(server);
		if (i + y == 2){
			res = false;
			break;
		}
		res = true;
		++it;
	}
	return res;
}

int ft::ConfigParser::checkHostname(ft::ServerInit *server)
{
	int i = 0;
	std::list<int> *list = &server->getListenPorts();
	checkPortsOnUniq(list);
	std::list<int>::iterator it = list->begin();
	std::list<ServerInit *>::iterator sit = _server_list.begin();
	for (; sit != _server_list.end(); ++sit) {
		if (server == sit.operator*()){ break; }
		else {
			std::list<int> list2 = (*sit)->getListenPorts();
			std::list<int>::iterator it2 = list2.begin();
			for (; it != list->end(); ++it){
				it2 = list2.begin();
				for(; it2 != list2.end(); ++it2) {
					if (*it == *it2)
						i = 1;
				}
			}
		}
	}
	return i;
}

int ft::ConfigParser::checkPorts(ft::ServerInit *server)
{
	int y = 0;
	std::list<std::string> *list = &server->getServerNames();
	checkHostnameOnUniq(list);
	std::list<std::string>::iterator it = list->begin();
	std::list<ServerInit *>::iterator sit = _server_list.begin();
	for (; sit != _server_list.end(); ++sit) {
		if (server == sit.operator*()){ break; }
		else {
			std::list<std::string> list2 = (*sit)->getServerNames();
			std::list<std::string>::iterator it2 = list2.begin();
			for (; it != list->end(); ++it){
				it2 = list2.begin();
				for(; it2 != list2.end(); ++it2) {
					if (*it == *it2)
						y = 1;
				}
			}
		}
	}
	return y;
}

void ft::ConfigParser::checkPortsOnUniq(std::list<int> *pList)
{
	if (!pList)
		throw ft::runtime_error("t::ConfigParser::checkPortsOnUniq - no list");
	int i = pList->size();
	pList->unique();
	int y = pList->size();
	if (i != y) {
		throw ft::runtime_error("Ports is not uniq");
	}
}

void ft::ConfigParser::checkHostnameOnUniq(std::list<std::string> *pList)
{
	if (!pList)
		throw ft::runtime_error("t::ConfigParser::checkHostnameOnUniq - no list");
	int i = pList->size();
	pList->unique();
	int y = pList->size();
	if (i != y) {
		throw ft::runtime_error("Hostnames is not Uniq");
	}
}
