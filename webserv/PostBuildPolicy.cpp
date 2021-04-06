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
		ServerInit *conf = getConfig();
		applyConfig(conf);
		LocationInit *location = getCorrectLocation(request, conf);
		if (ifCorrectMethod(request, location))
		{
			IHeader *head = AcceptingData(request);
			IResponse *response = new BasicResponse(head, NULL);
			return response;
		} else {
			IResponse *response = _e_pager.getErrorPage(405);
			response->getHeader()->setHeader(h_allow, location->getLocationsArguments().find("limit_except")->second);
			return response;
		}
	}

	IHeader *PostBuildPolicy::AcceptingData(IRequest *pRequest)
	{
		std::cout<<pRequest->getHeader()->to_string()<<std::endl;
		IHeader *head = new Header(response);
		head->setHTTPV(pRequest->getHeader()->getHTTPVersion());
		head->setResponseCode(405);
		head->setCodeDescription(ft::getCodeDescr(405));
		head->setHeader(h_allow, "GET, HEAD");
		head->setHeader(h_connection, "close");

		return head;
	}
}