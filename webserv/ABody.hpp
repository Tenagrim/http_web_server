#pragma once
#include <IBody.hpp>

namespace ft
{
	class ABody : public IBody
	{
	private:
		unsigned long _written;

		ABody &operator=(const ABody &ref);
		ABody(const ABody &ref);
	public:
		ABody();
		virtual ~ABody();

		virtual int					getFd(void) = 0;
		virtual std::string			to_string(void) const = 0;
		virtual unsigned int		size(void) const = 0;
		virtual BodyType			getType(void) = 0;
		unsigned long			getWritten();
		void					setWritten(unsigned long value);
	};

}