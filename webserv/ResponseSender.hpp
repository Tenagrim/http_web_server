#pragma once
#include <IResponseSender.hpp>
#include <Dispatcher.hpp>

namespace ft
{
	class ResponseSender : public IResponseSender
	{
	private:
		Dispatcher		*_dispattcher;
		ResponseSender();
	public:
		ResponseSender(Dispatcher *_disp);
		virtual ~ResponseSender();
		ResponseSender(const ResponseSender &ref);
		ResponseSender &operator=(const ResponseSender &ref);
		int sendResponce(IResponse *resp, IClient *client);
	};

}