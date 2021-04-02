#include <Request.hpp>

#include <iostream>

namespace ft
{
	Request::Request()
	{/* Illegal */}

	Request::~Request()
	{}

	Request::Request(const Request &ref)
	{
		(void)ref;
		throw ft::runtime_error("No implementation");
	}

	Request &Request::operator=(const Request &ref)
	{
		(void)ref;
		throw ft::runtime_error("No implementation");
		return (*this);
	}

	Request::Request(std::string const &req_text) : _text(req_text)
	{
		int pos, prev_pos;

		pos = _text.find(' ');
		_method = _text.substr(0, pos);
		prev_pos = pos;
		pos = _text.find(' ', prev_pos + 1);
		_uri = _text.substr(prev_pos + 1, pos - prev_pos - 1);
		prev_pos = pos;
		pos = _text.find('\n', prev_pos + 1);
		_version = _text.substr(prev_pos + 1, pos - prev_pos - 1);
		_version.erase(_version.find_last_not_of("\r") + 1);

		_header = 0;
		_body = 0;

		//std::cout << "\nURI: [" << _uri  << "]\n";
		//std::cout << "method: [" << _method  << "]\n";
		//std::cout << "version: [" << _version  << "]  len: "<< _version.size() <<"\n\n";
	}

	Request::Request(IHeader *head, IBody *body) : _header(head), _body(body)
	{}

	std::string &Request::getHeaderValue(std::string const &header)
	{
		(void)header;
		throw ft::runtime_error("No implementation");
	}

	std::map<std::string, std::string> &Request::getHeaders(void)
	{
		throw ft::runtime_error("No implementation");
	}

	std::string &Request::getMethod(void)
	{
		return _method;
	}

	std::string &Request::getURI(void)
	{
		return _uri;
	}

	std::string &Request::getText(void)
	{
		return (_text);
	}

	std::string &Request::getHTTPVersion(void)
	{
		return (_version);
	}
	
	std::string				Request::to_string(void) const
	{
		return (_text);
	}
	IHeader					*Request::getHeader(void)
	{
		return _header;
	}
	IBody					*Request::getBody(void)
	{
		return _body;
	}
}