#include <ABody.hpp>

namespace ft
{
	ABody::ABody() : _written(0)
	{}

	ABody::~ABody()
	{}

	ABody::ABody(const ABody &ref)
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
}