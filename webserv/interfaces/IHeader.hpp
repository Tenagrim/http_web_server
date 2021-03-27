#pragma once
#include <string>
class IHeader
{
public:
	virtual std::string		str(void) = 0;
	virtual char			*c_str(void) = 0;
};