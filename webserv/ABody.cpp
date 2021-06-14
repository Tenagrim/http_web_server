#include <ABody.hpp>
#include <runtime_error.hpp>
#include <webserv.hpp>

namespace ft
{
	ABody::ABody() : _last_written(0), _last_readed(0), _readed(0), _written(0), _buff()
	{}

	ABody::~ABody()
	{
		if (_buff)
			delete [] _buff;
	}

	ABody::ABody(const ABody &ref) : _last_written(0), _last_readed(0), _readed(0), _written(0), _buff()
	{
		(void)ref;
	}

	ABody &ABody::operator=(const ABody &ref)
	{
		(void)ref;
		return (*this);
	}



	std::string const			&ABody::getContentType() const
	{
		return _content_type;
	}

	void					ABody::setContentType(std::string const &type)
	{
		_content_type = type;
	}


	char *ABody::getBuff( unsigned int size) {
		if (!_buff)
			setBuff(size);
		return _buff;
	}

	void ABody::setBuff(unsigned int size) {
		if (_buff)
			delete _buff;
		_buff = new char [size];
		if (!_buff)
			throw ft::runtime_error("ABODY: SET BUFF: Malloc failed : " + ft::to_string(size));
	}

	long ABody::lastReaded() const {
		return _last_readed;
	}


	void ABody::setReaded(unsigned long readed) {
		_readed += readed;
		_last_readed = readed;
	}

	int ABody::lastWritten() const {
		return _last_written;
	}

	void					ABody::setWritten(unsigned long value)
	{
		_written += value;
		_last_written = value;
	}

	unsigned long			ABody::getWritten()
	{
		return _written;
	}

	unsigned long ABody::getReaded() const {
		return _readed;
	}

	int ABody::getOffset() const {
		return 0;
	}

	unsigned int ABody::getId() const {
		return 0;
	}

}
