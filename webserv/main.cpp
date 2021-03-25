#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>

#include <string.h>
#include <netinet/in.h>


char webpage[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Welcome to nginx!</title>"
"<style>"
"    body {"
"        width: 35em;"
"        margin: 0 auto;"
"        font-family: Tahoma, Verdana, Arial, sans-serif;"
"    }"
"</style>"
"</head>"
"<body>"
"<h1>Welcome to nginx!</h1>"
"<p>If you see this page, the nginx web server is successfully installed and "
"working. Further configuration is required.</p>"

"<p>For online documentation and support please refer to"
"<a href=\"http://nginx.org/\">nginx.org</a>.<br/>"
"Commercial support is available at "
"<a href=\"http://nginx.com/\">nginx.com</a>.</p>"

"<p><em>Thank you for using nginx.</em></p>"
"<img src=\"1.png\">"
"</body>"
"</html>";

/*
"<!DOCTYPE html>\r\n"
"<html><head><title>HelloWorld</title>\r\n"
"</head>"
"<body><center><h1>HELLOWORLD!!</h1><br>\r\n"
"</center></body></html\r\n>>";
*/
int		_ncmp(char *buff, char *str)
{
	return (strncmp(buff, str, strlen(str)));
}

int	ft_sendfile(int out_fd, char *filename)
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

void process(int sockfd)
{
	char					buff[2048];
	int						buffsize = 2048;
	int						n;
	char					*str = "Hello world\n";
	int						fd, len = 0;
	char					c;

	n = read(sockfd, buff, 2048);
	printf("READED: <%d>\n", n);
	write(1, buff, n);

	if (!_ncmp(buff, "GET /1.png"))
		ft_sendfile(sockfd, "1.png");
	if (!_ncmp(buff, "GET /favicon.ico"))
		ft_sendfile(sockfd, "favicon.ico");
	else if (!_ncmp(buff, "GET / HTTP/1.1"))
	{
		n = write(sockfd, webpage, sizeof(webpage) - 1);
		printf("\n<%d> written\n", n);
	}
    if (n < 0)
	{
         printf("ERROR writing to socket");
		 exit(0);
	}
}

int main(int ac, char **av)
{
	struct sockaddr_in		serv_addr;
	struct hostent			*server;
	int						sockfd, port, rc, pid, err, status;
	char					*hostname = "localhost";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	port = 80;

	if (sockfd < 0)
		exit(-1);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if ((err = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
	{
		close(sockfd);
		printf("bind error [%d]\n", err);
		exit(-2);
	}

	if (listen(sockfd, 25) < 0)
	{
		printf("listen error\n");
		exit (-3);
	}

	while (1)
	{
		rc = accept(sockfd, NULL, NULL);
		if (rc == -1)
		{
			printf("Connnection failed...\n");
			continue;
		}
		printf("Connection accepted\n");
		pid = fork();
		if (pid < 0)
		{
			printf("fork error\n");
			exit(-5);
		}
		else if (pid == 0)
		{
			close(sockfd);
			process(rc);
			exit(0);
		}
		else
		{
			close(rc);
			waitpid(pid, &status, 0);
		}
	}

}
