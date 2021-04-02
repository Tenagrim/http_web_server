#include <FileBody.hpp>

namespace ft
{
	FileBody::FileBody()
	{/* Illegal */}
	FileBody::FileBody(unsigned int size, int opened_fd) :_size(size), _fd(opened_fd), _path("no")
	{}
	FileBody::FileBody(unsigned int size, int opened_fd, std::string const &path) :_size(size), _fd(opened_fd), _path(path)
	{}

	FileBody::~FileBody()
	{
		if (_fd != -1)
		close(_fd);
	}

	FileBody::FileBody(const FileBody &ref)
	{/* Illegal */ (void)ref; }

	FileBody &FileBody::operator=(const FileBody &ref)
	{
		(void)ref;
		throw ft::runtime_error("No implementation");
		return (*this);
	}

	std::string		FileBody::readFile(void) const
	{

		std::stringstream	ss;
		std::ifstream		fin(_path, std::ios::binary);
		if (fin.good())
		{
			ss << fin.rdbuf();
			return(ss.str());
		}
		else
			return ("CAN\'T READ FILE BODY");
	}

	int					FileBody::getFd(void)
	{
		return(_fd);
	}

	std::string			FileBody::to_string(void) const
	{
		if (_path == "no")
			return ("DO\'NT READ MY FD");
		else
			return(readFile());
	}
	unsigned int		FileBody::size(void) const
	{
		return _size;
	}
	BodyType			FileBody::getType(void)
	{
		throw ft::runtime_error("Not implemented");
	}
}