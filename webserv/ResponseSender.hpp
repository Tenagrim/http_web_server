#pragma once
#include <IResponseSender.hpp>
#include <Dispatcher.hpp>
#include <TextBody.hpp>
#include <FileBody.hpp>

namespace ft
{
	class ResponseSender : public IResponseSender
	{
	private:
		Dispatcher		*_dispattcher;
		ResponseSender();
		void			sendHeader(IHeader *header, IClient *client);
		void			sendBody(IBody *body, IClient *client);
		
		void			sendTextBody(TextBody *body);
		void			sendFileBody(FileBody *body);
	public:
		ResponseSender(Dispatcher *_disp);
		virtual ~ResponseSender();
		ResponseSender(const ResponseSender &ref);
		ResponseSender &operator=(const ResponseSender &ref);
		int sendResponce(IResponse *resp, IClient *client);
	};

}