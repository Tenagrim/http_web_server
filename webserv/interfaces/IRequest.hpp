#pragma once
#include <string>
#include <map>
#include <ostream>

class IRequest
{
	public:
	virtual std::string							&getHeaderValue(std::string const &header) = 0;	
	virtual std::map<std::string, std::string>	&getHeaders(std::string const &header) = 0;	
	virtual std::string							&getMethod(void) = 0;	// GET / POST
	virtual std::string							&getURI(void) = 0;
	virtual std::string							&getText(void) = 0;

};

