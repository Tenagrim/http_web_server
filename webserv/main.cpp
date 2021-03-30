#include <Server.hpp>
#include <ConfigParser.hpp>

#include <signal.h> // FIXME
#include <Dispatcher.hpp>
#include <FileManager.hpp>
#include <ResponseBuilder.hpp>
#include <ResponseSender.hpp>

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
//	(void)ac; // FIXME
//	(void)av; // FIXME

//TODO: if you need to start server commit "Config Parser"
	ft::ConfigParser parser;
//	ft::Server		serv = ft::Server();
	(void)ac; // FIXME
	(void)av; // FIXME

//	ft::Dispatcher			dispatcher;
//	ft::FileManager			fmngr;
//	ft::ResponseBuilder		resp_builder(&fmngr);
//	ft::ResponseSender		sender(&dispatcher);
//	ft::Server				serv = ft::Server(&dispatcher, &sender, &resp_builder);
//
//	serv.start();
//
//	SERVER = &serv;
//	signal(SIGINT, &sigint_handler);
//
//	struct sockaddr addr;
//
//
//
//	while (1)
//	{
//		dispatcher.updateEvents();
//		dispatcher.handleEvents();
//		usleep(2 * 1000 * 1000);
//	}



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
