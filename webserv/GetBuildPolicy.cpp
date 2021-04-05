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
		if (_fmngr.isADirectory())
		IResponse *res = NULL;
		ServerInit *conf = getConfig();
		applyConfig(conf);
		LocationInit *location = getLocation(request, conf);
		if (!location)
			return (buildResponse(request, conf));
		else
			return (buildResponse(request, location));

#ifdef DEBUG
		std::cout << "URI ::::::::::: [" << request->getHeader()->getURI() << "]\n";
#endif
		if (_fmngr.isADirectory(request->getHeader()->getURI()))
			return (buildFromDir(request));

		if (_fmngr.isFileExisting(request->getHeader()->getURI()))
		{
#ifdef DEBUG
			std::cout << "FILE EXISTS\n";
#endif
			res = buildFromFile(request->getHeader()->getURI());

			return res;
		}
#ifdef DEBUG
		std::cout << "FILE NOT EXISTS\n";
#endif
		return (_e_pager.getErrorPage(404));
	}
}