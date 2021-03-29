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
		HeaderType										_type;
	public:
		Header();
		~Header();
		Header(const Header &ref);
		Header				&operator=(const Header &ref);
		
		std::string			to_string(void);
		
		std::string const	&getHeaderValue(header_keys_enum key);
		HeaderType			getType(void) const;
		int					getResponseCode(void) const;
		std::string			&getURI(void);
		std::string			&getHTTPVersion(void);
		methods_enum		getMethod(void) const; // GET / POST
		std::string			&getCodeDescription(void);

		void				setType(HeaderType new_type);
		void				setHTTPV(std::string const &new_vers);
		void				setMethod(methods_enum new_meth);
		void				setResponseCode(int new_code);
		void				setURI(std::string const &new_uri);
		void				setHeader(header_keys h_key, std::string const &header_value);
		void				setCodeDescription(std::string const &new_descr);

	};
#include <Header.hpp>

	#pragma region Copilen
	Header::Header()
	{}

	Header::~Header()
	{
	}

	Header::Header(const Header &ref)
	{
		*this = ref;
	}

	Header &Header::operator=(const Header &ref)
	{
		this->_header_map = ref._header_map;
		return (*this);
	}
	#pragma endregion

	#pragma region Getters
	std::string const	&Header::getHeaderValue(header_keys_enum key)
	{
		if (!_header_map.count(key))
			throw std::runtime_error("Header not exists");
		return _header_map[key];
	}

	HeaderType			Header::getType(void) const
	{
		return _type;
	}
	
	int					Header::getResponseCode(void)const
	{
		return _resp_code;
	}

	std::string			&Header::getURI(void)
	{
		return _uri;
	}

	std::string			&Header::getHTTPVersion(void)
	{
		return _http_v;
	}

	methods_enum		Header::getMethod(void) const
	{
		return _method;
	}
	std::string			&Header::getCodeDescription(void)
	{
		return _code_descr;
	}
	#pragma endregion

	#pragma region Setters
	void				Header::setType(HeaderType new_type)
	{
		_type = new_type;
	}

	void				Header::setHTTPV(std::string const &new_vers)
	{
		_http_v = new_vers;
	}

	void				Header::setMethod(methods_enum new_meth)
	{
		_method = new_meth;
	}

	void				Header::setURI(std::string const &new_uri)
	{
		_uri = new_uri;
	}

	void				Header::setHeader(header_keys h_key, std::string const &header_value)
	{
		_header_map[h_key] = header_value;
	}
	
	void				Header::setResponseCode(int new_code)
	{
		_resp_code = new_code;
	}

	void				Header::setCodeDescription(std::string const &new_descr)
	{
		_code_descr = new_descr;
	}
	#pragma endregion

	std::string			Header::to_string(void)
	{
		std::stringstream ss;
		if (_type == request)
		{
			ss << getMethodStr(_method) << " " << _uri << " " << _http_v << "\r\n";
		}
		else if (_type == response)
		{
			ss << _http_v << " " << _resp_code << " " << _code_descr << "\r\n";
		}
		else
			throw std::runtime_error("Unknown type of header");
		header_map::iterator it = _header_map.begin();
		for (; it != _header_map.end(); it++)
			ss << (*it).second << "\r\n";
		ss << "\r\n";
		//std::map<header_keys, std::string>::iterator = _header_map.begin()
		return (ss.str());	
	}
}