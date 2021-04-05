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
		int ret;
		client->updateEventTime();
		if (!client->headerSent())
		{
			sendHeader(resp->getHeader(), client);
			if (resp->getBody())
				return 1;
			else return 0;
		}
		else if (!client->bodySent())
		{
			#ifdef DEBUG
			std::cout << "SENDER: SEND BODY FOR URI: [" << client->getLastRequest()->getHeader()->getURI() << "]\n";
			#endif
			ret = sendBody(resp->getBody(), client);
		}
		else
			throw ft::runtime_error("All is already sent, no need to call Sender");
		return (ret);
	}
	
	void			ResponseSender::sendHeader(IHeader *header, IClient *client)
	{
		std::string str;
		
		str = header->to_string();
		write(client->getSock(), str.c_str(),str.size());
		client->sendHeader();
	}

	int ResponseSender::sendTextBody(TextBody *body, IClient *client)
	{
		std::string str;
		int ret;
		#ifdef DEBUG
			std::cout << "SENDER: SEND TEXT BODY\n";
		#endif	
		str = body->to_string();
		ret = write(client->getSock(), str.c_str(),str.size());
		if (ret == -1)
			throw ft::runtime_error("FAILED TO WRITE RESP: (Write returned -1)");
		#ifdef DEBUG
		std::cout << "SENDER: TEXT BODY SENT\n";
		#endif
		body->setWritten(ret);
		return (ret);
	}

	int ResponseSender::sendFileBody(FileBody *body, IClient *client)
	{
		#ifdef DEBUG
		std::cout << "SENDER: SEND FILE BODY\n";
		#endif
		//if (body->getWritten() < body->size()) {
			char *buff = new char[READ_BODY_ONE_TIME];
			int retw, retr;
			if (!buff)
				throw ft::runtime_error("RERPONSE SENDER: UNABLE TO SEND FILE BODY: MALLOC FAILED");
#ifdef DEBUG
			std::cout << "SENDER: BEGIN READING\n";
#endif
			retr = read(body->getOpenedFd(), buff, READ_BODY_ONE_TIME);
#ifdef DEBUG
			std::cout << "SENDER: READING ENDED. READED [" << ret << "]\nSENDER: BEGIN WRITING\n";
#endif
			retw = send(client->getSock(), buff, retr, 0);
#ifdef DEBUG
			std::cout << "SENDER: WRITING COMPLETED. WRITTEN: [" << ret << "] SENDER: FILE BODY SENT\n";
#endif
			if (retr != retw)
				throw ft::runtime_error("SOMETHING WENT WRONG");
			body->setWritten(retw);
			delete[] buff;
		//}
		return retw;
	}


	int ResponseSender::sendBody(IBody *body, IClient *client)
	{
		int written;
//		TODO:Some something when no BODY;
		if (!body) {
			client->sendBody();
			return 0;
		}
		if (dynamic_cast<TextBody*>(body))
			written = sendTextBody(dynamic_cast<TextBody*>(body), client);
		else if (dynamic_cast<FileBody*>(body))
			written = sendFileBody(dynamic_cast<FileBody*>(body), client);
		else
			throw ft::runtime_error("RESPONSE SENDER: WRONG TYPE OF BODY GOT");
		#ifdef DEBUG
			std::cout << "SENDER: SEND BODY SIZE: [" << body->size() << "] WRITTEN: [" <<  body->getWritten() << "]\n";
		#endif
	//	std::cout << "WRITTEN: " << written << " [" << client->getSock() << "] \n";
		if (written ==0)
			throw runtime_error();
		if (body->getWritten() >= body->size()) {
			client->sendBody();
			return 0;
		}
		return 1;
	}
}