#include "ConfigParser.hpp"

ft::ConfigParser::ConfigParser(): _tokenPool(), _server_count(0) {

	openConfigFile();
	if (!initParsing())
		throw ft::runtime_error("Can't Read Config File ... ");
	if (!startParse())
		throw ft::runtime_error("Mistake in config file...");
}

ft::ConfigParser::~ConfigParser() {
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
	if (it == _conf.end()) {
		state = true;
	}
	_confile.unique();
//	std::list<std::string>::iterator lit = _confile.begin();
//	for (; lit != _confile.end(); ++lit) {
//		std::cout<<">"<<*lit<<"<";
//	}
//	std::cout<<"\n";
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
	iterator it = _confile.begin();
	it = isSpace(it);
	if (*it == "server") {
		state = findServer(_confile, "server");
	} else {
		throw ft::runtime_error("No Main key-word... \"SERVER\"");
	}
	return state;
}

bool ft::ConfigParser::initServer(std::list<std::string> *tmp)
{
	bool state = false;
	ServerInit *newServer = new ServerInit();
	_server_list.push_back(newServer);
	newServer->setId(_server_count);
	_server_count++;
	state = newServer->parseInServer(*tmp);
	return state;
}

bool ft::ConfigParser::findServer(std::list<std::string> &_list, std::string _str)
{
	bool state = false;
	std::list<std::string> *tmp = ft::findAndCut(_list,_str);
	iterator count = tmp->begin();
	reverse_iterator recount = tmp->rbegin();
	count = isSpace(count);
	recount = isSpace(recount);
	if (*count != "{")
		throw ft::runtime_error("No Open Bracket ...");
	if (*recount != "}")
		throw ft::runtime_error("No Close Bracket ...");
	for (; count != tmp->end(); ++count){
		std::cout<<*count;
	}
	std::cout<<"\n";
	state = initServer(tmp);
	delete tmp;
	return state;
}
