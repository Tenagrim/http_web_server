#include <FileManager.hpp>
#include <Utils.hpp>

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
//		if (file.back() == '/')
//			file.erase(file.end() - 1);
		if (!stat(file.c_str(), &statbuf))
			return S_ISDIR(statbuf.st_mode);
		else
			return -1;
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
		int ret;

		file = getPath(filename);
		//file = _root + filename;
		ret = stat(file.c_str(), &statbuf);
		if (ret == -1)
			throw ft::runtime_error("Stat failed: filename:" + filename);
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
		int			fdFileTypes;
		char 		*line;

		tmp = FM_DEFAULT_ROOT;
//		todo hardcode=(
		tmp.resize(tmp.size() - 26);
		tmp += "/utils/mimi_types.txt";

		if ((fdFileTypes = open(tmp.c_str(), O_RDONLY)) < 0)
			throw CannotOpenFile();
		extension = filename.substr(filename.find('.') + 1);
		while (get_next_line(fdFileTypes, &line)) {
			buf = line;
			tmp = buf.substr(buf.find(' ') + 1);
			if (tmp == extension) {
				close(fdFileTypes);
				return buf.substr(0, buf.find(' '));
			}
		}
		close(fdFileTypes);
		return "";
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

	int				FileManager::getFd(std::string const &filename, unsigned int _acess)
	{
		int fd;
		std::string file;

		file = getPath(filename);
		fd = open(file.c_str(), _acess);
		#ifdef DEBUG
		std::cout << "FILE MANAGER: GET FD: [" << fd << "] ["<< file << "]\n";

		//char buff[10];
		//read(fd, buff, 9);
		//buff[9] = 0;
		//std::cout << "CONT: [" << buff<< "]\n";
		#endif
		if (fd < 0)
			throw CannotOpenFile();
		return fd;
	}

	void            FileManager::setRoot(const std::string &new_root) {
		_root = new_root;
	}


	const char *FileManager::CannotOpenFile::what() const throw() {
		return "FileManager: Cannot open file";
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

		mkdir_p(filename.substr(0, filename.rfind('/')));

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
		ft_close(fd);
		return 1;
	}

	int FileManager::mkdir_p(const std::string &dir_name)
	{
		int ret;
		if (dir_name == "/" || dir_name.empty()) {
			return 1;
		}
		std::string tmp = dir_name;
		if (tmp.back() == '/')
			tmp.erase(tmp.end()--);
		if (!isFileExisting(tmp)) {
			tmp = dir_name.substr(0, dir_name.rfind('/'));
		 	ret = mkdir_p(tmp);
		 	if (ret == 1) {
		 		ret = mkdir(getPath(dir_name).c_str(), 0755);
		 		if (ret == -1)
					throw ft::runtime_error("mkdir failed");
		 	}
		}
		return 1;
	}
}
