#pragma once
#include <IBody.hpp>

namespace ft
{
	class ABody : public IBody
	{
	protected:
		std::string			_content_type;
	private:
		unsigned long		_written;

		ABody &operator=(const ABody &ref);
		ABody(const ABody &ref);
	public:
		ABody();
		virtual ~ABody();

		virtual int					getFd() = 0;
		virtual std::string			to_string() const = 0;
		virtual unsigned int		size() const = 0;
		virtual BodyType			getType() = 0;

		std::string const			&getContentType() const;
		void						setContentType(std::string const &type);
		unsigned long				getWritten();
		void						setWritten(unsigned long value);
	};

}