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

//		if (resp->getBody() && resp->getBody()->size() < 2048)
//			return sendFullResponse(resp, client);
//		if (resp->getBody())
//			std::cout<<"FILE FD IN BODY : "<<resp->getBody()->getOpenedFd() << " ["<< resp->getBody()->getId() <<"]" <<std::endl;

		client->updateEventTime();

		if (!client->headerSent())
		{
			ret = sendHeader(resp->getHeader(), client);
			if (ret == -1)
				return -1;
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
	
	int ResponseSender::sendHeader(IHeader *header, IClient *client)
	{
		std::string str;
		int ret;

		str = header->to_string();
		ret = write(client->getSock(), str.c_str(),str.size());
		if (ret  == -1)
			return -1;
		client->sendHeader();
		return ret;
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
		//if (ret == -1)
		//	throw ft::runtime_error("FAILED TO WRITE RESP: (Write returned -1)");
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
			if (retr == -1)
				throw ft::runtime_error("SEND FILE BODY: UNABLE TO OPEN FILE FOR READING");
			body->setReaded(retr);
		}
		else
		{
			retr = body->getReaded() - body->getWritten();
			offset = READ_BODY_ONE_TIME - retr;
			std::cout << green << "PARTIAL SEND: ";
			write(1, green , ft::ft_strlen(green));
			write(1, buff + offset, 20);
			write(1, "\n", 1);
			write(1, reset_ , ft::ft_strlen(reset_));
		//	std::cout << "R: ["<< body->getReaded() <<"] W: ["<< body->getWritten() <<"] RETR: ["<<retr <<"]  OFFSET: ["<< offset <<"]\n";
		}

			retw = send(client->getSock(), buff + offset, retr, 0);

		//std::cout << "SEND : "<< retw <<" ["<< client->getSock() <<"]\n";
		if (body->getWritten() + 10 < READ_BODY_ONE_TIME) {
			//std::cout << magenta;
			write(1, magenta , ft::ft_strlen(magenta));
			write(1, buff, 20);
			write(1, "\n", 1);
			write(1, reset_ , ft::ft_strlen(reset_));

//			std::cout << reset_;
		}

		if (retw == -1)
				return -1;
			if (retw == 0 || retr == 0 || retr == -1 || retw == -1 || offset < 0)
				throw ft::runtime_error("SOMETHING WENT WRONG - ResponseSender::sendFileBody" + to_string(retw) +
										to_string(retr) + to_string(offset) + to_string(client->getSock()));
			body->setWritten(retw);
			std::cout << yellow << "[" << client->getSock() << "] SENDED : " << body->getWritten() << "  OF : " << body->size() << " [" << client->requests() << "] " << reset_ << "\n";
		return retw;
	}

	int ResponseSender::sendBody(IBody *body, IClient *client)
	{
		int written = -1;
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
			if (written == -1)
				return -1;
		//std::cout << "WRITTEN: " << written << " [" << client->getSock() << "] ["<< body->getOpenedFd() <<"]  \n";
		//if (written == 0 || )
		//	throw runtime_error();
		if (body->getWritten() >= body->size()) {
			client->sendBody();
			return 0;
		}
		return 1;
	}

	int ResponseSender::sendFullResponse(IResponse *resp, IClient *client) {
		std::string str = resp->to_string();
		size_t ret;
		ret = send(client->getSock(), str.c_str(), str.size(), 0);
		if (ret == str.size())
			return 0;
		else throw ft::runtime_error("SERVER CANNOT HANDLE RESPONSE AS FULL");
	}
}