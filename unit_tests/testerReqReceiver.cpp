//
// Created by Skipjack Adolph on 3/29/21.
//
#include <iostream>
#include <HeaderMaker.hpp>
#include <src/core/Client.hpp>
#include <BasicRequest.hpp>


//	GET / HTTP/1.1\r\nHost: localhost:83\r\nUser-Agent: Go-http-client/1.1\r\nAccept-Encoding: gzip\r\n\r\n
//	POST / HTTP/1.1\r\nHost: localhost:83\r\nUser-Agent: Go-http-client/1.1\r\nTransfer-Encoding: chunked\r\nContent-Type: test/file\r\nAccept-Encoding: gzip\r\n\r\n0\r\n\r\n

int main() {

	std::string get = "GET / HTTP/1.1\r\nUser-Agent: Go-http-client/1.1\r\nHost: localhost:83\r\nAccept-Encoding: gzip\r\n\r\n";
	std::string post = "POST / HTTP/1.1\r\nHost: localhost:83\r\nUser-Agent: Go-http-client/1.1\r\nCoNTent-length: 347052983704\r\nAccept-Encoding: gzip\r\nContent-Language: rus\r\n\r\n0\r\n\r\n";

	ft::Client * client = new ft::Client(0, 77);

	if (client->getStates() == ft::Client::s_not_begin)
		client->setLastRequest(new ft::BasicRequest());
	client->setStates(ft::Client::s_start_header_reading);
	client->setFlag(ft::Client::read_flags, ft::Client::r_begin);

	ft::HeaderMaker::readHeader(client, const_cast<char *>(get.c_str()));
	std::cout << "GET parsed: " << client->getLastRequest()->getHeader()->isValid() << std::endl;
	ft::HeaderMaker::validateHeader(client->getLastRequest()->getHeader());
	std::cout << "GET validated: " << client->getLastRequest()->getHeader()->isValid() << std::endl;

	delete client;

	ft::Client * client1 = new ft::Client(0, 77);

	if (client1->getStates() == ft::Client::s_not_begin)
		client1->setLastRequest(new ft::BasicRequest());
	client1->setStates(ft::Client::s_start_header_reading);
	client1->setFlag(ft::Client::read_flags, ft::Client::r_begin);

	ft::HeaderMaker::readHeader(client1, const_cast<char *>(post.c_str()));
	std::cout << "POST parsed: " << client1->getLastRequest()->getHeader()->isValid() << std::endl;
	ft::HeaderMaker::validateHeader(client1->getLastRequest()->getHeader());
	std::cout << "POST validated: " << client1->getLastRequest()->getHeader()->isValid() << std::endl;

	delete client1;

	return 0;
}
