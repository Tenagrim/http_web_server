#pragma once
#include <IResponse.hpp>
#include <string>
namespace ft
{
	class TextResponse : public IResponse
	{
	private:
		std::string		_text;
		TextResponse();
	public:
		TextResponse(std::string const &text);
		~TextResponse();
		TextResponse(const TextResponse &ref);
		TextResponse &operator=(const TextResponse &ref);

		unsigned int			getCode(void);
		std::string				getHTTPVersion(void);
		IHeader					*getHeader(void);
		IBody					*getBody(void);
		std::string				to_string(void) const;
		unsigned long			size() const;
	};

}