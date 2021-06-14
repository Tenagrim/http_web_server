#pragma once
#include <IResponseSender.hpp>

namespace ft {
	class Dispatcher;
}

#include <src/core/Dispatcher.hpp>
#include <src/components/TextBody.hpp>
#include <src/components/FileBody.hpp>

#include <defines.hpp>

namespace ft
{
	class ResponseSender : public IResponseSender
	{
	private:
		Dispatcher			*_dispattcher;
		ResponseSender();

		int sendHeader(IHeader *header, IClient *client);
		int					sendBody(IBody *body, IClient *client);
		
		int 				sendTextBody(TextBody *body, IClient *client);
		int 				sendFileBody(FileBody *body, IClient *client);

		int					sendFullResponse(IResponse *resp, IClient *client);
	public:
		ResponseSender(Dispatcher *_disp);
		virtual ~ResponseSender();
		ResponseSender(const ResponseSender &ref);
		ResponseSender		&operator=(const ResponseSender &ref);
		int					sendResponce(IResponse *resp, IClient *client);
	};

}