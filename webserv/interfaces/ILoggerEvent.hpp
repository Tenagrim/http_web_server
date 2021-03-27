#pragma once
#include <string>
class ILoggerEvent
{
	virtual std::string		str(void) = 0;
};