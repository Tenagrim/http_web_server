#pragma once
#include <string>

namespace ft
{
	enum HeaderType
	{
		some_type,
		some_another_type
	};

	enum MessageType
	{
		request,
		response
	};

	class IHeader
	{
	public:
		virtual std::string		str(void) = 0;
		virtual char			*c_str(void) = 0;
		virtual HeaderType		getType(void) = 0;

		virtual ~IHeader(){}
	};
}