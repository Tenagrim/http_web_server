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
	int		FakeRequestValidator::isValid(std::string const &line)
	{
		(void)line;
		return 1;
	}
	int		FakeRequestValidator::isValid(char const *line)
	{
		(void)line;
		return 1;
	}
	int		FakeRequestValidator::isValid(const IRequest &req)
	{
		(void)req;
		return 1;
	}

	void		FakeRequestValidator::reset(void)
	{}
} // namespace ft