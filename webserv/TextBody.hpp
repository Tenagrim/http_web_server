#pragma once
#include <ABody.hpp>
#include <runtime_error.hpp>
namespace ft
{
	class TextBody : public ABody
	{
	private:
		TextBody();
		std::string	_text;

	public:
		TextBody(std::string const & text);
		virtual ~TextBody();
		TextBody(const TextBody &ref);
		TextBody &operator=(const TextBody &ref);

		int					getFd(void);
		std::string			to_string(void) const;
		unsigned int		size(void) const;
		BodyType			getType(void);
	
	};

}
