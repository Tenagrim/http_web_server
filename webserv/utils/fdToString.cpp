//
// Created by Gerry Shona on 4/4/21.
//
#include <string>
#define BUFF_SIZE 512
#include <unistd.h>
#include <runtime_error.hpp>
namespace ft {
	std::string fdToString(int fd) {
		char buff[BUFF_SIZE];
		int readed = 0;
		std::string res = "";

		do {
			readed = read(fd, buff, BUFF_SIZE - 1);
			if (readed == -1)
				throw ft::runtime_error("READING FILE FAILED");
			buff[readed] = 0;
			res.append(buff);
		} while (readed == BUFF_SIZE - 1);
//		ft_close(fd);
		return res;
	}
}