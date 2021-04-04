#include <PostBuildPolicy.hpp>

namespace ft
{
	PostBuildPolicy::PostBuildPolicy()
	{
	}
	
	PostBuildPolicy::~PostBuildPolicy()
	{
	}

	PostBuildPolicy::PostBuildPolicy(const PostBuildPolicy &ref)
	{(void)ref;}

	PostBuildPolicy &PostBuildPolicy::operator=(const PostBuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IResponse		*PostBuildPolicy::buildResponse(IRequest *request)
	{
		(void) request;
		IHeader *head = AcceptingData(request);
		IResponse *response = new BasicResponse(head, NULL);
		return response;
	}

	IHeader *PostBuildPolicy::AcceptingData(IRequest *pRequest)
	{
		std::cout<<pRequest->getText()<<std::endl;
		IHeader *head = new Header(response);
		head->setHTTPV(pRequest->getHTTPVersion());
		head->setResponseCode(405);
		head->setCodeDescription(ft::getCodeDescr(405));
		return head;
	}
}