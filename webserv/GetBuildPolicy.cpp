#include <GetBuildPolicy.hpp>

namespace ft
{
	int GetBuildPolicy::_count = 0;

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
		std::cout << "Respone N: " << _count << "\n";
		_count++;


		IResponse *res = NULL;
		//std::cout<<request->to_string()<<std::endl;
		ServerInit *conf = getConfig();
		applyConfig(conf);
		LocationInit *location = findLocation(request->getHeader()->getPath(), conf);
		if (getFileExtension(request->getHeader()->getPath()) == "php") {
			location = extensionCheck(request, conf);
			res = redirectToCGI(request, location);
			if (res)
				return res;
		}
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
							std::pair<bool, std::string> author = ifAuthentication(request, location);
							if (ifAuthentication(request, location).first){
								return buildFromFile(request, correct_path);
							} else {
								res = _e_pager.getErrorPage(401);
								res->getHeader()->setHeader("WWW-Authenticate", "Basic realm=\""+author.second+"\"");
							}
						}
					}
				}
			}
		} else if (ifCorrectMethod(request, location)){
			std::string correct_path = ifRootArgument(request, location);
			std::pair<bool, std::string> author = ifAuthentication(request, location);
			if (author.first && author.second == ""){
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
				res = _e_pager.getErrorPage(401);
				res->getHeader()->setHeader("WWW-Authenticate", "Basic realm=\""+author.second+"\"");
				return res;
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

	int GetBuildPolicy::getCount() {
		return _count;
	}

	void GetBuildPolicy::reset() {
		_count = 0;
	}
}