#include <Server.hpp>
#include <ConfigParser.hpp>

#include <signal.h> 
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

#define	DISPATCHER_TICK_MICROS (0.5 * 1000 * 1000)
//								^ seconds


int main(int ac, char **av)
{

//TODO: if you need to start server commit "Config Parser"
//	ft::ConfigParser parser;
//	ft::Server		serv = ft::Server();

	(void)ac; // FIXME
	(void)av; // FIXME

	ft::Dispatcher			dispatcher;
	ft::FileManager			fmngr;
	ft::ResponseBuilder		resp_builder(&fmngr);
	ft::ResponseSender		sender(&dispatcher);
	ft::Server				serv(&dispatcher, &sender, &resp_builder);

	
	SERVER = &serv;
	signal(SIGINT, &sigint_handler);
	
	serv.addListener(DEFAULT_PORT);
	serv.addListener(93);
	serv.addListener(97);
	serv.addListener(85);

	dispatcher.connectToServer(&serv);
	serv.start();

	while (1)
	{
		dispatcher.updateEvents();
		dispatcher.handleEvents();
		usleep(DISPATCHER_TICK_MICROS);
	}

	// TODO: классы-наследники от Header: ReaponseHeader и  RequestHeader
	// TODO: Раздельное чтение запроса
	// TODO: Закрывать соединение когда в сокете конец файла
	// TODO: починить сегу при SIGINT'e во время отправки файла
	// TODO: УТЕЧКА ДЕСКРИПТОРОВ!!!!!!
	// TODO: Отследить единоновременые события чтения и записи

}
