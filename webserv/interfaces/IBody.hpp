#pragma once
#include <string>

namespace ft
{
	enum BodyType
	{
		file,
		pipe,
		cgi_input

		// maybe more
	};

	class IBody
	{
	public:
		// opens file descriptor to data
		virtual bool				getFd(void) = 0;

		// returns string wich containing data BY VALUE (DANGER!!!  MAY CAUSE STACK OVERFLOW)
		virtual std::string			str(void) = 0;

		// returns pointer to alllocated c-style string with \0 at end
		virtual char				*c_str(void) = 0;

		// returns size of data
		virtual unsigned int		size(void) = 0;

		virtual BodyType			getType(void) = 0;

		virtual ~IBody(){}
	};
}