#pragma once
#include <webserv.hpp>
#include <Header.hpp>
#include <BasicResponse.hpp>
namespace ft
{

	class ErrorPager
	{
	private:
		std::string			_page_template;
		IBody				*getErrPageBody(int code, std::string const &descr);
	public:
		ErrorPager();
		~ErrorPager();
		ErrorPager(const ErrorPager &ref);
		ErrorPager	&operator=(const ErrorPager &ref);
		IResponse	*getErrorPage(int code);
	};
#include <ErrorPager.hpp>

	ErrorPager::ErrorPager()
	{
		_page_template =	"<html>"
							"<head><title>000 DESCR</title></head>"
							"<body bgcolor=\"white\">"
							"<center><h1>000 DESCR</h1></center>"
							"<hr><center>SERV/VERS</center>"
							"</body>"
							"</html>";
	}

	ErrorPager::~ErrorPager()
	{}

	ErrorPager::ErrorPager(const ErrorPager &ref)
	{
		(void)ref;
	}

	ErrorPager &ErrorPager::operator=(const ErrorPager &ref)
	{
		(void)ref;
		return (*this);
	}

	IBody		*ErrorPager::getErrPageBody(int code, std::string const &descr)
	{
		int pos;
		std::string temp = _page_template;
		//std::string s_code = std::s
		
		//pos = temp.find("000");

	}
	
	IResponse	*ErrorPager::getErrorPage(int code)
	{
		IHeader	*head = new Header(response);
		std::string descr = getCodeDescr(code);
		head->setHTTPV("HTTP/1.1");
		head->setResponseCode(code);
		head->setCodeDescription(descr);
		IBody	*body = getErrPageBody(code, descr);		
		return (new BasicResponse(head, body));
	}
	


} // namespace ft