#include <TextBody.hpp>

namespace ft
{
	TextBody::TextBody()
	{/* Illegal */}
	TextBody::TextBody(std::string const &text) : _text(text)
	{}

	TextBody::~TextBody()
	{}

	TextBody::TextBody(const TextBody &ref) : _text(ref._text)
	{}

	TextBody &TextBody::operator=(const TextBody &ref)
	{
		_text = ref._text;
		return (*this);
	}
	bool				TextBody::getFd(void)
	{
		throw std::runtime_error("Not implemented");
	}
	std::string			TextBody::to_string(void) const
	{
		return _text;
	}
	unsigned int		TextBody::size(void) const
	{
		return _text.size();
	}
	BodyType			TextBody::getType(void)
	{
		throw std::runtime_error("Not implemented");
	}
}