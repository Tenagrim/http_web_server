#include <FakeRequestValidator.hpp>

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
	bool		FakeRequestValidator::isValid(std::string const &line)
	{
		(void)line;
		return true;
	}
	bool		FakeRequestValidator::isValid(const IRequest &req)
	{
		(void)req;
		return true;
	}

	void		FakeRequestValidator::reset(void)
	{}
} // namespace ft