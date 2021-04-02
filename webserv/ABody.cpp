#include <ABody.hpp>

namespace ft
{
	ABody::ABody() : _written(0)
	{}

	ABody::~ABody()
	{}

	ABody::ABody(const ABody &ref) : _written(0)
	{
		(void)ref;
	}

	ABody &ABody::operator=(const ABody &ref)
	{
		(void)ref;
		return (*this);
	}

	unsigned long			ABody::getWritten()
	{
		return _written;
	}

	void					ABody::setWritten(unsigned long value)
	{
		_written += value;
	}

	std::string const			&ABody::getContentType() const
	{
		return _content_type;
	}
	void					ABody::setContentType(std::string const &type)
	{
		_content_type = type;
	}
}