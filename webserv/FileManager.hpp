#pragma once

#include <IFileManager.hpp>
#include <string>
#include <fstream>

#include <defines.hpp>

#ifdef DEBUG	
# include <iostream>
#endif

namespace ft
{
	class FileManager : public IFileManager
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
		int				getFd(std::string const &filename, int _acess);
		//std::ifstream	getIfstream(std::string const &filename);

		void			setRoot(std::string const &new_root);
		std::string		getFullPath(std::string const &filename);

		class CannotOpenFile : public std::exception { const char * what() const throw(); };
		class NoSuchType : public std::exception { const char * what() const throw(); };
	};

}