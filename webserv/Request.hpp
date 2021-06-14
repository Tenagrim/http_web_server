#pragma once
#include <IRequest.hpp>
#include <map>
#include <runtime_error.hpp>

namespace ft
{
	class Request : public IRequest
	{
	private:
		std::string _text;
		std::string _method;
		std::string _uri;
		std::string _version;
		std::map<std::string, std::string> _headers;

		IHeader		*_header;
		IBody		*_body;
		

		Request(const Request &ref);
	public:
		Request();

		void setBody(IBody *body);
		void setHeader(IHeader *header);

		Request(std::string const &req_text);
		virtual ~Request();
		Request(IHeader *head, IBody *body);

		IHeader					*getHeader(void);
		IBody					*getBody(void);
		
		Request					&operator=(const Request &ref);
		std::string				&getHeaderValue(std::string const &header);
		std::map<std::string, std::string> &getHeaders(void);
		std::string				&getMethod(void); // GET / POST
		std::string				&getURI(void);
		std::string				&getText(void);
		std::string				&getHTTPVersion(void);
		std::string				to_string(void) const;
	};
}