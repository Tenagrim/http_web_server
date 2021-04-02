#include <FakeRequestValidator.hpp>
#include <iostream>

namespace ft
{
	FakeRequestValidator::FakeRequestValidator()
	{
	}

	FakeRequestValidator::~FakeRequestValidator()
	{
	}

	FakeRequestValidator::FakeRequestValidator(const FakeRequestValidator &ref)
	{
		(void)ref;
	}

	FakeRequestValidator &FakeRequestValidator::operator=(const FakeRequestValidator &ref)
	{
		(void)ref;
		return (*this);
	}
	/*
	bool		FakeRequestValidator::isValid(const IRequest &req, std::string const &http_version)
	{
		(void)req;
		(void)http_version;
		return true;
	}
	*/
	int FakeRequestValidator::isValid(std::string const &line)
	{
		(void)line;
		return true;
	}
	int FakeRequestValidator::isValid(const IRequest &req)
	{
		(void)req;
		return true;
	}

	void		FakeRequestValidator::reset(void)
	{}

	FakeRequestValidator::FakeRequestValidator(const std::string &text) {
		state = readin;
		process = start;
		strPos pos1 = 0;
		strPos pos2 = 0;

		while (state == readin) {
			switch (process) {
				case start: valiateStartLine(pos1, pos2); break;
				case header: valiateHeader(pos1, pos2); break;
				case body:
//				TODO body
//				write Content-Length symbols into file, start from pos2
					break;
			}
		}
		if (state == error)
//			TODO requests without body - valid case
			throw std::runtime_error("RequestValidator: no body");
	}

//	TODO REPLACE ALL REQ (using for tests) INTO REQUEST TEXT
	void FakeRequestValidator::valiateHeader(strPos &pos1, strPos &pos2) {
		std::string line;
		int i = 0;
		header_keys a;

		if ((pos2 = req.find("\r\n", pos1)) != std::string::npos) {
			line = req.substr(pos1, pos2);
			pos2 = pos1 + 2;
			do {
				a = static_cast<header_keys>(i);
				i++;
			}
			while (line != getHeaderKey(a));
			if (_header.find(a) == _header.end())
				throw std::runtime_error("RequestValidator: the header field is duplicate");
			line = line.substr(line.find(' ') + 1);
			_header.insert(std::pair<header_keys, std::string>(a, line));
		} else if ((pos2 = req.find('\n', pos1)) != std::string::npos) {
			pos2++;
			process = body;
		} else
			state = error;
	}

	void FakeRequestValidator::valiateStartLine(strPos &pos1, strPos &pos2) {
		std::string line;

		if ((pos2 = req.find("\r\n", pos1)) != std::string::npos) {
			line = req.substr(pos1, pos2);
			pos2 = pos1 + 2;
			fillMethod(line);
			fillUrl(line);
			checkHttp(line);
			process = header;
		} else
			state = error;

	}

	void FakeRequestValidator::fillMethod(const std::string &line) {
		std::string method;
		int i = 0;
		methods_enum a;

		method = line.substr(0, line.find(' '));
		do {
			a = static_cast<methods_enum>(i);
			i++;
		}
		while (method != getMethodStr(a));
		_method = a;
	}

	void FakeRequestValidator::fillUrl(const std::string &line) {
		strPos a = line.find(' ') + 1;
		strPos b = line.rfind(' ');

		_url = line.substr(a, b - a);
	}

	void FakeRequestValidator::checkHttp(const std::string &line) {
		std::string http;

		http = line.substr(line.rfind(' ') + 1, 8);
		if (http != "HTTP/1.1")
			throw std::runtime_error("RequestValidator: invalid HTTP version");
	}

} // namespace ft