#pragma once
#include <exception>
#include <string>
namespace ft
{
class runtime_error : public std::exception
	{
	private:
		std::string _what;
	public:
		explicit runtime_error(std::string const &what);
		runtime_error();
		virtual ~runtime_error() _NOEXCEPT;
		runtime_error(const runtime_error &ref);
		runtime_error &operator=(const runtime_error &ref);
		const char* what() const throw();
	};

} // namespace ft
