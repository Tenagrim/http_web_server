#pragma once
#include <string>
#include <time.h>
#include <fstream>
#include <fcntl.h>
namespace ft
{
	class IFileManager
	{
		public:
			virtual	bool			isFileExisting(std::string const &filename) = 0;
			virtual	bool			isADirectory(std::string const &filename) = 0;
			virtual unsigned int	getFileSize(std::string const &filename) = 0;

			// as in http header content-type
			virtual std::string		getContentType(std::string const &filename) = 0;

			// Last modification time 
			virtual time_t			getMTime(std::string const &filename) = 0;

			// Last change time 
			virtual time_t			getCTime(std::string const &filename) = 0;

			// open file & returns it's descriptor
			virtual int				getFd(std::string const &filename, unsigned int acess = O_RDONLY) = 0;
			virtual int				getFdReadOnly(std::string const &filename) = 0;
			virtual int				getFdWriteOnly(std::string const &filename) = 0;
			virtual int				getFdReadWrite(std::string const &filename) = 0;
			virtual void			setRoot(std::string const &new_root) = 0;
			virtual std::string		getFullPath(std::string const &filename) = 0;
			//virtual std::ifstream	getIfstream(std::string const &filename) = 0;

			virtual ~IFileManager(){}	
	};
}