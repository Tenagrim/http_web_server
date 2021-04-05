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
		int					getInputFd(void);
		std::string			to_string(void);
		unsigned int		size(void) const;
		BodyType			getType(void);
		int						getOpenedFd();
	
	};

}
