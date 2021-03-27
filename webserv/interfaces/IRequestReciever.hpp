#pragma once
#include <IRequest.hpp>


namespace ft
{
	class IRequestReciever
	{
	public:
		virtual IRequest		*getRequest()=0;
		virtual int				getId()=0;

		virtual ~IRequestReciever(){}
	};
}