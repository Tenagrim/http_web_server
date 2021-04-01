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
	}

	FakeRequestValidator &FakeRequestValidator::operator=(const FakeRequestValidator &ref)
	{
		return (*this);
	}
	bool		FakeRequestValidator::isValid(const IRequest &req, std::string const &http_version)
	{
		return true;
	}
	bool		FakeRequestValidator::isValid(std::string const &line)
	{
		return true;
	}
	bool		FakeRequestValidator::isValid(const IRequest &req)
	{
		return true;
	}

	void		FakeRequestValidator::reset(void)
	{}
} // namespace ft