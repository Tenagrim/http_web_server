#include <src/core/Server.hpp>
#include <ConfigParser.hpp>

#include <signal.h>
#include <FileManager.hpp>
#include <ResponseBuilder.hpp>

#include <Request.hpp>
#include <defines.hpp>

ft::Server	*SERVER;

void	sigint_handler(int sig)
{
	(void)sig;
	std::cout <<  "\n\nSIGINT catched\nABORTING...\n";
	//SERVER->abort();
	SERVER->stop();
	std::cout <<  "SERVER STOPPED\n\n" ;
	exit(2);
}

int main(int ac, char **av)
{
	(void)ac; // FIXME:
	(void)av; // FIXME:

//TODO: if you need to start server commit "Config Parser"
	ft::ConfigParser parser;
	parser.firstStep(ac, av);
////////// PRIMARY PART ///////////////////////////////////////////////////////////////

	ft::FileManager			fmngr;
	ft::ResponseBuilder		resp_builder;

	ft::Server				serv(&resp_builder);

	SERVER = &serv;
	signal(SIGINT, &sigint_handler);
	signal(SIGTERM, &sigint_handler);

	std::list<ft::ServerInit *> serv_list = parser.getServerList();
	std::list<ft::ServerInit *>::iterator serv_it = serv_list.begin();
//Config Lists in Response

	resp_builder.getConfigLists(&serv_list);
	for (; serv_it != serv_list.end(); ++serv_it) {
		std::list<int> list_listner = (*serv_it)->getListenPorts();
		list_listner.sort();
		list_listner.unique();
		std::list<int>::iterator it = list_listner.begin();
		for (; it != list_listner.end(); ++it){
			serv.addListener(*it);
		}
	}

	serv.start();

////////////////////////////////////////////////////////////////////////////////

}
