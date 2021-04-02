#pragma once
#include <IRequestValidator.hpp>
namespace ft
{

	class FakeRequestValidator : public IRequestValidator
	{
	private:
	public:
		FakeRequestValidator();
		virtual ~FakeRequestValidator();
		FakeRequestValidator(const FakeRequestValidator &ref);
		FakeRequestValidator &operator=(const FakeRequestValidator &ref);
		
		int		isValid(const IRequest &req);
		int		isValid(std::string const &line);
		int		isValid(char const *line);

		void reset(void);
		
		
		//optional
		//bool isValid(const IRequest &req, std::string const &http_version);
	};

} // namespace ft