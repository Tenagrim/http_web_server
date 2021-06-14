#pragma once
#include <string>
#include <ILoggerEvent.hpp>

namespace ft
{
	class ILogger
	{
	public:
		virtual int logString(std::string const &str) = 0;
		virtual int logEvent(ILoggerEvent const &event) = 0;

		virtual ~ILogger(){}
	};
}