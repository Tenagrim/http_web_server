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
		virtual std::string		str(void) const = 0;
		virtual char			*c_str(void) const = 0;
		virtual HeaderType		getType(void) const = 0;

		virtual ~IHeader(){}
	};
}

std::ostream			&operator<<(std::ostream &os, const ft::IHeader &ref);