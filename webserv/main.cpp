#include <Server.hpp>
#include <ConfigParser.hpp>

#include <signal.h>
#include <FileManager.hpp>
#include <ResponseBuilder.hpp>


#include <Request.hpp>
#include <defines.hpp>

////// TODO: LIST////////////////////////////////////////////////////////////////////
	// TODO: классы-наследники от Header: ReaponseHeader и  RequestHeader
	// TODO: Раздельное чтение запроса
	// TODO: Закрывать соединение когда в сокете конец файла
	// TODO: починить сегу при SIGINT'e во время отправки файла
	// TODO: УТЕЧКА ДЕСКРИПТОРОВ!!!!!!
	// TODO: Отследить единоновременые события чтения и записи
	// TODO: Autoindexer
	// TODO: Раскидать проект по папкам, настроить мейкфайл
	// TODO: Кастомные еррор-пейджи из конфига
	// TODO: Раздельное чтение 
	// TODO: Перейти на евенты (чтоб по-взрослому было)
	// TODO: Красивое логгирование
	// TODO: Засунуть в бод тип контента
	// TODO: Fake Request Validator 
	// TODO: УТЕЧКА ПАМЯТИ !!!!!!!!!!!!!!!
	// TODO: Засунуть  диспетчера в сервер
	// TODO: Несколько билдеров по методам
	// TODO: Раскидать файлы по папкам
	// TODO: 
	// TODO: 


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
//	ft::ConfigParser parser;
//	ft::Server		serv = ft::Server();
////////// PRIMARY PART ///////////////////////////////////////////////////////////////

	ft::FileManager			fmngr;
	ft::ResponseBuilder		resp_builder;

	ft::Server				serv(&resp_builder);

	
	SERVER = &serv;
	signal(SIGINT, &sigint_handler);
	
	serv.addListener(DEFAULT_PORT);
	serv.addListener(93);
	serv.addListener(97);
	serv.addListener(85);

	serv.start();

////////////////////////////////////////////////////////////////////////////////

}
