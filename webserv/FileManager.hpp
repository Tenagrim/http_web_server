#pragma once
#include <IFileManager.hpp>

#include <string>
namespace ft
{
	class FileManager : public IFileManager
	{
	private:
		std::string		_root;
	public:
		FileManager();
		virtual ~FileManager();
		FileManager(const FileManager &ref);
		FileManager &operator=(const FileManager &ref);

		bool			isFileExisting(std::string const &filename);
		unsigned int	getFileSize(std::string const &filename);

			// as in http header content-type
		std::string		getContentType(std::string const &filename);

			// Last modification time 
		time_t			getMTime(std::string const &filename);

			// Last change time 
		time_t			getCTime(std::string const &filename);

			// returns opened file descriptor
		int				getFd(std::string const &filename);
		void			setRoot(std::string const &new_root);
	};

}