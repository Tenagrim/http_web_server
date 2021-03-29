#include <FileManager.hpp>
namespace ft
{
	FileManager::FileManager()
	{
	}

	FileManager::~FileManager()
	{
	}

	FileManager::FileManager(const FileManager &ref)
	{
	}

	FileManager		&FileManager::operator=(const FileManager &ref)
	{
		return (*this);
	}

	bool			FileManager::isFileExisting(std::string const &filename)
	{

	}

	unsigned int	FileManager::getFileSize(std::string const &filename)
	{

	}

	std::string		FileManager::getContentType(std::string const &filename)
	{

	}

	time_t			FileManager::getMTime(std::string const &filename)
	{

	}

	time_t			FileManager::getCTime(std::string const &filename)
	{

	}

	int				FileManager::getFd(std::string const &filename)
	{

	}
}