#include <Server.hpp>

int main(int ac, char **av)
{
	(void)ac; // FIXME
	(void)av; // FIXME
	
	ft::Server		serv = ft::Server();

	//int			pid;
	while (1)
	{
		serv.acceptConnection();
		//pid = fork();
		//if (pid < 0)
		//{
		//	printf("fork error\n");
		//	exit(-5);
		//}
		//else if (pid == 0)
			serv.processConnection();
		//else
		//	serv->parentForkPart();
	}


	//Request req("GET / HTTP/1.1\r\n");




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
