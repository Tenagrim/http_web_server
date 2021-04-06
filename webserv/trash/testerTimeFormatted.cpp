//
// Created by Skipjack Adolph on 3/29/21.
//
#include <iostream>
#include <webserv.hpp>
#include <defines.hpp>

int main() {
	char buf[TIME_BUFF_AUTOINDEX];

	ft::timeFormatted("%d-%b-%Y %H-%M", buf, TIME_BUFF_AUTOINDEX);
	std::cout << buf << std::endl;
	return 0;
}
