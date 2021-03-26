#pragma once
#include <IRequest.hpp>
#include <map>

class Request : public IRequest
{
	private:
		std::string							_text;
		std::string							_method;
		std::string							_uri;
		std::map<std::string, std::string>	_headers;
		Request();
	public:
		Request(std::string const &req_text);
		virtual ~Request();
		Request(const Request &ref);

		Request								&operator=(const Request &ref); 
		std::string							&getHeaderValue(std::string const &header);
		std::map<std::string, std::string>	&getHeaders(std::string const &header);	
		std::string							&getMethod(void);	// GET / POST
		std::string							&getURI(void);
		std::string							&getText(void);
};