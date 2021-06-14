#pragma once
#include <IResponse.hpp>
#include <string>
#include <src/components/TextBody.hpp>
#include <runtime_error.hpp>

namespace ft
{
	// SHOULD INERHIT FROM BASIC RESPONSE


	// BUT IT DON'T
	class TextResponse : public IResponse
	{
	private:
		std::string		_text;
		IHeader		*_header;
		IBody			*_body;
		TextResponse();
	public:
		TextResponse(std::string const &text);
		TextResponse(IHeader *head, IBody *body);
		~TextResponse();
		TextResponse(const TextResponse &ref);
		TextResponse &operator=(const TextResponse &ref);

		unsigned int			getCode(void);
		std::string				getHTTPVersion(void);
		IHeader					*getHeader(void);
		IBody					*getBody(void);
		std::string				to_string(void) const;
		unsigned long			size() const;

		virtual	void 			deleteBody();
	};

}