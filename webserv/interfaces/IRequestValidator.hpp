#pragma once
#include <IRequest.hpp>
#include <string>

namespace ft
{
	class IRequestValidator
	{
	public:
		virtual int isValid(const IRequest &req) = 0;

		//optional
	//	virtual bool isValid(const IRequest &req, std::string const &http_version) = 0;
		
		// returns -1 if not valid, 1 if valid and 0 if got only "\r"
		virtual int isValid(std::string const & line) = 0;
		virtual int isValid(char const * line) = 0;

		virtual void reset(void) = 0;

		virtual ~IRequestValidator(){}
	};
}