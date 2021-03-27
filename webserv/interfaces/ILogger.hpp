#pragma once
#include <string>
#include <ILoggerEvent.hpp>
class ILogger
{
	public:
		virtual int		logString(std::string const &str) = 0;
		virtual int		logEvent(ILoggerEvent const &event) = 0;
};