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
			if (resp->getBody() && resp->getBody()->size()) //&& resp->getHeader()->getResponseCode() != 405)
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
		int retw, retr, offset = 0;
		char *buff = body->getBuff(READ_BODY_ONE_TIME);

		//int lr = body->lastReaded();

		if (body->getReaded() == body->getWritten()) {
			retr = read(body->getOpenedFd(), buff, READ_BODY_ONE_TIME);
			body->setReaded(retr);
		}
		else
		{
			retr = body->getReaded() - body->getWritten();
			offset = READ_BODY_ONE_TIME - retr;
		//	std::cout << "R: ["<< body->getReaded() <<"] W: ["<< body->getWritten() <<"] RETR: ["<<retr <<"]  OFFSET: ["<< offset <<"]\n";
		}

			retw = send(client->getSock(), buff + offset, retr, 0);
				if (retw == 0 || retr == 0 || retr == -1 || retw == -1 || offset < 0)
					throw ft::runtime_error("SOMETHING WENT WRONG");
				body->setWritten(retw);
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
		//std::cout << "WRITTEN: " << written << " [" << client->getSock() << "] ["<< body->getOpenedFd() <<"]  \n";
		//if (written == 0 || )
		//	throw runtime_error();
		if (body->getWritten() + body->getOffset() >= body->size()) {
			client->sendBody();
			return 0;
		}
		return 1;
	}

	int ResponseSender::sendFullResponse(IResponse *resp, IClient *client) {
		std::string str = resp->to_string();
		int ret;
		ret = send(client->getSock(), str.c_str(), str.size(), 0);
		if (ret == str.size())
			return 0;
		else throw ft::runtime_error("SERVER CANNOT HANDLE RESPONSE AS FULL");
	}
}