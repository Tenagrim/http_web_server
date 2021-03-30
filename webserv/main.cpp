#include <Server.hpp>

#include <signal.h> // FIXME
#include <Dispatcher.hpp>
#include <FileManager.hpp>
#include <ResponseBuilder.hpp>
#include <ResponseSender.hpp>


#include <Request.hpp>

ft::Server	*SERVER;
void	sigint_handler(int sig)
{
	(void)sig;
	SERVER->abort();
	printf("\n\nSIGINT catched\n\n");
	exit(2);
}

int main(int ac, char **av)
{
	(void)ac; // FIXME
	(void)av; // FIXME

	ft::Dispatcher			dispatcher;
	ft::FileManager			fmngr;
	ft::ResponseBuilder		resp_builder(&fmngr);
	ft::ResponseSender		sender(&dispatcher);
	ft::Server				serv = ft::Server(&dispatcher, &sender, &resp_builder);

	serv.start();
	
	SERVER = &serv;
	signal(SIGINT, &sigint_handler);
	
	//std::string req = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
	
	
	// std::string req = "GET /some_shit.cpp HTTP/1.1\r\nHost: localhost\r\n\r\n";

	// ft::IRequest *request = new ft::Request(req);
	
	// ft::IResponse *resp = resp_builder.buildResponse(request);

	// std::cout << "REQUEST: ===========================\n" << request->to_string() << "=====================\n";
	// std::cout << "RESPONSE: ==========================\n" << resp->to_string() << "=====================\n";

	while (1)
	{
		dispatcher.updateEvents();
		dispatcher.handleEvents();
		usleep(2 * 1000 * 1000);
	}

	// TODO классы-наследники от Header: ReaponseHeader и  RequestHeader
	
	// TODO Раздельное чтение запроса

	/*
	std::string str("GET /trump.gif HTTP/1.1");
	int pos = str.find(' ');
	std::cout << "[" << str.substr(0, pos) << "]\n";
	int o_pos = pos;
	pos = str.find(' ', o_pos + 1);
	std::cout << "o_pos:"  << o_pos << " pos: " << pos <<"\n";
	std::cout << "[" << str.substr(o_pos + 1, pos - o_pos - 1) << "]\n";
	*/
}
