#include <ErrorPager.hpp>

namespace ft
{
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
	void				ErrorPager::replaceAll(std::string &src, std::string const &find, std::string const &replace)
	{
		std::size_t	pos = 0;
		while (true)
		{
			pos = src.find(find, pos);
			if (pos == std::string::npos)
				break;
			src.replace(pos, find.length(), replace);
			pos += replace.size() + 1;
		}
	}

	ErrorPager &ErrorPager::operator=(const ErrorPager &ref)
	{
		(void)ref;
		return (*this);
	}

	IBody		*ErrorPager::getErrPageBody(int code, std::string const &descr)
	{
		std::string temp = _page_template;
		std::string s_code = ft::to_string(code);
		
		replaceAll(temp, "000", s_code);
		replaceAll(temp, "DESCR", descr);
		return new TextBody(temp);
	}
	
	IResponse	*ErrorPager::getErrorPage(int code)
	{
		IHeader	*head = getErrorHead(code);
		IBody	*body = getErrPageBody(code, getCodeDescr(code));
		head->setHeader("content-length", ft::to_string(body->size()));
		IResponse *response = new BasicResponse(head, body);
		return response;
	}

	IHeader *ErrorPager::getErrorHead(int code)
	{
		char buf[TIME_BUFF_RESPONSE];

		IHeader *head = new Header(response);
		std::string descr = getCodeDescr(code);
		head->setHTTPV("HTTP/1.1");
		head->setResponseCode(code);
		head->setCodeDescription(descr);
		currentTimeFormatted("%a, %d %b %Y %T GMT", buf, TIME_BUFF_RESPONSE);
		head->setHeader("date", buf);
		head->setHeader("content-type", "text/html");
//		Tester 42 don't like this line
//		head->setHeader(h_server, DEFAULT_SERVER_HEADER);
//		head->setHeader(h_connection, "close");
		return head;
	}

} // namespace ft