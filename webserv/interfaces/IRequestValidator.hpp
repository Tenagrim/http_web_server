#pragma once
#include <IRequest.hpp>
#include <string>

namespace ft
{
	class IRequestValidator
	{
	public:
		virtual bool isValid(const IRequest &req) = 0;

		//optional
	//	virtual bool isValid(const IRequest &req, std::string const &http_version) = 0;
		
		virtual bool isValid(std::string const & line) = 0;
		virtual void reset(void) = 0;

		virtual ~IRequestValidator(){}
	};
}