#pragma once
#include <IRequest.hpp>
#include <Client.hpp> // FIXME should be ICLIENT

namespace ft
{
	class IRequestReciever
	{
	public:
		virtual void getRequest(Client *client)=0;
		virtual int				getId()=0;

		virtual ~IRequestReciever(){}
	};
}