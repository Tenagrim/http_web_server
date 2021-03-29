#include <FileManager.hpp>
#include <sys/stat.h>
#include <fstream>

#include <iostream>

namespace ft
{

	FileManager::FileManager()
	{
	}

	FileManager::~FileManager()
	{
	}

	FileManager::FileManager(const FileManager &ref)
	{
	}

	FileManager		&FileManager::operator=(const FileManager &ref)
	{
		return (*this);
	}
//	TODO it's better to check ENOENT here (errno for non-existing file error)
	bool			FileManager::isFileExisting(std::string const &filename)
	{
		struct stat statbuf = {};

		return !stat(filename.c_str(), &statbuf);
	}

	unsigned int	FileManager::getFileSize(std::string const &filename)
	{
		struct stat statbuf = {};

		stat(filename.c_str(), &statbuf);
		return statbuf.st_size;
	}

	std::string		FileManager::getContentType(std::string const &filename)
	{
		std::string extension;
		std::string buf;
		std::ifstream fileTypes(filename);

		extension = filename.substr(filename.find('.') + 1);
		while (std::getline(fileTypes, buf))
			if (buf.substr(filename.find(' ') + 1) == extension)
				return buf.substr(0, filename.find(' '));
		throw std::runtime_error("FileManager: getContentType: Nginx doesn't support file type ." + extension);
	}

	time_t			FileManager::getMTime(std::string const &filename)
	{
		struct stat statbuf = {};

		stat(filename.c_str(), &statbuf);
		return statbuf.st_mtime;
	}

	time_t			FileManager::getCTime(std::string const &filename)
	{
		struct stat statbuf = {};

		stat(filename.c_str(), &statbuf);
		return statbuf.st_ctime;
	}

	int				FileManager::getFd(std::string const &filename)
	{

	}

	void            FileManager::setRoot(const std::string &new_root) {
		this->_root = new_root;
	}
}