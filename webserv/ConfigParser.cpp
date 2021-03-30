#include "ConfigParser.hpp"

ft::ConfigParser::ConfigParser(): _tokenPool(), _server_count(0) {

	openConfigFile();
	if (!initParsing())
		throw std::runtime_error("Can't Read Config File ... ");
	if (!startParse())
		throw std::runtime_error("Mistake in config file...");
}

ft::ConfigParser::~ConfigParser() {
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
	if (it == _conf.end()) {
		state = true;
	}
	_confile.unique();
	std::list<std::string>::iterator lit = _confile.begin();
	for (; lit != _confile.end(); ++lit) {
		std::cout<<">"<<*lit<<"<";
	}
	std::cout<<"\n";
	return state;
}

void ft::ConfigParser::openConfigFile(void)
{
	std::ifstream fin("./conf/mywebserv.conf");
	if (!fin.is_open())
		throw std::runtime_error("Can not open file ....");
	std::getline(fin, _conf, '\0');
}

bool ft::ConfigParser::startParse(void)
{
	bool state = false;
	iterator it = _confile.begin();
	it = is_Space(it);
	if (*it == "server") {
		iterator end = findInList(_confile, ++it, "server");
		if (end == _confile.end())
			std::cout<<"1\n";
		else
			std::cout<<"2\n";
		std::list<std::string> *new_list = listCutter(_confile, it, end);

		std::cout<<*end<<std::endl;
		state = serverParse(it);
	} else {
		throw std::runtime_error("No Main key-word... \"SERVER\"");
	}
	return state;
}

bool ft::ConfigParser::serverParse(iterator it)
{
	bool state = false;
	++it;
	it = is_Space(it);
	if (*it == "{") {
		state = InitServer(it);
	} else {
		throw std::runtime_error("No Open Bracket....");
	}
	return state;
}

bool ft::ConfigParser::InitServer(iterator it)
{
	bool state = false;
	ServerInit *newServer = new ServerInit();
	std::list<std::string> tmp = copyContent(it, "server");
	_server_list.push_back(newServer);
	newServer->setId(_server_count);
	_server_count++;
	state = newServer->parseInServer(tmp);
	return state;
}

ft::ConfigParser::iterator ft::ConfigParser::is_Space(ft::ConfigParser::iterator it)
{
	while (*it == " " || *it == "\t" || *it == "\n" || *it == "\r")
		++it;
	return it;
}

std::list<std::string> ft::ConfigParser::copyContent(ft::ConfigParser::iterator it, std::string const &stop)
{
	iterator start = it;
	while ((*it != stop) && (it != _confile.end()))
		++it;
	iterator end = it;
	std::list<std::string> content_list;
	content_list.assign(start, end);
	return content_list;
}
