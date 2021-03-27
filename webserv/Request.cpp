#include <Request.hpp>

#include <iostream>

namespace ft
{
	Request::Request()
	{
		throw std::runtime_error("No implementation");
	}

	Request::~Request()
	{
	}

	Request::Request(const Request &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
	}

	Request &Request::operator=(const Request &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
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

		//std::cout << "\nURI: [" << _uri  << "]\n";
		//std::cout << "method: [" << _method  << "]\n";
		//std::cout << "version: [" << _version  << "]  len: "<< _version.size() <<"\n\n";
	}

	std::string &Request::getHeaderValue(std::string const &header)
	{
		(void)header;
		throw std::runtime_error("No implementation");
	}

	std::map<std::string, std::string> &Request::getHeaders(void)
	{
		throw std::runtime_error("No implementation");
	}

	std::string &Request::getMethod(void)
	{
		throw std::runtime_error("No implementation");
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
}