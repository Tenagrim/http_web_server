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
		
		virtual void			setLastResponse(IResponse *request) = 0;
		virtual IResponse		*getLastResponse(void) = 0;

		virtual bool			needsResponce() = 0;
		virtual bool			requestReceived() = 0;
		virtual bool			headerSent() = 0;
		virtual bool			bodySent() = 0;
		virtual void			sendHeader() = 0;
		virtual void			sendBody() = 0;
		virtual void 			updateEventTime() = 0;
		virtual unsigned long	getUsecsFromLastEvent() = 0;
		virtual ~IClient(){}
	};
}