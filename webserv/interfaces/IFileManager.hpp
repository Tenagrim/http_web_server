#pragma once
#include <string>
#include <time.h>

namespace ft
{
	class IFileManager
	{
		public:
			virtual	bool			isFileExisting(std::string const &filename) = 0;
			virtual unsigned int	getFileSize(std::string const &filename) = 0;

			// as in http header content-type
			virtual std::string		getContentType(std::string const &filename) = 0;

			// Last modification time 
			virtual time_t			getMTime(std::string const &filename) = 0;

			// Last change time 
			virtual time_t			getCTime(std::string const &filename) = 0;

			// returns opened file descriptor
			virtual int				getFd(std::string const &filename) = 0;
			virtual void			setRoot(std::string const &new_root) = 0;

			virtual ~IFileManager(){}	
	};
}