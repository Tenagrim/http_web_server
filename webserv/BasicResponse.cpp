#include <BasicResponse.hpp>
namespace ft
{
	

	BasicResponse::BasicResponse()
	{/* Illegal*/}

	BasicResponse::BasicResponse(IHeader *head, IBody *body) : _header(head), _body(body)
	{}

	BasicResponse::~BasicResponse()
	{
		if (_header)
			delete _header;
		if (_body)
			delete _body;
	}

	BasicResponse::BasicResponse(const BasicResponse &ref)
	{
		(void)ref;
		throw std:: runtime_error("No implementation");
	}

	BasicResponse &BasicResponse::operator=(const BasicResponse &ref)
	{
		(void)ref;
		throw std:: runtime_error("No implementation");
		return (*this);
	}

	IHeader					*BasicResponse::getHeader(void)
	{
		return _header;
	}

	IBody					*BasicResponse::getBody(void)
	{
		return _body;
	}

	std::string				BasicResponse::to_string(void) const
		{
			if (_header && _body)
				return	_header->to_string() + _body->to_string();
			else if (_header)
				return _header->to_string();
			else
				return "";
		}

	unsigned long			BasicResponse::size() const
	{
		return (_header->size() + _body->size());
	}
} // namespace ft