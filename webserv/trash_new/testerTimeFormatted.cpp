//
// Created by Skipjack Adolph on 3/29/21.
//
#include <iostream>
#include <webserv.hpp>
#include <defines.hpp>

//05-Apr-2021 11:05

int main() {
	char buf[TIME_BUFF_AUTOINDEX];

	buf[TIME_BUFF_AUTOINDEX -1] = '\0';
	ft::currentTimeFormatted("%d-%b-%Y %H-%M", buf, TIME_BUFF_AUTOINDEX);
	std::cout << buf << std::endl;
	return 0;
}
