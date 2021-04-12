#include <Utils.hpp>
#include <webserv.hpp>

namespace ft {
	std::list<std::string> *findAndCut(std::list<std::string> &_list, std::string const &_str) {
		iterator it = ++_list.begin();
//	TODO:   make correct splice with last element
		iterator it_new = std::find(++it, _list.end(), _str);
		std::list<std::string> *tmp = new std::list<std::string>;
		tmp->splice(tmp->begin(), _list, ++it, it_new);
		return tmp;
	}

	std::list<std::string> &findAndErase(std::list<std::string> &_list,const std::string &_start,const std::string
	&_end) {
		iterator start = std::find(_list.begin(), _list.end(), _start);
		iterator end = std::find(start, _list.end(), _end);
		_list.erase(start, ++end);
		return _list;
	};

	void deleteCommit(std::list<std::string> &list) {
		bool res = true;
		while(res) {
			iterator it = std::find(list.begin(), list.end(), "#");
			if (*it == "#")
				ft::findAndErase(list, "#", "\n");
			else
				res = false;
		}
	};

	iterator &isSpace(iterator &it) {
		while (*it == " " || *it == "\t" || *it == "\n")
			++it;
		return it;
	};

	reverse_iterator &isSpace(reverse_iterator &it) {
		while (*it == " " || *it == "\t" || *it == "\n")
			++it;
		return it;
	};

	int temporaryBody(std::string const &str) {
		int fd[2];
		pipe(fd);
		std::string result;
		write(fd[1], str.c_str(), str.size());
		ft_close(fd[1]);
		return fd[0];
	}

	int ft_close(int fd) {
		std::cout<<"Closing FD : "<<fd<<std::endl;
		return close(fd);
	}

	std::string readFileIntoString4(const std::string& path) {
		struct stat sb;
		std::string res;

		int fd = open(path.c_str(), O_RDONLY);
		if (fd < 0) {
			return (res = "");
		}

		fstat(fd, &sb);
		res.resize(sb.st_size);
		read(fd, (char*)(res.data()), sb.st_size);
		close(fd);

		return res;
	}

}