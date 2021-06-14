#include "ConfigParser.hpp"

ft::ConfigParser::ConfigParser(): _tokenPool(), _server_count(0), _confile(0), _conf(), _server_list(0) {
}

ft::ConfigParser::~ConfigParser() {
	if (!_confile.empty()){
		_confile.clear();
	}
	std::list<ServerInit *>::iterator it = _server_list.begin();
	for (; it != _server_list.end(); it++) {
		delete *it;
	}
	_server_list.clear();
}

bool ft::ConfigParser::initParsing(void) {
	bool state = false;
	std::string buff;
	_confile.clear();
	for (size_t i = 0; i < _conf.size(); i++) {
		if (_tokenPool.checkInPool(_conf[i])){
			if (!buff.empty()) {
				_confile.push_back(buff);
				buff.clear();
			}
			buff += _conf[i];
		} else {
			if (_tokenPool.checkInPool(buff.front())) {
				_confile.push_back(buff);
				buff.clear();
			}
			buff += _conf[i];
		}
	}
	buff.clear();
	_confile.unique();
	state = true;
	return state;
}

void ft::ConfigParser::openConfigFile(const char *config)
{
	std::string path = config;
	_conf = ft::readFileIntoString4(path);
	if (_conf.empty())
		_conf = ft::readFileIntoString4("./conf/mywebserv.conf");
	if (_conf.empty())
		throw ft::runtime_error("Can not open file or default config is wrong....");
}

bool ft::ConfigParser::startParse(void)
{
	bool state = false;
	_confile.pop_front();
	iterator start = _confile.begin();
	if (!_confile.empty())
		ft::deleteCommit(_confile);
	while (start != _confile.end()){
		start = std::find(_confile.begin(), _confile.end(), "server");
		if (*start != "server" && _server_count == 0) {
			throw std::runtime_error("No one Server");
			break;
		}
		else if (start != _confile.end()){
			_confile.pop_front();
			iterator end = std::find(++start, _confile.end(), "server");
			if (*end != "server") {
				end = _confile.end();
			}
			std::list<std::string> server_part;
			server_part.splice(server_part.begin(), _confile, _confile.begin(), end);
			state = findServer(server_part);
			_server_count++;
		}
	}
	return state;
}

bool ft::ConfigParser::findServer(std::list<std::string> &_list)
{
	bool state = false;
	_list = isSpace(_list);
	if (_list.front() != "{"){
		throw std::runtime_error("No Open Bracket after SERVER key word...");
	}
	_list = isSpaceRev(_list);
	if (_list.back() != "}") {
			throw std::runtime_error("No ft_close Bracket ...");
	}
	state = initServer(_list);
	return state;
}

bool ft::ConfigParser::initServer(std::list<std::string> &tmp)
{
	bool state = false;
	ServerInit *newServer = new ServerInit(_server_count);
	_server_list.push_back(newServer);
	newServer->setId(_server_count);
	state = newServer->parseInServer(tmp);
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

void ft::ConfigParser::firstStep(int ac, char **av)
{
	if (ac == 2)
		openConfigFile(av[1]);
	else
		openConfigFile("./conf/mywebserv.conf");
	if (!initParsing())
		throw ft::runtime_error("Can't Read Config File ... ");
	if (!startParse())
		throw ft::runtime_error("Mistake in config file...");
	if (!checkConfig())
		throw ft::runtime_error("In config file you have duplicate construct...");
}
