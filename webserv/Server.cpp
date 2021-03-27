#include <Server.hpp>

Server::Server()
{
	bool st = false;
	port = 80;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Unable to sreate socket");




	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_port = port; // htons(port);  //FIXME ?
	serv_addr.sin_port =  htons(port);  //FIXME ?
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	//std::cout << "htons port: " << htons(port) << "\n";

	do{
		if ((err = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
		{
			close(sockfd);
			//throw std::runtime_error("Unable to bind socket");
			printf("Unable to bind socket [%d]\n", err);
			usleep(10 * 1000 * 1000);
		}
		else
			st = true;
	}while(!st);

	int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");

	//if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1)
	///	throw std::runtime_error("FCNTL NONBLOCK FAILED");

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
	{
		n = write(client_fd, webpage_header, sizeof(webpage_header) - 1);
		n = write(client_fd, webpage_body, sizeof(webpage_body) - 1);
	}
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

	printf("GET REQUEST\n");
	n = read(client_fd, buff, 2047);
	if (n == 0)
		throw std::runtime_error("Empty read");
	buff[n] = 0;
	if (n == -1)
		throw std::runtime_error("Cannot read client fd");
	ss << buff;
	dprintf(2, "reading finished\n");
	return new Request(ss.str());
}



int			Server::processConnection()
{
	bool cont = true;
	printf("PROCESS CONNECTION\n");
	do
	{	
		//close(sockfd);
		try
		{
			process(rc);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			cont = false;
		}
		
	} while (cont);
	close(rc);
	printf("EXIT CONNECTION\n");
	//exit(0);
	return (1);
}

unsigned int			Server::get_file_size(std::string const &filename)
{
	std::ifstream	in_file(filename, std::ios::binary);
	
	in_file.seekg(0, std::ios::end);
	return(in_file.tellg());
}

int						Server::ft_sendfile(int out_fd, char *filename)
{
	char					buff[2048];
	const int				buffsize = 2048;
	int						fd, n, size = 0;
	std::stringstream		ss;
	std::string				str;
	unsigned int			file_size;
	char					*head_str;

	printf("SENDFILE: %s\n", filename);


	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("file %s cannot be opened\n", filename);
		return (0);
	}

	file_size = get_file_size(std::string(filename));
	std::cout << "FILE SIZE: " << file_size << "\n";


	ss << "HTTP/1.1 200 OK\r\n";
	ss << "Connection: keep-alive\r\n";
	ss << "Accept-Ranges: bytes\r\n";
	ss << "Content-Length: "<< file_size <<"\r\n";
	//ss << "Content-Type: image\r\n";
	ss << "\r\n";
	
	str = ss.str();
	std::cout << "HEADER:\n";
	std::cout << "===============\n"<< str << "\n=========\n";
	std::cout << "WRITE HEADER\n";
	write(out_fd, str.c_str(), str.size());
	std::cout << "HEADER WRITTEN\n";

	while ( (n = read(fd, buff, buffsize)) > 0)
	{
		//std::cout << "BEGIN ["<< n <<"]\n";
		write(out_fd, buff, n);
		//std::cout << "END\n";
	}
	close(fd);
	std::cout << "FILE SENDED\n";
	return (1);
}




int			Server::sendResponce(const IResponse &resp)
{
	throw std::runtime_error("No implementation");
	return (-1);
}

bool		Server::hasFlag(unsigned int flag)
{
	if (_flags & flag)
		return (true);
	else
		return (false);
}
int			Server::setFlag(unsigned int flag)
{
	_flags |= flag;
	return(1);
}
int			Server::switchFlag(unsigned int flag)
{
	_flags ^= flag;
	return (1);
}