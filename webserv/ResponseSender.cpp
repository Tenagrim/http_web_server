#include <ResponseSender.hpp>

namespace ft
{
	#pragma region Copilen

	ResponseSender::ResponseSender()
	{/* Illegal */}
	ResponseSender::ResponseSender(Dispatcher *_disp) : _dispattcher(_disp)
	{}

	ResponseSender::~ResponseSender()
	{
		(void)_dispattcher;  // FIXME
	}

	ResponseSender::ResponseSender(const ResponseSender &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
	}

	ResponseSender &ResponseSender::operator=(const ResponseSender &ref)
	{
		(void)ref;
		throw std::runtime_error("No implementation");
		return (*this);
	}
	#pragma endregion

	int ResponseSender::sendResponce(IResponse *resp, IClient *client)
	{
		unsigned long	size = resp->size();
		std::string		str = resp->to_string();
		//char const	*c_resp = resp->to_string().c_str();
		write(client->getSock(), str.c_str(), size);
		return (1);
	}
}