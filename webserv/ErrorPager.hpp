#pragma once
#include <webserv.hpp>
#include <Header.hpp>
#include <BasicResponse.hpp>
#include <TextBody.hpp>
namespace ft
{

	class ErrorPager
	{
	private:
		std::string			_page_template;
		IBody				*getErrPageBody(int code, std::string const &descr);
		void				replaceAll(std::string &src, std::string const &find, std::string const &replace);
	public:
		ErrorPager();
		~ErrorPager();
		ErrorPager(const ErrorPager &ref);
		ErrorPager	&operator=(const ErrorPager &ref);
		IResponse	*getErrorPage(int code);
	};
} // namespace ft