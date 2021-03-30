#pragma once
#include <IBody.hpp>
#include <unistd.h>
#include <fstream>
#include <sstream>
namespace ft
{
	class FileBody : public IBody
	{
	private:
		unsigned int	_size;
		int				_fd;
		std::string		_path;
		FileBody();
		FileBody(const FileBody &ref);
		std::string		readFile(void) const;
	public:
		FileBody(unsigned int size, int opened_fd);
		FileBody(unsigned int size, int opened_fd, std::string const &path);
		~FileBody();
		FileBody &operator=(const FileBody &ref);

		bool				getFd(void);
		std::string			to_string(void) const;
		unsigned int		size(void) const;
		BodyType			getType(void);
	};


}