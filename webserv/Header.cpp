#include <Header.hpp>

namespace ft
{
	

	#pragma region Copilen
	Header::Header() : _http_v(DEFAULT_HTTPV)
	{}

	Header::Header(MessageType type) :  _method(m_undefined), _http_v(DEFAULT_HTTPV), _type(type), _isValid(true)
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
	std::string const	&Header::getHeader(std::string const & key) const
	{
		if (!isFieldInHeader(key))
			throw ft::runtime_error("Header not exists");
		return (*(_header_map.find(key))).second;
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

	void				Header::setHeader(std::string const & key, std::string const &header_value)

	{
		_header_map[strToLower(key)] = header_value;
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

//	TODO stringstream here
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

	bool Header::isValid() {
		return _isValid;
	}

	void Header::makeInvalid() {
		_isValid = false;
	}

	bool Header::isFieldInHeader(std::string const & key) const {
		return _header_map.count(strToLower(key));
	}

	std::string Header::getPath() {
		int pos = _uri.find('?');
		if ((size_t)pos == std::string::npos)
			return _uri;
		return _uri.substr(0, pos);
	}

	std::string Header::getQuery() {
		int pos = _uri.find('?');
		if ((size_t)pos != std::string::npos)
			return _uri.substr(pos);
		else
			return "";
	}

	void Header::setEnvs(Environment &env) {
		for (header_map::iterator it = _header_map.begin(); it != _header_map.end(); it++) {
			if (!isParsedHeader((*it).first))
				env.setVar(headToEnvFormat((*it).first), (*it).second);
		}
	}

	std::string Header::headToEnvFormat(const std::string &s) {
		std::string		res;
		size_t			i = -1;

		while (s[++i]) {
			if (s[i] == '-')
				res	+= '_';
			else
				res += std::toupper(s[i]);
		}
		return res;
	}

} // namespace ft