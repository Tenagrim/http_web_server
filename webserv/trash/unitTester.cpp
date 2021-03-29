//
// Created by Skipjack Adolph on 3/29/21.
//
#include <FileManager.hpp>
#include <iostream>

int main() {
	ft::FileManager file;

//	isFileExisting
	std::cout << file.isFileExisting("/Users/sadolph/21/webserv/README.md") << std::endl;
//	getContentType
	std::cout << file.getContentType("/Users/sadolph/21/webserv/README.md") << std::endl;
}
