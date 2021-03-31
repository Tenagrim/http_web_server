#pragma once
#include <string>
#include <webserv.hpp>

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
		virtual std::string			to_string(void)= 0;

		virtual MessageType			getType(void) const = 0;
		virtual std::string const	&getHeaderValue(header_keys_enum key) = 0;
		virtual int					getResponseCode(void) const = 0;
		virtual std::string			&getURI(void) = 0;
		virtual std::string			&getHTTPVersion(void) = 0;
		virtual std::string			&getCodeDescription(void) = 0;
		virtual methods_enum		getMethod(void) const = 0; // GET / POST

		virtual void				setHTTPV(std::string const &new_vers) = 0;
		virtual void				setMethod(methods_enum new_meth) = 0;
		virtual void				setURI(std::string const &new_uri) = 0;
		virtual void				setCodeDescription(std::string const &new_descr) = 0;
		virtual void				setResponseCode(int new_code) = 0;
		virtual void				setHeader(header_keys h_key, std::string const &header_value) = 0;
		virtual unsigned long		size() = 0;
		virtual ~IHeader(){}
	};
}

//std::ostream			&operator<<(std::ostream &os, const ft::IHeader &ref);