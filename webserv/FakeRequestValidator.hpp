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
		
		bool isValid(const IRequest &req);
		bool isValid(std::string const &line);
		void reset(void);
		
		
		//optional
		bool isValid(const IRequest &req, std::string const &http_version);
	};

} // namespace ft