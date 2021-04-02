#pragma once
#include <ABuildPolicy.hpp>
namespace ft
{

	class PutBuildPolicy : public ABuildPolicy
	{
	private:
		PutBuildPolicy(const PutBuildPolicy &ref);

	public:
		PutBuildPolicy();
		virtual ~PutBuildPolicy();
		PutBuildPolicy &operator=(const PutBuildPolicy &ref);
		IResponse		*buildResponse(IRequest *request);
	};
} // namespace ft