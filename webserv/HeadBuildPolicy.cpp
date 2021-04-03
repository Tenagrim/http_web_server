#include <HeadBuildPolicy.hpp>

ft::HeadBuildPolicy::HeadBuildPolicy(){
}

ft::HeadBuildPolicy::~HeadBuildPolicy() {
}

ft::HeadBuildPolicy &ft::HeadBuildPolicy::operator=(const ft::HeadBuildPolicy &ref)
{
	(void)ref;
	return (*this);
}

ft::IResponse *ft::HeadBuildPolicy::buildResponse(ft::IRequest *request)
{
	(void) request;
	Header *head = createHeader(request);
	BasicResponse *response = new BasicResponse(head, NULL);
	if (response == nullptr)
		return (_e_pager.getErrorPage(404));
	return response;
}

ft::Header *ft::HeadBuildPolicy::createHeader(ft::IRequest *pRequest)
{
	IHeader *head = new Header(response);

}
