//
// Created by Skipjack Adolph on 3/29/21.
//
#include <webserv.hpp>
#include <iostream>
#include <vector>

int main() {
	std::string s = "123;;;1234;;;12345;;;123456;;;1234567;;;12345678;;;;;;;123;;;";
	std::string delim = ";;;";
	std::vector<std::string> split;

	split = ft::splitString(s, delim);
	for (std::vector<std::string>::iterator i = split.begin(); i < split.end(); i++) {
		std::cout << "|" << *i << "|" << std::endl;
	}

	return 0;
}
