#pragma once
#include <IHeader.hpp>
#include <IBody.hpp>
#include <string>
namespace ft
{
	class IResponse
	{
	public:
		virtual IHeader					*getHeader(void) = 0;
		virtual IBody					*getBody(void) = 0;
		virtual std::string				to_string(void) const = 0;
		virtual unsigned long			size() const = 0;
		virtual ~IResponse(){}

		virtual void deleteBody() = 0;
	};
	std::ostream			&operator<<(std::ostream &os, const IResponse &ref);
}