#include <Server.hpp>

Server::Server()
{
	bool st = false;
	port = 80;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Unable to sreate socket");


	int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	do{
		if ((err = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
		{
			close(sockfd);
			//throw std::runtime_error("Unable to bind socket");
			printf("Unable to bind socket\n");
			usleep(10 * 1000 * 1000);
		}
		else
			st = true;

	}while(!st);
	printf("========= Socket binded ======\n");
	if (listen(sockfd, 25) < 0)
	{
		printf("listen error\n");
		throw std::runtime_error("Unable to listen socket");
	}
}

Server::~Server()
{}

Server::Server(const Server &ref)
{
}

Server	&Server::operator=(const Server &ref)
{
	return (*this);
}

int			Server::acceptConnection()
{
	client_fd = accept(sockfd, NULL, NULL);
	if (client_fd == -1)
		throw std::runtime_error("Connection failed...");
}

int			Server::process(int sockfd)
{
	int						n = 0;
	IRequest				*req;

	req = getRequest();
	std::cout << "\nTEXT:\n" << req->getText() << "\n";

	//std::cout << "URI: " << req->getURI() << " =================\n";

	if (req->getURI() == "/")
		n = write(client_fd, webpage2, sizeof(webpage2) - 1);
	else if (req->getURI() == "/favicon.ico")
		ft_sendfile(client_fd, "resources/favicon.ico");
	else if (req->getURI() == "/trump.gif")
	{
		ft_sendfile(client_fd, "resources/trump.gif");
	}

	std::cout << "WRITING COMPLETED\n";

    if (n < 0)
         throw std::runtime_error("ERROR writing to socket");
	printf("EXIT FROM PROCESS\n");
	delete req;
}

IRequest	*Server::getRequest(void)
{
	std::stringstream	ss;
	int					n;
	char				buff[2048];

	n = read(client_fd, buff, 2047);
	buff[n] = 0;
	if (n == -1)
		throw std::runtime_error("Cannot read client fd");
	ss << buff;
	dprintf(2, "reading finished\n");
	return new Request(ss.str());
}



int			Server::processConnection()
{
	printf("PROCESS CONNECTION\n");
	close(sockfd);
	process(rc);
	close(rc);
	exit(0);
	return (1);
}

int			Server::parentForkPart()
{
	close(rc);
	return (1);
}



int						Server::_ncmp(char *buff, char *str)
{
	return (strncmp(buff, str, strlen(str)));
}

int						Server::ft_sendfile(int out_fd, char *filename)
{
	char					buff[2048];
	const int				buffsize = 2048;
	int						fd, n;

	printf("SENDFILE: %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("file %s cannot be opened\n", filename);
		return (0);
	}
	while ( (n = read(fd, buff, buffsize)) > 0)
		write(out_fd, buff, n);
	close(fd);
	std::cout << "FILE SENDED\n";
	return (1);
}




int			Server::sendResponce(const IResponse &resp)
{
	throw std::runtime_error("No implementation");
	return (-1);
}