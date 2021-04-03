#pragma once
#include <ABody.hpp>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <runtime_error.hpp>
namespace ft
{
	class FileBody : public ABody
	{
	private:
		unsigned int	_size;
		int				_fd;
		int				_inp_fd;
		std::string		_path;

		FileBody();
		FileBody(const FileBody &ref);
		std::string		readFile() const;
	public:
		FileBody(unsigned int size, int opened_fd);
		FileBody(unsigned int size, int opened_fd, std::string const &path);
		~FileBody();
		FileBody &operator=(const FileBody &ref);

		int					getFd();
		int					getInputFd();
		std::string			to_string() const;
		unsigned int		size() const;
		BodyType			getType();
	};
}