//
// Created by Gerry Shona on 4/3/21.
//
#include <BodyReader.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include <src/components/FileBody.hpp>
#include <FileManager.hpp>
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
//	ft::FileManager fm;

//	int rr;
	//rr =fm.getFileSize("123");
	//ft::BodyReader::_max_id = 0;

	char str2[] =
			"9\r\n123456799\r\n9\r\n123456489\r";
	char str[] =
			"\n10\r\n1234r6799sssssss\r\n0\r\n\r\n";


	int _pipe[2];
	int ret;
	pipe(_pipe);

	dprintf(_pipe[1], str, sizeof (str));
	ft_close(_pipe[1]);

	//print_fd(_pipe[0]);

	ft::BodyReader reader(_pipe[0], LEN_CHUNKED, std::string(str2));

	do {
		ret = reader.readBody();
	} while (ret == 1);
	ft_close (_pipe[0]);
	ft::IBody *body = reader.getBody();
	if (ret == -1)
		std::cout << "WRONG BODY\n";
	else {
		//print_fd(reader.get_resultFd());
		std::cout << body->to_string() << "\n";
		std::cout << body->to_string() << "\n";
		std::cout << body->to_string() << "\n";
	}

//	std::cout << body->to_string() << "\n";
};