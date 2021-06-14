#pragma once
#include <string>

namespace ft
{
	class ILoggerEvent
	{
		public:
		virtual std::string str(void) = 0;

		virtual ~ILoggerEvent(){}
	};
}