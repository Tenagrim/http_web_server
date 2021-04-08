//
// Created by Gerry Shona on 4/8/21.
//
#include <sys/stat.h>
#include <string>
#include <runtime_error.hpp>
namespace ft {
	unsigned int getFileSize(const char *path)
	{
		struct stat statbuf = {};
		int ret;

		ret = stat(path, &statbuf);
		if (ret == -1)
			throw ft::runtime_error("Stat failed: filename:" + std::string(path));
		return statbuf.st_size;
	}
}