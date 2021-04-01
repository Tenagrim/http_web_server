#pragma once
#include <ABuildPolicy.hpp>
namespace ft
{

	class GetBuildPolicy : public ABuildPolicy
	{
	private:
		GetBuildPolicy();
		GetBuildPolicy(const GetBuildPolicy &ref);
	public:
		GetBuildPolicy(IFileManager *mngr, ITimeMachine *machine);
		~GetBuildPolicy();
		GetBuildPolicy	&operator=(const GetBuildPolicy &ref);
		IResponse		*buildResponse(IRequest *request);
	};

} // namespace ft