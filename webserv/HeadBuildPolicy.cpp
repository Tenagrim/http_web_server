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
//	Header *head = createHeader(request);
//	BasicResponse *response = new BasicResponse(head, NULL);
//	if (response == nullptr)
//		return (_e_pager.getErrorPage(404));
//	return response;
	IResponse *res = NULL;
	ServerInit *conf = getConfig();
	applyConfig(conf);
	LocationInit *location = NULL;
	res = (_e_pager.getErrorPage(405));
	res->deleteBody();
	return  res;
	if (_fmngr.isADirectory(request->getHeader()->getURI())) {
		location = getCorrectLocation(request, conf);
		if (!location)
			location = getCorrectLocation("/", conf);
		res = (buildFromDir(request, location));
		res->deleteBody();
		return res;
	} else if (_fmngr.isFileExisting(request->getHeader()->getURI())) {
		location = getLocationFile(request, conf);
		if (!location)
			location = getCorrectLocation("/", conf);
		res = (buildFromFile(request, location));
		res->deleteBody();
		return res;
	} else {
		res = (_e_pager.getErrorPage(404));
		res->deleteBody();
		return  res;
	}
}

ft::Header *ft::HeadBuildPolicy::createHeader(ft::IRequest *request)
{

}
