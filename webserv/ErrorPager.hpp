#pragma once
#include <webserv.hpp>
#include <IResponse.hpp>
namespace ft
{

	class ErrorPager
	{
	private:
	public:
		ErrorPager();
		~ErrorPager();
		ErrorPager(const ErrorPager &ref);
		ErrorPager &operator=(const ErrorPager &ref);
		//I
	};
#include <ErrorPager.hpp>

	ErrorPager::ErrorPager()
	{
	}

	ErrorPager::~ErrorPager()
	{
	}

	ErrorPager::ErrorPager(const ErrorPager &ref)
	{
	}

	ErrorPager &ErrorPager::operator=(const ErrorPager &ref)
	{
		return (*this);
	}

} // namespace ft