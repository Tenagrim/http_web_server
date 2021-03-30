#include <TextResponse.hpp>

#include <iostream>

namespace ft
{
	TextResponse::TextResponse()
	{/* Illegal */}

	TextResponse::TextResponse(std::string const &text) : _text(text), _header(0), _body(0)
	{
		_header = NULL;
		_body = NULL;
	}
	
	TextResponse::TextResponse(IHeader *head, IBody *body) :  _header(head), _body(body)
	{
		_text = head->to_string() + body->to_string();
	}

	TextResponse::~TextResponse()
	{}

	TextResponse::TextResponse(const TextResponse &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
	}

	TextResponse &TextResponse::operator=(const TextResponse &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
		return (*this);
	}

	unsigned int			TextResponse::getCode(void)
	{
		throw std::runtime_error("No implementation");
		return (200);
	}
	
	std::string				TextResponse::getHTTPVersion(void)
	{
		throw std::runtime_error("No implementation");
		return std::string("NULL");
	}
	IHeader					*TextResponse::getHeader(void)
	{
		//std::cout << "TEXT RESPONSE: GET HEADER["<< _header <<"]\n";
		return _header;
	}
	IBody					*TextResponse::getBody(void)
	{
		return _body;
	}
	
	std::string				TextResponse::to_string(void) const
	{
		return _text;
	}
	
	unsigned long			TextResponse::size() const
	{
		return _text.size();
	}
} // namespace ft