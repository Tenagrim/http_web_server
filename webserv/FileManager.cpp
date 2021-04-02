#include <FileManager.hpp>

namespace ft
{

	FileManager::FileManager()
	{
		//char 		dir[MAXPATHLEN];

		//getcwd(dir, MAXPATHLEN);
		this->_root = FM_DEFAULT_ROOT;
		//std::cout << "root: " << _root << std::endl;
	}

	FileManager::~FileManager()
	{
	}

	FileManager::FileManager(const FileManager &ref) : _root(ref._root)
	{
	}

	FileManager		&FileManager::operator=(const FileManager &ref)
	{
		_root = ref._root;
		return (*this);
	}

	std::string		FileManager::getPath(std::string const &filename)
	{
		std::string file;
		if (_root.back() != '/' && filename.front() != '/')
			file = _root + '/' + filename;
		else
			file = _root + filename;
		return file;
	}

	bool			FileManager::isADirectory(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;
		file = _root + filename;
		stat(file.c_str(), &statbuf);
		return S_ISDIR(statbuf.st_mode);	
	}

	bool			FileManager::isFileExisting(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;
		
		file = getPath(filename);
		
		#ifdef DEBUG
			std::cout << "FILE MANAGER: IS FILE EXISTS: [" << file << "]\n";
		#endif

		return !stat(file.c_str(), &statbuf);
	}

	unsigned int	FileManager::getFileSize(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;

		file = getPath(filename);
		//file = _root + filename;
		stat(file.c_str(), &statbuf);
		return statbuf.st_size;
	}

	std::string		FileManager::getFullPath(std::string const &filename)
	{
		return (getPath(filename));
	}

	std::string		FileManager::getContentType(std::string const &filename)
	{
		std::string extension;
		std::string buf;
		std::string tmp;
		char 		dir[MAXPATHLEN];

		getcwd(dir, MAXPATHLEN);
		tmp = dir;
		tmp = tmp.substr(0, tmp.rfind('/'));
		tmp += "/webserv/utils/mimi_types.txt";
		std::ifstream fileTypes(tmp);
		if (!fileTypes)
			throw CannotOpenFile();
		extension = filename.substr(filename.find('.') + 1);
		while (std::getline(fileTypes, buf)) {
			tmp = buf.substr(buf.find(' ') + 1);
			if (tmp == extension) {
				fileTypes.close();
				return buf.substr(0, buf.find(' '));
			}
		}
		fileTypes.close();
		throw NoSuchType();
	}

	time_t			FileManager::getMTime(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;

		file = _root + filename;
		stat(file.c_str(), &statbuf);
		return statbuf.st_mtime;
	}

	time_t			FileManager::getCTime(std::string const &filename)
	{
		struct stat statbuf = {};
		std::string file;

		file = _root + filename;
		stat(file.c_str(), &statbuf);
		return statbuf.st_ctime;
	}
/*
	std::ifstream	FileManager::getIfstream(std::string const &filename)
	{
		std::ifstream res(getPath(filename), std::ios::binary);
		if (res.good())
			return res;
		else
			throw CannotOpenFile();
	}
*/
	int				FileManager::getFd(std::string const &filename, unsigned int _acess)
	{
		int fd;
		std::string file;

		file = getPath(filename);
		fd = open(file.c_str(), _acess);
		#ifdef DEBUG
			std::cout << "FILE MANAGER: GET FD: [" << fd << "] ["<< file << "]\n";
		#endif
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	int				FileManager::getFdReadOnly(std::string const &filename)
	{
		int fd;
		std::string file;

		file = _root + filename;
		fd = open(file.c_str(), O_RDONLY);
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	int				FileManager::getFdWriteOnly(std::string const &filename)
	{
		int fd;
		std::string file;

		file = _root + filename;
		fd = open(file.c_str(), O_WRONLY);
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	int				FileManager::getFdReadWrite(const std::string &filename) {
		int fd;
		std::string file;

		file = _root + filename;
		fd = open(file.c_str(), O_RDWR);
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	void            FileManager::setRoot(const std::string &new_root) {
		_root = new_root;
		
		/*
		char 		dir[MAXPATHLEN];

		getcwd(dir, MAXPATHLEN);
		std::string slash;
		if (new_root[0] != '/')
			slash += '/';
		this->_root = dir + slash + new_root;
		#ifdef DEBUG
			std::cout << "set root: " << _root << std::endl;
		#endif
		*/
	}

	std::string FileManager::getRoot()
	{
		return _root;
	}

	const char *FileManager::CannotOpenFile::what() const throw() {
		return "FileManager: Cannot open file";
	}

	const char *FileManager::NoSuchType::what() const throw() {
		return "FileManager: getContentType: Nginx doesn't support this file type";
	}

	std::string const		&FileManager::getRoot(void)
	{
			return _root;
	}	
	int				FileManager::copyFdToFile(std::string const &filename, int input_fd)
	{
		char	buff[FM_RW_BUFF];
		int		readed = 1, written;
		int 	fd;

		std::string file = getPath(filename);

		fd = open(file.c_str(), O_CREAT | O_RDWR, 0666);
		if (fd < 0)
			throw CannotOpenFile();
		do
		{
			readed = read(input_fd, buff, FM_RW_BUFF);
			written = write(fd, buff, readed);
			if (readed != written)
				throw ft::runtime_error("An error in rewriting file");
		} while (readed != 0);
		return fd;
	}
}
