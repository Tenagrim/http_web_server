#pragma once
#include <IRequestValidator.hpp>
namespace ft
{

	class FakeFakeRequestValidator : public IRequestValidator
	{
	private:
	public:
		FakeFakeRequestValidator();
		virtual ~FakeFakeRequestValidator();
		FakeFakeRequestValidator(const FakeFakeRequestValidator &ref);
		FakeFakeRequestValidator &operator=(const FakeFakeRequestValidator &ref);
		
		int		isValid(const IRequest &req);
		int		isValid(std::string const &line);
		int		isValid(char const *line);

		void reset(void);
		
		
		//optional
		//bool isValid(const IRequest &req, std::string const &http_version);
	};

} // namespace ft