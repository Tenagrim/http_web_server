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
		Header *head = checkCommingURI(request);
		BasicResponse *response = new BasicResponse(head, NULL);
		return response;
		return _e_pager.getErrorPage(404);
	}

	Header *PutBuildPolicy::checkCommingURI(IRequest *request)
	{
		Header *head = new Header(response);
		if (!_fmngr->isFileExisting(request->getURI())) {
			head->setResponseCode(201);
			head->setCodeDescription(ft::getCodeDescr(201));
			head->setHeader("Content-Location", request->getURI());
//			creatFile(request->getBody());
			return head;
		} else {
			if (request->getBody()) {
				head->setResponseCode(200);
				head->setCodeDescription(ft::getCodeDescr(200));
//				mutantExistingFile(request->getBody());
				return head;
			} else {
				head->setResponseCode(204);
				head->setCodeDescription(ft::getCodeDescr(204));
				head->setHeader("Content-Location", request->getURI());
				return head;
			}
		}
		return head;
	}
}