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
//	IResponse *res = NULL;
//	ServerInit *conf = getConfig();
//	applyConfig(conf);
//	LocationInit *location = NULL;
//	res = (_e_pager.getErrorPage(405));
//	res->deleteBody();

	IResponse *res = NULL;
	ServerInit *conf = getConfig();
	applyConfig(conf);
	LocationInit *location = getCorrectLocation(request->getHeader()->getURI(), conf);
	if (!location)
		location = getCorrectLocation("/", conf);
	if (ifCorrectMethod(request, location)){
		std::string correct_path = ifRootArgument(request, location);
		if (_fmngr.isADirectory(correct_path)) {
			res = buildFromDir(request, correct_path, location);
		}
		else if (_fmngr.isFileExisting(correct_path)) {
			 res = buildFromFile(request, correct_path);
		}
		else {
			return (_e_pager.getErrorPage(404));
		}
	} else {
		return (_e_pager.getErrorPage(405));
	}
	res->deleteBody();
	return  res;
}

ft::Header *ft::HeadBuildPolicy::createHeader(ft::IRequest *request)
{

}
