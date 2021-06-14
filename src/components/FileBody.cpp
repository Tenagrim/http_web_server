#include <src/components/FileBody.hpp>
#include <iostream>


namespace ft
{
	unsigned  int FileBody::_max_id = 0;
	FileBody::FileBody() : _size(0), _opened_fd(-1)
	{/* Illegal */}

	FileBody::~FileBody()
	{
		if (_opened_fd != -1) {
			std::cout << "FILE BODY DESTR : " << _opened_fd <<" ["<<_id <<"] \n";
			ft_close(_opened_fd);
			_opened_fd = -1;
		}
	}

	FileBody::FileBody(const FileBody &ref) : _size(0), _opened_fd(-1)
	{/* Illegal */ (void)ref; }

	FileBody::FileBody(std::string const &path, int offset) : _filename(path), _opened_fd(-1), _offset(offset)
	{
		int ret;

		struct stat statbuf = {};
		ret = stat(_filename.c_str(), &statbuf);
		if (ret == -1)
			throw ft::runtime_error("Stat failed: filename:" + _filename);
		_size = statbuf.st_size;
		_id = _max_id;
		_max_id++;
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
		ret = open(_filename.c_str(), O_RDONLY);

		if (ret == -1)
			throw ft::runtime_error("FILE BODY: CANNOT OPEN FILE FOR READING");
		if (_offset)
			if (lseek(ret, _offset, SEEK_SET) == -1)
				throw ft::runtime_error("FILE BODY: CANNOT SEEK IN FILE");
		return(ret);
	}

	std::string			FileBody::to_string()
	{
		int fd = getFd();

		std::string  res = ft::fdToString(fd);
		ft_close(fd);
		return (res);
	}

	unsigned int		FileBody::size() const
	{
		return _size - _offset;
	}

	BodyType			FileBody::getType()
	{
		throw ft::runtime_error("Not implemented");
	}

	int FileBody::getOpenedFd() {
		if (_opened_fd == -1)
		{
			_opened_fd = getFd();
//			_opened_fd = open(_filename.c_str(), O_RDONLY, 0666);
//			if (_opened_fd == -1)
//				throw ft::runtime_error("FILE BODY: CANNOT OPEN FILE FOR READING");
		}
		return _opened_fd;
	}

	int FileBody::getOffset() const {
		return _offset;
	}

	unsigned int FileBody::getId() const {
		return _id;
	}

	unsigned int FileBody::getMaxId() {
		return _max_id;
	}

}