#include <GetBuildPolicy.hpp>

namespace ft
{
	GetBuildPolicy::~GetBuildPolicy()
	{}

	GetBuildPolicy::GetBuildPolicy()
	{
	}

	GetBuildPolicy::GetBuildPolicy(const GetBuildPolicy &ref)
	{ (void) ref; /* Illegal */}

	GetBuildPolicy &GetBuildPolicy::operator=(const GetBuildPolicy &ref)
	{
		(void) ref;
		return (*this);
	}

	IResponse *GetBuildPolicy::buildResponse(IRequest *request)
	{
		#ifdef DEBUG
				std::cout << "URI ::::::::::: [" << request->getHeader()->getURI() << "]\n";
		#endif
		IResponse *res = NULL;
		ServerInit *conf = getConfig();
		applyConfig(conf);
		LocationInit *location = getCorrectLocation(request->getHeader()->getURI(), conf);
		if (!location)
			location = getCorrectLocation("/", conf);
		if (ifCorrectMethod(request, location)){
			std::string correct_path = ifRootArgument(request, location);
			if (_fmngr.isADirectory(correct_path)) {
				return buildFromDir(request, correct_path, location);
			}
			else if (_fmngr.isFileExisting(correct_path)) {
				return buildFromFile(request, correct_path);
			}
			else {
				return (_e_pager.getErrorPage(404));
			}
		} else {
			res = (_e_pager.getErrorPage(405));
			res->getHeader()->setHeader(h_allow, location->getArgs().find("limit_except")->second);
			return res;
		}
	}
}