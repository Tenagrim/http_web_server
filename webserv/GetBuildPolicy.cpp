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
		std::cout<<request->to_string()<<std::endl;
		ServerInit *conf = getConfig();
		applyConfig(conf);
		LocationInit *location = findLocation(request->getHeader()->getPath(), conf);
		if (!location) {
			std::string path = checkerPath(request, conf);
			if (!_fmngr.isFileExisting(path)) {
				return (_e_pager.getErrorPage(404));
			} else {
				if (_fmngr.isADirectory(path)) {
					return buildFromDir(request, path, getCorrectLocation(request->getHeader()->getPath(), conf));
				} else {
					location = getCorrectLocation(request->getHeader()->getPath(), conf);
					if (!location) {
						return buildFromFile(request, path);
					} else {
						if (ifCorrectMethod(request, location)){
							std::string correct_path = ifRootArgument(request, location);
							 return buildFromFile(request, correct_path);
						}
					}
				}
			}
		} else if (ifCorrectMethod(request, location)){
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
			res = ifErrorPage(request, location, to_string(405));
			if (!res)
				res = (_e_pager.getErrorPage(405));
			res->getHeader()->setHeader("allow", location->getArgs().find("limit_except")->second);
			return res;
		}
		return res;
	}

	IResponse *GetBuildPolicy::buildIfNoLocation(IRequest *request)
	{
		if (!_fmngr.isFileExisting(request->getHeader()->getPath())) {
			return _e_pager.getErrorPage(404);
		} else if (_fmngr.isADirectory(request->getHeader()->getPath())) {
			return buildFromDir(request, request->getHeader()->getPath(), NULL);
		} else {
			return buildFromFile(request, request->getHeader()->getPath());
		}
	}
}