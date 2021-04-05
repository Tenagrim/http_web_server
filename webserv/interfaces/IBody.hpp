#pragma once
#include <string>

namespace ft
{
	enum BodyType
	{
		file,
		pipe,
		cgi_input

		// maybe more
	};

	class IBody
	{
	public:
		// opens file descriptor to data
		virtual int						getFd() = 0;
//		virtual int						getInputFd() = 0;
		// returns string wich containing data
		virtual std::string				to_string() = 0;
		// returns size of data
		virtual unsigned int			size() const = 0;
		virtual BodyType				getType() = 0;
		virtual unsigned long			getWritten() = 0;
		virtual void					setWritten(unsigned long value) = 0;

		virtual std::string const		&getContentType() const = 0;
		virtual void					setContentType(std::string const &type) = 0;
		virtual int						getOpenedFd() = 0;

		virtual ~IBody(){}
	};
}