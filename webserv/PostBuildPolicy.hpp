#pragma once
#include <ABuildPolicy.hpp>
namespace ft
{

	class PostBuildPolicy : public ABuildPolicy
	{
	private:
		PostBuildPolicy();
		PostBuildPolicy(const PostBuildPolicy &ref);

	public:
		PostBuildPolicy(IFileManager *mngr, ITimeMachine *machine);
		virtual ~PostBuildPolicy();
		PostBuildPolicy &operator=(const PostBuildPolicy &ref);
		IResponse		*buildResponse(IRequest *request);
	};


} // namespace ft