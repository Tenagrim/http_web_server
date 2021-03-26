#include <Server.hpp>

int main(int ac, char **av)
{
	IServer		*serv = new Server();
	int			pid;
	while (1)
	{
		serv->acceptConnection();
		pid = fork();
		if (pid < 0)
		{
			printf("fork error\n");
			exit(-5);
		}
		else if (pid == 0)
			serv->processConnection();
		else
			serv->parentForkPart();
	}

}
