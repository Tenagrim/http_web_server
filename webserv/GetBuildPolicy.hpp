#pragma once
#include <ABuildPolicy.hpp>
namespace ft
{

	class GetBuildPolicy : public ABuildPolicy
	{
	private:
		GetBuildPolicy(const GetBuildPolicy &ref);
		static int 		_count;
	public:
		static int getCount();

	public:
		GetBuildPolicy();
		virtual ~GetBuildPolicy();
		GetBuildPolicy	&operator=(const GetBuildPolicy &ref);
		IResponse		*buildResponse(IRequest *request);

		IResponse *buildIfNoLocation(IRequest *request);
	};

} // namespace ft