#pragma once
#include <ABuildPolicy.hpp>
namespace ft
{

	class PutBuildPolicy : public ABuildPolicy
	{
	private:
		PutBuildPolicy();
		PutBuildPolicy(const PutBuildPolicy &ref);

	public:
		PutBuildPolicy(IFileManager *mngr, ITimeMachine *machine);
		virtual ~PutBuildPolicy();
		PutBuildPolicy &operator=(const PutBuildPolicy &ref);
		IResponse		*buildResponse(IRequest *request);

		Header *checkCommingURI(IRequest *request);

		void creatFile(IRequest *pRequest);
	};
} // namespace ft