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
		throw ft::runtime_error("No implementation");
	}

	ResponseSender &ResponseSender::operator=(const ResponseSender &ref)
	{
		(void)ref;
		throw ft::runtime_error("No implementation");
		return (*this);
	}
	#pragma endregion


	int ResponseSender::sendResponce(IResponse *resp, IClient *client)
	{
		if (!client->headerSent())
		{
			sendHeader(resp->getHeader(), client);
		}
		else if (!client->bodySent())
		{
			#ifdef DEBUG
			std::cout << "SENDER: SEND BODY FOR URI: [" << client->getLastRequest()->getHeader()->getURI() << "]\n";
			#endif
			sendBody(resp->getBody(), client);
		}
		else
			throw ft::runtime_error("All is already sent, no need to call Sender");
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
		#ifdef DEBUG
			std::cout << "SENDER: SEND TEXT BODY\n";
		#endif	
		str = body->to_string();
		ret = write(client->getSock(), str.c_str(),str.size());
		if (ret != -1)
			body->setWritten(ret);
		else
			throw ft::runtime_error("FAILED TO WRITE RESP: (Write returned -1)");
		#ifdef DEBUG
		std::cout << "SENDER: TEXT BODY SENT\n";
		#endif
	}

	void			ResponseSender::sendFileBody(FileBody *body, IClient *client)
	{
		#ifdef DEBUG
		std::cout << "SENDER: SEND FILE BODY\n";
		#endif
		char	*buff = new char [READ_BODY_ONE_TIME];
		int ret;
		if (!buff)
			throw ft::runtime_error("RERPONSE SENDER: UNABLE TO SEND FILE BODY: MALLOC FAILED");
		#ifdef DEBUG
			std::cout << "SENDER: BEGIN READING\n";
		#endif
		ret = read(body->getFd(), buff, READ_BODY_ONE_TIME);
		#ifdef DEBUG
			std::cout << "SENDER: READING ENDED. READED [" << ret << "]\nSENDER: BEGIN WRITING\n";
		#endif
		ret = send(client->getSock(), buff, ret, 0);
		#ifdef DEBUG
			std::cout << "SENDER: WRITING COMPLETED. WRITTEN: [" << ret << "]\nSENDER: FILE BODY SENT\n";
		#endif
		body->setWritten(ret);
		delete [] buff;
	}


	void			ResponseSender::sendBody(IBody *body, IClient *client)
	{
//		TODO:Some something when no BODY;
		if (!body) {
			client->sendBody();
			return;
		}
//			throw ft::runtime_error("RESPONSE SENDER: NULL BODY GOT");
		if (dynamic_cast<TextBody*>(body))
			sendTextBody(dynamic_cast<TextBody*>(body), client);
		else if (dynamic_cast<FileBody*>(body))
			sendFileBody(dynamic_cast<FileBody*>(body), client);
		else
			throw ft::runtime_error("RESPONSE SENDER: WRONG TYPE OF BODY GOT");
		#ifdef DEBUG
			std::cout << "SENDER: SEND BODY SIZE: [" << body->size() << "] WRITTEN: [" <<  body->getWritten() << "]\n";
		#endif
		if (body->size() == body->getWritten())
			client->sendBody();
	}
}