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


Request::Request(std::string const &req_text) : _text(req_text)
{
	int pos, prev_pos;

	pos = _text.find(' ');
	_method = _text.substr(0, pos);
	prev_pos = pos + 1;
	pos = _text.find(' ', prev_pos);
	_uri =_text.substr(prev_pos, pos);
}

std::string		&Request::getHeaderValue(std::string const &header)
{
	throw std::runtime_error("No implementation");


}

std::map<std::string, std::string>	&Request::getHeaders(std::string const &header)
{
	throw std::runtime_error("No implementation");

}

std::string							&Request::getMethod(void)
{
	throw std::runtime_error("No implementation");

}

std::string							&Request::getURI(void)
{
	return _uri;
}

std::string							&Request::getText(void)
{
	return (_text);
}