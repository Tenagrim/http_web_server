#pragma once
#include <map>
#include <webserv.hpp>
#include <IHeader.hpp>
#include <sstream>

namespace ft
{
	class Header : public IHeader
	{
	private:
		typedef std::map<header_keys_enum, std::string>	header_map;
		//std::map<header_keys_enum, std::string>				_header_map;
		header_map										_header_map;
		methods_enum									_method;
		std::string										_uri;
		std::string										_http_v;
		std::string										_code_descr;
		int												_resp_code;
		MessageType										_type;
		Header();
	public:
		Header(MessageType type);
		~Header();
		Header(const Header &ref);
		Header				&operator=(const Header &ref);
		
		std::string			to_string(void);
		
		std::string const	&getHeaderValue(header_keys_enum key);
		MessageType			getType(void) const;
		int					getResponseCode(void) const;
		std::string			&getURI(void);
		std::string			&getHTTPVersion(void);
		methods_enum		getMethod(void) const; // GET / POST
		std::string			&getCodeDescription(void);

		void				setType(MessageType new_type);
		void				setHTTPV(std::string const &new_vers);
		void				setMethod(methods_enum new_meth);
		void				setResponseCode(int new_code);
		void				setURI(std::string const &new_uri);
		void				setHeader(header_keys h_key, std::string const &header_value);
		void				setCodeDescription(std::string const &new_descr);

	};

}