#include <BasicRequest.hpp>

namespace ft
{
	

	BasicRequest::BasicRequest()
	{/* Illegal */}


	BasicRequest::BasicRequest(IHeader *head, IBody *body) : _header(head), _body(body)
	{}

	BasicRequest::~BasicRequest()
	{
		if (_header)
			delete _header;
		if (_body)
			delete _body;
	}

	BasicRequest::BasicRequest(const BasicRequest &ref)
	{
		(void)ref;
		throw ft::runtime_error("No implementation");
	}

	BasicRequest &BasicRequest::operator=(const BasicRequest &ref)
	{
		(void)ref;
		throw ft::runtime_error("No implementation");
		return (*this);
	}

	IHeader					*BasicRequest::getHeader(void)
	{
		return _header;
	}

	IBody					*BasicRequest::getBody(void)
	{
		return _body;
	}

	std::string				BasicRequest::to_string(void) const
	{
		return	_header->to_string() + _body->to_string();
	}


} // namespace ft