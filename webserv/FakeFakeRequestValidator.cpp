#include <FakeFakeRequestValidator.hpp>

namespace ft
{
	FakeFakeRequestValidator::FakeFakeRequestValidator()
	{
	}

	FakeFakeRequestValidator::~FakeFakeRequestValidator()
	{
	}

	FakeFakeRequestValidator::FakeFakeRequestValidator(const FakeFakeRequestValidator &ref)
	{
		(void)ref;
	}

	FakeFakeRequestValidator &FakeFakeRequestValidator::operator=(const FakeFakeRequestValidator &ref)
	{
		(void)ref;
		return (*this);
	}
	/*
	bool		FakeFakeRequestValidator::isValid(const IRequest &req, std::string const &http_version)
	{
		(void)req;
		(void)http_version;
		return true;
	}
	*/
	int		FakeFakeRequestValidator::isValid(std::string const &line)
	{
		(void)line;
		return 1;
	}
	int		FakeFakeRequestValidator::isValid(char const *line)
	{
		(void)line;
		return 1;
	}
	int		FakeFakeRequestValidator::isValid(const IRequest &req)
	{
		(void)req;
		return 1;
	}

	void		FakeFakeRequestValidator::reset(void)
	{}
} // namespace ft