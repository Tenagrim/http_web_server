#pragma once
#include <string>
class IFileManager
{
	public:
		virtual	bool			isFileExisting(std::string const &filename) = 0;
		virtual unsigned int	getFileSize(std::string const &filename) = 0;
		virtual std::string		getContentType(std::string const &filename) = 0;
};