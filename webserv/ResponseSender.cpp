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
	
	void			ResponseSender::sendHeader(IHeader *header, IClient *client)
	{
		std::string str;

		str = header->to_string();
		write(client->getSock(), str.c_str(),str.size());
		client->sendHeader();
	}

	void			ResponseSender::sendTextBody(TextBody *body, IClient *client)
	{
		std::string str;
		int ret;
		
		std::cout << "SENDER: SEND TEXT BODY\n";
		str = body->to_string();
		ret = write(client->getSock(), str.c_str(),str.size());
		if (ret != -1)
			body->setWritten(ret);
		else
			throw std::runtime_error("FAILED TO WRITE RESP: (Write returned -1)");
		std::cout << "SENDER: TEXT BODY SENT\n";
	}

	void			ResponseSender::sendFileBody(FileBody *body, IClient *client)
	{
		std::cout << "SENDER: SEND FILE BODY\n";
		char	*buff = new char [READ_BODY_ONE_TIME];
		int ret;
		if (!buff)
			throw std::runtime_error("RERPONSE SENDER: UNABLE TO SEND FILE BODY: MALLOC FAILED");
		std::cout << "SENDER: BEGIN READING\n";
		ret = read(body->getFd(), buff, READ_BODY_ONE_TIME);
		std::cout << "SENDER: READING ENDED. READED [" << ret << "]\nSENDER: BEGIN WRITING\n";
		//ret = write(client->getSock(), buff, body->size());
		ret = send(client->getSock(), buff, ret, 0);
		std::cout << "SENDER: WRITING COMPLETED. WRITTEN: [" << ret << "]\nSENDER: FILE BODY SENT\n";
		body->setWritten(ret);
		delete [] buff;
	}


	void			ResponseSender::sendBody(IBody *body, IClient *client)
	{
		if (!body)
			throw std::runtime_error("RESPONSE SENDER: NULL BODY GOT");
		if (dynamic_cast<TextBody*>(body))
			sendTextBody(dynamic_cast<TextBody*>(body), client);
		else if (dynamic_cast<FileBody*>(body))
			sendFileBody(dynamic_cast<FileBody*>(body), client);
		else
			throw std::runtime_error("RESPONSE SENDER: WRONG TYPE OF BODY GOT");
			std::cout << "SENDER: SEND BODY SIZE: [" << body->size() << "] WRITTEN: [" <<  body->getWritten() << "]\n";
		if (body->size() == body->getWritten())
			client->sendBody();
	}
}

//RESP BODY SIZE: [1488398]
//RESP BODY STR SIZE: [1488398]