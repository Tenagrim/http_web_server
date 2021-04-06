#pragma once
#include <IBody.hpp>
#include <unistd.h>
namespace ft
{
	class ABody : public IBody
	{
	protected:
		std::string			_content_type;

	private:
		long int			_last_written;
		long int			_last_readed;
		unsigned long 		_readed;
		unsigned long		_written;
		char 				*_buff;

		ABody &operator=(const ABody &ref);
		ABody(const ABody &ref);
	public:
		ABody();
		virtual ~ABody();

		virtual int					getFd() = 0;
		virtual std::string			to_string() = 0;
		virtual unsigned int		size() const = 0;
		virtual BodyType			getType() = 0;

		std::string const			&getContentType() const;
		void						setContentType(std::string const &type);
		char 						*getBuff(unsigned  int size);
		void 						setBuff(unsigned int size);

		unsigned long				getWritten();
		void						setWritten(unsigned long value);
		int 						lastWritten() const;

		unsigned long				getReaded() const;
		void						setReaded(unsigned long readed);
		long						lastReaded() const;
	};

}
