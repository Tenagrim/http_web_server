#pragma once
#include <map>
#include <webserv.hpp>
#include <IHeader.hpp>
#include <sstream>
#include <runtime_error.hpp>
#include <defines.hpp>

namespace ft
{
	class Header : public IHeader
	{
	private:
		typedef std::map<std::string, std::string>	header_map;

		header_map			_header_map;
		methods_enum		_method;
		std::string			_uri;
		std::string			_http_v;
		std::string			_code_descr;
		int					_resp_code;
		MessageType			_type;
		bool 				_isValid;
		Header();
		std::string 		headToEnvFormat(const std::string & s);

	public:
		explicit Header(MessageType type);
		~Header();
		Header(const Header &ref);
		Header				&operator=(const Header &ref);

		std::string			to_string(void);

		MessageType			getType(void) const;
		int					getResponseCode(void) const;
		std::string			&getURI(void);
		std::string			&getHTTPVersion();
		methods_enum		getMethod() const; // GET / POST
		std::string			&getCodeDescription();

		void				setType(MessageType new_type);
		void				setHTTPV(std::string const &new_vers);
		void				setMethod(methods_enum new_meth);
		void				setResponseCode(int new_code);
		void				setURI(std::string const &new_uri);
		void				setCodeDescription(std::string const &new_descr);

		void				setHeader(std::string const & key, std::string const &header_value);
		std::string const	&getHeader(std::string const & key) const;
		bool 				isValid();
		void 				makeInvalid();
		bool 				isFieldInHeader(std::string const & key) const;
		void 				setEnvs(Environment &env);

		std::string 		getPath();
		std::string 		getQuery();

		unsigned long		size();

	};

}