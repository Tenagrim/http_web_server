#include <GetBuildPolicy.hpp>

namespace ft
{
	GetBuildPolicy::~GetBuildPolicy()
	{}

	GetBuildPolicy::GetBuildPolicy()
	{
	}

	GetBuildPolicy::GetBuildPolicy(const GetBuildPolicy &ref)
	{(void)ref; /* Illegal */}

	GetBuildPolicy &GetBuildPolicy::operator=(const GetBuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IResponse *GetBuildPolicy::buildResponse(IRequest *request)
	{
		applyConfig(getConfig());
		collectResponse(request, getConfig());
		IResponse *res = 0;
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

	void GetBuildPolicy::collectResponse(IRequest *request, ServerInit *server)
	{
		LocationInit* location = getCorrectLocation(request, server);
		if (!location) {

		}
	}

	void GetBuildPolicy::applyConfig(ServerInit *server)
	{
		if (server == NULL)
			throw ft::runtime_error("GetBuildPolicy::ApplyConfig - no incoming server config");
		_fmngr.setRoot(server->getRoot());
	}

	LocationInit *GetBuildPolicy::getCorrectLocation(IRequest *request, ServerInit *server)
	{
		LocationInit *location = NULL;
		std::list<LocationInit *> list = server->getLocationInits();
		std::list<LocationInit *>::iterator it = list.begin();
		for (int i = 0; i < server->getLocationCount(); i++){
			if ((*it)->getPath() == request->getHeader()->getURI()) {
				location = it.operator*();
				break;
			}
		}
		return location;
	}
}