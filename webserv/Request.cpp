#include <Request.hpp>

Request::Request()
{
}

Request::~Request()
{
}

Request::Request(const Request &ref)
{
}

Request	&Request::operator=(const Request &ref)
{
	return (*this);
}


Request::Request(char *request_text)
{

}

std::string		Request::getHeaderValue(std::string const &header)
{


}
