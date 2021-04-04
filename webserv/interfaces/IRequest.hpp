#pragma once
#include <string>
#include <map>
#include <ostream>
#include <IHeader.hpp>
#include <IBody.hpp>

namespace ft
{
	class IRequest
	{
	public:
		virtual IHeader					*getHeader(void) = 0;
		virtual IBody					*getBody(void) = 0;
		
	//	virtual std::string				&getHeaderValue(std::string const &header) = 0;
	//	virtual std::map<std::string, std::string> &getHeaders(void) = 0;
	
//		virtual std::string				&getMethod(void) = 0; // GET / POST
//		virtual std::string				&getURI(void) = 0;
	//	virtual std::string				&getHTTPVersion(void) = 0;
//		virtual std::string				&getText(void) = 0;
		
		virtual std::string				to_string(void) const = 0;
		virtual void					setBody(IBody *body) = 0;
		virtual void					setHeader(IHeader *header) = 0;


		virtual ~IRequest(){};
	};
	std::ostream			&operator<<(std::ostream &os, const IRequest &ref);
}
