//
// Created by Gerry Shona on 4/6/21.
//
#include <BasicRequest.hpp>
#include <TextBody.hpp>
#include <Header.hpp>
#include <CgiModule.hpp>
#include <iostream>
int main()
{
	ft::CgiModule module;
	ft::Header *head = new ft::Header(ft::request);
	ft::TextBody * body= new ft::TextBody("123.bla");
	ft::BasicRequest *req = new ft::BasicRequest(head, body);

	head->setHeader(ft::h_content_length, ft::to_string(body->size()));

	head->setURI("/123.bla");
	head->setMethod(ft::m_post);
	head->setHeader(ft::h_host, "localhost");

	module.setRoot("/Users/gshona/Desktop");
	module.setExecutable("/Users/gshona/Desktop/cgi_tester");

	ft::IResponse	*resp = module.getResponse(req);
	std::string res;
	try {
		res  = ft::fdToString(open(TMP_OUT, O_RDONLY));
	}
	catch (ft::runtime_error)
	{
		std::cout << "CANNOT READ FILE\n";
	}
	std::cout << "====================\n" <<req->to_string() <<"\n=====================\n";
	if (resp)
	{
		std::cout << ">>>>>>>>>>>>>>>>>>>>\n" <<resp->to_string() <<"\n=====================\n";
		std::cout << "====================\n" <<res <<"\n=====================\n";
	}
	else
		std::cout << "====================\n" <<res <<"\n=====================\n";
}