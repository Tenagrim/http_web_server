#include <runtime_error.hpp>
namespace ft
{
	runtime_error::runtime_error(std::string const &what) : _waht(what)
	{}
	
	runtime_error::runtime_error() : _waht("Uncaught exception")
	{}
	
	runtime_error::~runtime_error() _NOEXCEPT
	{}

	runtime_error::runtime_error(const runtime_error &ref) : _waht(ref._waht)
	{}
	
	runtime_error	&runtime_error::operator=(const runtime_error &ref)
	{
		_waht = ref._waht;
		return (*this);
	}
	const char* runtime_error::what() const throw()
	{
		return _waht.c_str();
	}
} // namespace ft	