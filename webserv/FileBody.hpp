#pragma once
#include <ABody.hpp>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <runtime_error.hpp>
#include <fcntl.h>
#include <sys/stat.h>
#include <webserv.hpp>
namespace ft
{
	class FileBody : public ABody
	{
	private:
		unsigned int	_size;
		std::string		_filename;

		FileBody();
		FileBody(const FileBody &ref);
		std::string		readFile() const;
	public:
		FileBody(std::string const &path);
		~FileBody();
		FileBody &operator=(const FileBody &ref);

		int					getFd();
		std::string			to_string();
		unsigned int		size() const;
		BodyType			getType();
	};
}