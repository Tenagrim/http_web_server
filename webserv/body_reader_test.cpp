//
// Created by Gerry Shona on 4/3/21.
//
#include <BodyReader.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include <FileBody.hpp>

void 	print_fd(int fd)
{
	int ret;
	char buff[250];

	do {
		std::cout << "READING ["<< fd <<"]\n";
		ret = read(fd, buff, 249);
		if(ret == -1) {
			std::cout << "\nCANT READ BODY\n";
			return;
		}
		buff[ret] = 0;
		std::cout << buff;
	} while (ret == 249);
	std::cout << "\n";
}

int main()
{
	char str[] =
			"6789\r\n7\r\n123456789\r\n0\r\n\r\n";
	char str2[] =
			"9\r\n123456789\r\n9\r\n12345";


	int _pipe[2];
	int ret;
	pipe(_pipe);

	dprintf(_pipe[1], str, sizeof (str));
	close(_pipe[1]);

	//print_fd(_pipe[0]);


	ft::BodyReader reader(_pipe[0], LEN_CHUNKED, std::string(str2));

	do {
		ret = reader.readBody();
	} while (ret == 1);

	ft::FileBody *body = new ft::FileBody(reader.getSize(), reader.get_resultFd());
	if (ret == -1)
		std::cout << "WRONG BODY\n";
	else
		print_fd(reader.get_resultFd());

//	std::cout << body->to_string() << "\n";
};