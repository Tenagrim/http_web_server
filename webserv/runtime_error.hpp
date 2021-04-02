#include <exception>
#include <string>
namespace ft
{
	#pragma once
	class runtime_error
	{
	private:
		std::string _waht;
	public:
		runtime_error(std::string const &what);
		runtime_error();
		~runtime_error();
		runtime_error(const runtime_error &ref);
		runtime_error &operator=(const runtime_error &ref);
		const char* what() const throw();
	};

} // namespace ft
