#include <Header.hpp>

namespace ft
{
	

	#pragma region Copilen
	Header::Header()
	{}

	Header::Header(MessageType type) : _type(type)
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
	std::string const	&Header::getHeader(std::string const & key)
	{
		if (!_header_map.count(key))
			throw ft::runtime_error("Header not exists");
		return _header_map[key];
	}

	MessageType			Header::getType(void) const
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
	void				Header::setType(MessageType new_type)
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

	void				Header::setHeader(std::string const & h_key, std::string const &header_value)

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
			throw ft::runtime_error("Unknown type of header");
		header_map::iterator it;
		for (it = _header_map.begin(); it != _header_map.end(); it++)
			ss << (*it).first << ": " << (*it).second << "\r\n";
		ss << "\r\n";
		//std::map<header_keys, std::string>::iterator = _header_map.begin()
		return (ss.str());	
	}

	unsigned long		Header::size()
	{
		throw ft::runtime_error("not implemented");
		return (0);
	}
} // namespace ft