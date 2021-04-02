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
		BasicResponse *response = new BasicResponse(checkCommingURI(request), NULL);
		return response;
		return _e_pager.getErrorPage(404);
	}

	Header *PutBuildPolicy::checkCommingURI(IRequest *request)
	{
		(void) request;
		Header *head = new Header(response);
		if (!_fmngr->isFileExisting(request->getURI())) {
			head->setHTTPV(request->getHTTPVersion());
			head->setResponseCode(201);
			head->setHeader("Content-Location", request->getURI());
			return head;
		} else {
			if (request->getBody()) {
				head->setHTTPV(request->getHTTPVersion());
				head->setResponseCode(200);
				return head;
			} else {
				head->setHTTPV(request->getHTTPVersion());
				head->setResponseCode(204);
				head->setHeader("Content-Location", request->getURI());
//			mutantExistingFile(request);
			}
		}
		return head;
	}
}