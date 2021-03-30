#include <FileManager.hpp>
#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/param.h>

#include <iostream>
namespace ft
{

	FileManager::FileManager()
	{
		char 		dir[MAXPATHLEN];

		getcwd(dir, MAXPATHLEN);
		this->_root = dir;
		std::cout << "root: " << _root << std::endl;
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

	bool			FileManager::isFileExisting(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;

		file = _root + filename;
		return !stat(file.c_str(), &statbuf);
	}

	unsigned int	FileManager::getFileSize(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;

		file = _root + filename;
		stat(file.c_str(), &statbuf);
		return statbuf.st_size;
	}

	std::string		FileManager::getContentType(std::string const &filename)
	{
		std::string extension;
		std::string buf;
		std::string tmp;
		char 		dir[MAXPATHLEN];

		getcwd(dir, MAXPATHLEN);
		tmp = dir;
		tmp = tmp.substr(0, tmp.rfind('/'));
		tmp += "/webserv/utils/mimi_types.txt";
		std::ifstream fileTypes(tmp);
		if (!fileTypes)
			throw CannotOpenFile();
		extension = filename.substr(filename.find('.') + 1);
		while (std::getline(fileTypes, buf)) {
			tmp = buf.substr(buf.find(' ') + 1);
			if (tmp == extension) {
				fileTypes.close();
				return buf.substr(0, buf.find(' '));
			}
		}
		fileTypes.close();
		throw NoSuchType();
	}

	time_t			FileManager::getMTime(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;

		file = _root + filename;
		stat(file.c_str(), &statbuf);
		return statbuf.st_mtime;
	}

	time_t			FileManager::getCTime(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;

		file = _root + filename;
		stat(file.c_str(), &statbuf);
		return statbuf.st_ctime;
	}

	int				FileManager::getFd(std::string const &filename, unsigned int _acess)
	{
		int fd;
		std::string file;

		file = _root + filename;
		fd = open(file.c_str(), _acess);
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	int				FileManager::getFdReadOnly(std::string const &filename)
	{
		int fd;
		std::string file;

		file = _root + filename;
		fd = open(file.c_str(), O_RDONLY);
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	int				FileManager::getFdWriteOnly(std::string const &filename)
	{
		int fd;
		std::string file;

		file = _root + filename;
		fd = open(file.c_str(), O_WRONLY);
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	int				FileManager::getFdReadWrite(const std::string &filename) {
		int fd;
		std::string file;

		file = _root + filename;
		fd = open(file.c_str(), O_RDWR);
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	void            FileManager::setRoot(const std::string &new_root) {
		char 		dir[MAXPATHLEN];

		getcwd(dir, MAXPATHLEN);
		this->_root = dir + new_root;
		std::cout << "set root: " << _root << std::endl;
	}

	const char *FileManager::CannotOpenFile::what() const throw() {
		return "FileManager: Cannot open file";
	}

	const char *FileManager::NoSuchType::what() const throw() {
		return "FileManager: getContentType: Nginx doesn't support this file type";
	}
}
