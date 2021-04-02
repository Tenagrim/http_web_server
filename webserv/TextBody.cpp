#include <TextBody.hpp>

namespace ft
{
	TextBody::TextBody()
	{/* Illegal */}
	TextBody::TextBody(std::string const &text) : _text(text)
	{
		_content_type = "text/html";
	}

	TextBody::~TextBody()
	{}

	TextBody::TextBody(const TextBody &ref) : _text(ref._text)
	{}

	TextBody &TextBody::operator=(const TextBody &ref)
	{
		_text = ref._text;
		return (*this);
	}
	int					TextBody::getFd(void)
	{
		throw ft::runtime_error("Not implemented");
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
		throw ft::runtime_error("Not implemented");
	}
}