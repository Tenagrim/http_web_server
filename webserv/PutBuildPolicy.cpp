#include <PutBuildPolicy.hpp>

namespace ft
{
	PutBuildPolicy::PutBuildPolicy()
	{
	}
	PutBuildPolicy::PutBuildPolicy(IFileManager *mngr, ITimeMachine *machine) : ABuildPolicy(mngr,machine)
	{}

	PutBuildPolicy::~PutBuildPolicy()
	{
	}

	PutBuildPolicy::PutBuildPolicy(const PutBuildPolicy &ref)
	{(void)ref;}

	PutBuildPolicy &PutBuildPolicy::operator=(const PutBuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IResponse		*PutBuildPolicy::buildResponse(IRequest *request)
	{
		(void) request;
		return _e_pager.getErrorPage(404);
	}
}