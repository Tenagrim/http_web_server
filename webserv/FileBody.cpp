#include <FileBody.hpp>

namespace ft
{
	FileBody::FileBody() : _size(0), _opened_fd(-1)
	{/* Illegal */}

	FileBody::~FileBody()
	{
		if (_opened_fd != -1)
			close(_opened_fd);
	}

	FileBody::FileBody(const FileBody &ref) : _size(0), _opened_fd(-1)
	{/* Illegal */ (void)ref; }

	FileBody::FileBody(const std::string &path) : _filename(path), _opened_fd(-1)
	{
		int ret;

		struct stat statbuf = {};
		ret = stat(_filename.c_str(), &statbuf);
		if (ret == -1)
			throw ft::runtime_error("Stat failed: filename:" + _filename);
		_size = statbuf.st_size;
	}
	FileBody &FileBody::operator=(const FileBody &ref)
	{
		(void)ref;
		throw ft::runtime_error("No implementation");
		return (*this);
	}

	std::string		FileBody::readFile() const
	{

		std::stringstream	ss;
		std::ifstream		fin(_filename, std::ios::binary);
		if (fin.good())
		{
			ss << fin.rdbuf();
			return(ss.str());
		}
		else
			return ("CAN\'T READ FILE BODY");
	}

	int					FileBody::getFd()
	{
		int ret;
		ret = open(_filename.c_str(), O_RDONLY, 0666);
		if (ret == -1)
			throw ft::runtime_error("FILE BODY: CANNOT OPEN FILE FOR READING");
		return(ret);
	}

	std::string			FileBody::to_string()
	{
		int fd = getFd();
		std::string  res = ft::fdToString(fd);
		close(fd);
		return (res);
	}

	unsigned int		FileBody::size() const
	{
		return _size;
	}

	BodyType			FileBody::getType()
	{
		throw ft::runtime_error("Not implemented");
	}


	int FileBody::getOpenedFd() {
		if (_opened_fd == -1)
		{
			_opened_fd = open(_filename.c_str(), O_RDONLY, 0666);
			if (_opened_fd == -1)
				throw ft::runtime_error("FILE BODY: CANNOT OPEN FILE FOR READING");
		}
		return _opened_fd;
	}

}