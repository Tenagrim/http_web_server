#pragma once
#include <IRequest.hpp>
#include <string>
class IRequestValidator
{
public:
	virtual bool	isValid(const IRequest &req) =0;
	virtual bool	isValid(const IRequest &req, std::string const &http_version) =0;
	virtual bool	isValidFirstLine(std::string const &line) = 0;
	virtual bool	isValidHeader(std::string const &h_line) = 0;
};