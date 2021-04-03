#pragma once
#include <IRequestValidator.hpp>
namespace ft
{

	class FakeRequestValidator : public IRequestValidator
	{
	private:
		typedef std::string::size_type strPos;
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

//		bool isValid(const IRequest &req);
//		bool isValid(std::string const &line);
		void reset(void);


		//optional
		//bool isValid(const IRequest &req, std::string const &http_version);
		void fillUrl(const std::string &line);

		void checkHttp(const std::string &line);
	};

} // namespace ft