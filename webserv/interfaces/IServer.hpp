#pragma once
#include <IRequest.hpp>
#include <IResponse.hpp>

namespace ft
{
	class IServer
	{
	private:
	public:
		virtual IRequest	*getRequest(void) = 0;
		virtual int			sendResponce(const IResponse &resp) = 0;
		virtual int			acceptConnection() = 0;
		virtual int			processConnection() = 0;
		virtual int			parentForkPart() = 0;

		virtual ~IServer(){}
	};
}