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
	iterator back = is_backSpace(--(tmp.end()));
	if (*back != ";")
		throw std::runtime_error("No \"}\"");
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