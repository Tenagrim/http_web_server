#pragma once
#include <IHeader.hpp>
#include <IBody.hpp>

namespace ft
{
	class IResponse
	{
	public:
		virtual unsigned int			getCode(void) = 0;
		virtual std::string				&getHTTPVersion(void) = 0;
		virtual IHeader					*getHeader(void) = 0;
		virtual IBody					*getBody(void) = 0;

		virtual ~IResponse(){}
	};
}