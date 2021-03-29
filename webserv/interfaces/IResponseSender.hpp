#pragma once
#include <IResponse.hpp>
#include <IClient.hpp>
class IResponseSender
{
	public:
	virtual int		sendResponce(IResponse *resp, IClient *client);
	virtual	~IResponseSender(){}
};
