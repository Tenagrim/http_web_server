//
// Created by Skipjack Adolph on 3/29/21.
//
#include <FileManager.hpp>
#include <iostream>

int main() {
	ft::FileManager file;

	try {
////	isFileExisting
		std::cout << file.isFileExisting("/Makefile") << std::endl;
////	getContentType
		std::cout << file.getContentType("test.html") << std::endl;
////	setRoot
		file.setRoot("/root/newroot");
////	getFD
		file.getFdReadOnly("/Makefile");
////	getTime
		std::cout << file.getCTime("/Makefile") << std::endl;
	}
	catch (std::exception & ex) {
		std::cerr << ex.what() << std::endl;
	}
}
