#pragma once
#include <IRequest.hpp>
namespace ft
{
	class IClient
	{
		public:		
		virtual int				getSock(void) const = 0;
		virtual void			setLastRequest(IRequest *request) = 0;
		virtual IRequest		*getLastRequest(void) = 0;
		virtual bool			needsResponce(void) = 0;
		virtual ~IClient(){}
	};
}