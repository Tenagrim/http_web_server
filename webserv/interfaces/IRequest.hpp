#pragma once
#include <string>

class IRequest
{
	public:
	virtual std::string	getHeaderValue(std::string const &header) = 0;	
};

