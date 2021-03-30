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

	//void	send

	int ResponseSender::sendResponce(IResponse *resp, IClient *client)
	{
		//unsigned long	size = resp->size();
		//std::string		str = resp->to_string();
		//char const	*c_resp = resp->to_string().c_str();
		//write(client->getSock(), str.c_str(), size);
		//if (resp->getHeader())
		//	std::cout << "RESPONSE SENDER: HEADER SIZE: ["<< resp->getHeader()->to_string().size() <<"]\n";
		//std::cout << "RESPONSE SENDER: WRITE SIZE: ["<< size <<"] CSTR SIZE:[" << ft_strlen((char*)(str.c_str())) << "]\n";

		if (!client->headerSent())
			sendHeader(resp->getHeader(), client);
		else if (!client->bodySent())
			sendBody(resp->getBody(), client);
		else
			throw std::runtime_error("All is already sent, no need to call Sender");
		return (1);
	}
	
	void			sendHeader(IHeader *header, IClient *client)
	{
		std::string str;

		str = header->to_string();
		write(client->getSock(), str.c_str(),str.size());
		client->sendHeader();
	}

	void			ResponseSender::sendTextBody(TextBody *body)
	{
		std::string str;

		str = header->to_string();
		write(client->getSock(), str.c_str(),str.size());
	}

	void			ResponseSender::sendFileBody(FileBody *body)
	{
		char	*buff = malloc(sizeof(char) * body->size());
		if (!buff)
			throw std::runtime_error("RERPONSE SENDER: UNABLE TO SEND FILE BODY: MALLOC FAILED");
		free(buff);
	}


	void			ResponseSender::sendBody(IBody *body, IClient *client)
	{
		if (dynamic_cast<TextBody*>(body))
			sendTextBody(dynamic_cast<TextBody*>(body));
		if (dynamic_cast<FileBody*>(body))
			sendTextBody(dynamic_cast<FileBody*>(body));
		else
			throw std::runtime_error("RESPONSE SENDER: WRONG TYPE OF BODY GOT");
		client->sendBody();
	}
}

//RESP BODY SIZE: [1488398]
//RESP BODY STR SIZE: [1488398]