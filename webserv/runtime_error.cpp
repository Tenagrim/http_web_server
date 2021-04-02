#include <runtime_error.hpp>
namespace ft
{
	runtime_error::runtime_error(std::string const &what) : _what(what)
	{}
	
	runtime_error::runtime_error() : _what("Uncaught exception")
	{}
	
	runtime_error::~runtime_error()
	{}
	
	runtime_error::runtime_error(const runtime_error &ref) : _what(ref._what)
	{}
	
	runtime_error	&runtime_error::operator=(const runtime_error &ref)
	{
		_what = ref._what;
		return (*this);
	}
	const char* runtime_error::what() const throw()
	{
		return _what.c_str();
	}
} // namespace ft	