#pragma once

#include <string>

#include <defines.hpp>

#include <IFileManager.hpp>

#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/param.h>
#include <iostream>
#include <runtime_error.hpp>


#ifdef DEBUG	
# include <iostream>
#endif

namespace ft
{
	class FileManager
	{
	private:
		std::string		_root;
		std::string		getPath(std::string const &filename);
	public:
		FileManager();
		virtual ~FileManager();
		FileManager(const FileManager &ref);
		FileManager &operator=(const FileManager &ref);

		bool			isFileExisting(std::string const &filename);
		bool			isADirectory(std::string const &filename);
		unsigned int	getFileSize(std::string const &filename);

		// as in http header content-type
		std::string		getContentType(std::string const &filename);

		// Last modification time
		time_t			getMTime(std::string const &filename);

		// Last change time
		time_t			getCTime(std::string const &filename);

		// open file & returns it's descriptor
		int				getFd(std::string const &filename, unsigned int _acess = O_RDONLY);

		//std::ifstream	getIfstream(std::string const &filename);

		void			setRoot(std::string const &new_root);
		int				copyFdToFile(std::string const &filrname, int input_fd);	
		std::string		getFullPath(std::string const &filename);

		std::string const &getRoot(void);

		class CannotOpenFile : public std::exception { const char * what() const throw(); };
		class NoSuchType : public std::exception { const char * what() const throw(); };
	};

}