//
// Created by Skipjack Adolph on 4/4/21.
//

#include <HeaderMaker.hpp>
#include <Header.hpp>
#include <BodyReader.hpp>

namespace ft {

	std::string HeaderMaker::readHeader(Client *client, char *buff) {
		int end_pos;
		int ending;
		std::string bodyPart;
		if (client->getStates() == Client::s_start_header_reading)
				client->getLastRequest()->setHeader(new Header(request));

		if (buff[0] == 0) // if we got only \0
		{
			client->setStates(Client::s_header_readed);
			client->setFlag(Client::read_flags, Client::r_end);
			client->getLastRequest()->getHeader()->makeInvalid();
			return "";
		}

		client->getReadBuff().append(buff);

		end_pos = client->getReadBuff().find("\r\n\r\n");
		ending = 4;
		if (end_pos == std::string::npos) {
			end_pos = client->getReadBuff().find("\n\n");
			ending = 2;
		}

		if (end_pos != std::string::npos)
		{
			if (client->getReadBuff().size() > end_pos + ending) {
				bodyPart = client->getReadBuff().substr(end_pos + ending);
			}
			client->resizeReadBuff(end_pos + ending / 2);

			ft::HeaderMaker::headerBuilder(client->getReadBuff(),
										   client->getLastRequest()->getHeader(), client->getStates());

			if (!client->getLastRequest()->getHeader()->isValid()) {
				client->setStates(Client::s_end_reading);
				client->setFlag(Client::read_flags, Client::r_end);
				return "";
			}
			client->setStates(Client::s_header_readed);
			client->setFlag(Client::read_flags, Client::r_end);
		}
		else
			client->setStates(Client::s_header_reading);
		return bodyPart;
	}

	void HeaderMaker::headerBuilder(const std::string &text, IHeader *header,
									Client::req_r_states &state) {
		std::string subLine;
		strPos pos1 = 0, pos2;
		int ending;

		while (header->isValid()) {
			pos2 = text.find("\r\n", pos1);
			ending = 2;
			if (pos2 == std::string::npos) {
				pos2 = text.find("\n", pos1);
				ending = 1;
				if (pos2 == std::string::npos)
					break;
			}
			subLine = text.substr(pos1, pos2 - pos1);
			subLine.erase(std::remove(subLine.begin(), subLine.end(), '\r'),
						  subLine.end());
			pos1 = pos2 + ending;
			switch (state) {
				case Client::s_start_header_reading:
					firstLine(subLine, header, state);
					break;
				case Client::s_header_reading:
					fillHeader(subLine, header, state);
					break;
			}
		}
	}

	void HeaderMaker::fillHeader(std::string subLine, IHeader *header,
									 Client::req_r_states &states) {
		int i = 0;
		header_keys a;
		std::string head;
		std::string key;

		head = subLine.substr(0, subLine.find(':'));
		do {
			a = static_cast<header_keys>(i);
			i++;
		} while (!(key = getHeaderKey(a)).empty() && strToLower(key) != strToLower(head));
		if (key.empty())
			return;
		if (header->isHeadAlreadyExist(a)) {
			header->makeInvalid();
			return;
		}
		subLine = subLine.substr(subLine.find(':') + 1);
		while (subLine[0] == ' ') {
			subLine.erase(0, 1);
		}
		header->setHeader(a, subLine);
	}

	void HeaderMaker::firstLine(std::string const &line, IHeader *header,
									Client::req_r_states &state) {
		fillMethod(line, header);
		fillUrl(line, header);
		checkHttp(line, header);
		state = Client::s_header_reading;
	}

	void HeaderMaker::fillMethod(const std::string &line, IHeader *header) {
		std::string method;
		int i = 0;
		methods_enum a;

		method = line.substr(0, line.find(' '));
		try {
		do {
			a = static_cast<methods_enum>(i);
			i++;
		} while (method != getMethodStr(a));
		}
		catch (ft::runtime_error) {
			header->makeInvalid();
		}
		header->setMethod(a);
	}

	void HeaderMaker::fillUrl(const std::string &line, IHeader *header) {
		strPos a = line.find(' ') + 1;
		strPos b = line.rfind(' ');

		header->setURI(line.substr(a, b - a));
	}

	void HeaderMaker::checkHttp(const std::string &line, IHeader *header) {
		std::string http;

		http = line.substr(line.rfind(' ') + 1);
		if (http != "HTTP/1.1")
			header->makeInvalid();
	}

	void HeaderMaker::validateHeader(IHeader *header) {
		if (!header->isFieldInHeader(h_host)) {
			header->makeInvalid();
			return;
		}

		if (methodNeedsBody(header->getMethod())) {

			if ((!header->isFieldInHeader(h_content_length) &&
				 !header->isFieldInHeader(h_transfer_encoding))
				||
				(header->isFieldInHeader(h_content_length) &&
				 header->isFieldInHeader(h_transfer_encoding))) {
				header->makeInvalid();
				return;
			}

			if (header->isFieldInHeader(h_content_length)) {
				if (isNumber(header->getHeader(h_content_length))) {
					if (strtol(header->getHeader(h_content_length).c_str(), NULL, 10) < 0
						|| errno == ERANGE) {
						header->makeInvalid();
						return;
					}
				} else {
					header->makeInvalid();
					return;
				}
			}

			if (header->isFieldInHeader(h_transfer_encoding)) {
				if (header->getHeader(h_transfer_encoding) != "chunked") {
					header->makeInvalid();
					return;
				}
			}
		}
	}

	bool HeaderMaker::methodNeedsBody(methods_enum method) {
		return (method == m_post || method == m_put);
	}

	int HeaderMaker::getContLen(const IHeader &header) {
		long int contLen;

		if (header.isFieldInHeader(h_content_length)) {
			std::string s = header.getHeader(h_content_length);
			contLen = strtol(s.c_str(), nullptr, 10);
		} else
			contLen = LEN_CHUNKED;
		return contLen;
	}

}