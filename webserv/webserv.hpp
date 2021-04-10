#pragma once
#include <string>
#include <stdexcept>
#include <sys/time.h>
namespace ft
{
	static const char reset[] = "\033[0m";
	static const char red[] = "\033[31m";
	static const char green[] = "\033[32m";
	static const char yellow[] = "\033[33m";

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
	void 				currentTimeFormatted(char *format, char *buf, int bufLen);
	void				rawTimeFormatted(time_t rawTime,const char *format,
						  								char *buf, int bufLen);
	bool				isParsedHeader(std::string const & head);

	bool				methodNeedsBody(methods_enum method);
	unsigned int		getFileSize(const char *path);

	int					ft_close(int fd);
}
