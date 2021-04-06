#pragma once
#include <webserv.hpp>
#include <Header.hpp>
#include <BasicResponse.hpp>
#include <TextBody.hpp>
#include <defines.hpp>
#include <FakeTimeMachine.hpp>
namespace ft
{

	class ErrorPager
	{
	private:
		std::string			_page_template;
		IBody				*getErrPageBody(int code, std::string const &descr);
		void				replaceAll(std::string &src, std::string const &find, std::string const &replace);
		FakeTimeMachine		_t_machine;
	public:
		ErrorPager();
		~ErrorPager();
		ErrorPager(const ErrorPager &ref);
		ErrorPager	&operator=(const ErrorPager &ref);
		IResponse	*getErrorPage(int code);
		IHeader *getErrorHead(int code);
		IBody *getErrorBody(int code);
	};
} // namespace ft