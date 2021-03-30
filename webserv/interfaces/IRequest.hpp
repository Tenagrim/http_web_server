#pragma once
#include <string>
#include <map>
#include <ostream>

namespace ft
{
	class IRequest
	{
	public:
		virtual std::string				&getHeaderValue(std::string const &header) = 0;
		virtual std::map<std::string, std::string> &getHeaders(void) = 0;
		virtual std::string				&getMethod(void) = 0; // GET / POST
		virtual std::string				&getURI(void) = 0;
		virtual std::string				&getHTTPVersion(void) = 0;
		virtual std::string				&getText(void) = 0;
		virtual std::string				to_string(void) const = 0;

		virtual ~IRequest(){};
	};
	std::ostream			&operator<<(std::ostream &os, const IRequest &ref);
}
