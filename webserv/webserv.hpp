#pragma once
#include <string>
#include <stdexcept>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
Black        0;30     Dark Gray     1;30
Red          0;31     Light Red     1;31
Green        0;32     Light Green   1;32
Brown/Orange 0;33     Yellow        1;33
Blue         0;34     Light Blue    1;34
Purple       0;35     Light Purple  1;35
Cyan         0;36     Light Cyan    1;36
Light Gray   0;37     White         1;37
*/
namespace ft
{
	static const char reset_[] = "\033[0m";
	static const char red[] = "\033[31m";
	static const char green[] = "\033[32m";
	static const char yellow[] = "\033[33m";

	static const char magenta[] = "\033[1;35m";
	static const char blue[] = "\033[1;34m";
	static const char cyan[] = "\033[0;36m";
	static const char purple[] = "\033[0;35m";

	enum methods_enum
	{
		m_get = 0,
		m_post,
		m_put,
		m_head,
		m_undefined
	};

	void				*ft_memcpy(void *dest, const void *src, unsigned long num);
	unsigned long		ft_strlen(char const *str);
	std::string			getMethodStr(const methods_enum key);
	std::string			getCodeDescr(int code);
	std::string			to_string(int num);
	std::string			getFileExtension(std::string const & filename);
	int					ft_strcmp(const char *string1, const char *string2);
	std::string			fdToString(int fd);
	bool				isNumber(std::string s);
	std::string 		strToLower(const std::string & s);
	unsigned long		get_time_udiff(struct timeval *t1, struct timeval *t2);
	std::vector<std::string> splitString(std::string const & basicString,
										 std::string const & delim);
	void 				currentTimeFormatted(const char *format, char *buf, int bufLen);
	void				rawTimeFormatted(time_t rawTime,const char *format,
						  								char *buf, int bufLen);
	bool				isParsedHeader(std::string const &head);
	unsigned int		getFileSize(const char *path);

	int					ft_close(int fd);

	std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	std::string base64_decode(std::string const &encoded_string);

	std::string readFileIntoString4(const std::string& path);
}
