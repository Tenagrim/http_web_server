#include <TextResponse.hpp>

namespace ft
{
	TextResponse::TextResponse()
	{/* Illegal */}

	TextResponse::TextResponse(std::string const &text) : _text(text)
	{}

	TextResponse::~TextResponse()
	{}

	TextResponse::TextResponse(const TextResponse &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
	}

	TextResponse &TextResponse::operator=(const TextResponse &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
		return (*this);
	}

	unsigned int			TextResponse::getCode(void)
	{
		throw std::runtime_error("No implementation");
		return (200);
	}
	
	std::string				TextResponse::getHTTPVersion(void)
	{
		throw std::runtime_error("No implementation");
		return std::string("NULL");
	}
	IHeader					*TextResponse::getHeader(void)
	{

		throw std::runtime_error("No implementation");
		return NULL;
	}
	IBody					*TextResponse::getBody(void)
	{
		throw std::runtime_error("No implementation");
		return NULL;
	}
	
	std::string				TextResponse::to_string(void) const
	{
		return _text;
	}
	
	unsigned long			TextResponse::size() const
	{
		return _text.size();
	}
} // namespace ft