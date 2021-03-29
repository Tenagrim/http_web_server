#pragma once
#include <IHeader.hpp>
#include <IBody.hpp>
#include <string>
namespace ft
{
	class IResponse
	{
	public:
		virtual unsigned int			getCode(void) = 0;
		virtual std::string				getHTTPVersion(void) = 0;
		virtual IHeader					*getHeader(void) = 0;
		virtual IBody					*getBody(void) = 0;
		virtual std::string				to_string(void) const = 0;
		virtual unsigned long			size() const = 0;
		virtual ~IResponse(){}
	};
	std::ostream			&operator<<(std::ostream &os, const IResponse &ref);
}