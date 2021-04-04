#pragma once
#include <string>
#include <stdexcept>
namespace ft
{
	enum header_keys
	{
		h_accept_charsets = 0,
		h_accept_language,
		h_allow,
		h_authorization,
		h_content_language,
		h_content_length,
		h_content_location,
		h_content_type,
		h_date,
		h_host,
		h_last_modified,
		h_location,
		h_referer,
		h_retry_after,
		h_server,
		h_transfer_encoding,
		h_user_agent,
		h_www_authenticate,
		h_connection
	};

	enum methods_enum
	{
		m_get = 0,
		m_post,
		m_put,
		m_undefined
	};
	void				*ft_memcpy(void *dest, const void *src, unsigned long num);
	unsigned long		ft_strlen(char const *str);
	std::string			getHeaderKey(header_keys key);
	std::string			getMethodStr(const methods_enum key);
	std::string			getCodeDescr(int code);
	std::string			to_string(int num);
	std::string			getFileExtension(std::string const & filename);
	bool				isNumber(std::string s);

}