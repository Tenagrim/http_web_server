#pragma once
#include <IRequest.hpp>
#include <map>

class Request : public IRequest
{
	private:
		std::map<std::string, std::string>	headers;
		Request();
	public:
		Request(char *request_text);
		virtual ~Request();
		Request(const Request &ref);

		Request			&operator=(const Request &ref); 
		std::string		getHeaderValue(std::string const &header);	
};