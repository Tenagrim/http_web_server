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
		IResponse *res = NULL;
		ServerInit *conf = getConfig();
		applyConfig(conf);
		LocationInit *location = NULL;
		if (_fmngr.isADirectory(request->getHeader()->getURI())) {
			location = getCorrectLocation(request, conf);
			if (!location)
				location = getCorrectLocation("/", conf);
			return (buildFromDir(request, location));
		} else if (_fmngr.isFileExisting(request->getHeader()->getURI())) {
			location = getLocationFile(request, conf);
			if (!location)
				location = getCorrectLocation("/", conf);
			return (buildFromFile(request, location));
		} else
			return (_e_pager.getErrorPage(404));




//#ifdef DEBUG
//		std::cout << "URI ::::::::::: [" << request->getHeader()->getURI() << "]\n";
//#endif
//		if (_fmngr.isADirectory(request->getHeader()->getURI()))
//			return (buildFromDir(request));
//
//		if (_fmngr.isFileExisting(request->getHeader()->getURI()))
//		{
//#ifdef DEBUG
//			std::cout << "FILE EXISTS\n";
//#endif
//			res = buildFromFile(request->getHeader()->getURI());
//
//			return res;
//		}
//#ifdef DEBUG
//		std::cout << "FILE NOT EXISTS\n";
//#endif
//		return (_e_pager.getErrorPage(404));
	}
}