#pragma once
#include <IRequestValidator.hpp>
#include <map>
#include <webserv.hpp>
#include "Header.hpp"

namespace ft
{
	static std::string req = "POST /users/sign_in HTTP/1.1\r\n"
							 "Host: signin.intra.42.fr\r\n"
							 "Connection: keep-alive\r\n"
							 "Content-Length: 209\r\n"
							 "Cache-Control: max-age=0\r\n"
							 "Upgrade-Insecure-Requests: 1\r\n"
							 "Origin: https://signin.intra.42.fr\r\n"
							 "Content-Type: application/x-www-form-urlencoded\r\n"
							 "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 11_0_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36\r\n"
							 "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"
							 "Sec-Fetch-Site: same-origin\r\n"
							 "Sec-Fetch-Mode: navigate\r\n"
							 "Sec-Fetch-User: ?1\r\n"
							 "Sec-Fetch-Dest: document\r\n"
							 "Referer: https://signin.intra.42.fr/users/sign_in\r\n"
							 "Accept-Encoding: gzip, deflate, br\r\n"
							 "Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
							 "Cookie: _intra_42_session_production=a0572979de861f48a6d42db6760396cc\r\n"
							 "\r\n"
							 "utf8=%E2%9C%93&authenticity_token=aBAFvYQbRaXzg1TZVfz%2BUCCRitzIjKbHJyZUHhvW%2FN%2B3Eu27O5cLGIQ%2BzIbbvybKzCNptiNBuwpqI9KOH7nuWA%3D%3D&user%5Blogin%5D=sadolph&user%5Bpassword%5D=11111111%2Fkazan&commit=Sign+in";

	enum state {
		readin,
		endRead,
		error
	};
	enum process {
		p_start,
		p_head
	};

	class FakeRequestValidator : public IRequestValidator
	{
	private:
		typedef typename std::string::size_type strPos;
		void valiateStartLine(strPos &pos1, strPos &pos2);
		void valiateHeader(strPos &pos1, strPos &pos2);
		enum state state;
		enum process process;
		methods_enum _method;
		std::string _url;
		std::map<header_keys, std::string> _header;

	public:
		void fillMethod(std::string const &line);
		FakeRequestValidator();
		FakeRequestValidator(const std::string &text,
							 Header &header);
		virtual ~FakeRequestValidator();
		FakeRequestValidator(const FakeRequestValidator &ref);
		FakeRequestValidator &operator=(const FakeRequestValidator &ref);

		bool isValid(const IRequest &req);
		bool isValid(std::string const &line);
		void reset(void);


		//optional
		//bool isValid(const IRequest &req, std::string const &http_version);
		void fillUrl(const std::string &line);

		void checkHttp(const std::string &line);
	};

} // namespace ft