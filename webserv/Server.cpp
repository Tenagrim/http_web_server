#include <Server.hpp>

Server::Server()
{
	port = 80;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Unable to sreate socket");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if ((err = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
	{
		close(sockfd);
		throw std::runtime_error("Unable to bind socket");
	}

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
	//char					buff[2048];
	//int						buffsize = 2048;
	int						n = 0;
	IRequest				*req;

	req = getRequest();
	std::cout << req->getText() << "\n";
	//std::string				&uri = req->getURI();
	/*
	if (!_ncmp(buff, "GET /1.png"))
		ft_sendfile(sockfd, "resources/gshona.png");
	else if (!_ncmp(buff, "GET /favicon.ico"))
		ft_sendfile(sockfd, "resources/favicon.ico");
	else if (!_ncmp(buff, "GET /trump.gif"))
		ft_sendfile(sockfd, "resources/trump.gif");
	else if (!_ncmp(buff, "GET / HTTP/1.1"))
	{
		n = write(sockfd, webpage, sizeof(webpage) - 1);
		printf("\n<%d> written\n", n);
	}
	*/

	std::cout << req->getURI() << " =================\n";

	if (req->getURI() == "/")
		n = write(sockfd, webpage, sizeof(webpage) - 1);
	else if (req->getURI() == "/favicon.ico")
		ft_sendfile(sockfd, "resources/favicon.ico");
	else if (req->getURI() == "/trump.gif")
		ft_sendfile(sockfd, "resources/trump.gif");

    if (n < 0)
         throw std::runtime_error("ERROR writing to socket");
	delete req;
}

IRequest	*Server::getRequest(void)
{
	std::stringstream	ss;
	int					n;
	char				buff[2048];

	n = read(client_fd, buff, 2048);
	if (n == -1)
		throw std::runtime_error("Cannot read client fd");
	ss << buff;
	dprintf(2, "reading finished\n");
	return new Request(ss.str());
}



int			Server::processConnection()
{
	close(sockfd);
	process(rc);
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
	return (1);
}




int			Server::sendResponce(const IResponse &resp)
{
	throw std::runtime_error("No implementation");
	return (-1);
}