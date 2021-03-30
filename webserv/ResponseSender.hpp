#pragma once
#include <IResponseSender.hpp>
#include <Dispatcher.hpp>
#include <TextBody.hpp>
#include <FileBody.hpp>

#define READ_BODY_ONE_TIME 200000

namespace ft
{
	class ResponseSender : public IResponseSender
	{
	private:
		Dispatcher		*_dispattcher;
		ResponseSender();
		void			sendHeader(IHeader *header, IClient *client);
		void			sendBody(IBody *body, IClient *client);
		
		void			sendTextBody(TextBody *body, IClient *client);
		void			sendFileBody(FileBody *body, IClient *client);
	public:
		ResponseSender(Dispatcher *_disp);
		virtual ~ResponseSender();
		ResponseSender(const ResponseSender &ref);
		ResponseSender &operator=(const ResponseSender &ref);
		int sendResponce(IResponse *resp, IClient *client);
	};

}