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
		ApplyConfig(getConfig());
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

	void GetBuildPolicy::ApplyConfig(ServerInit *server)
	{
		if (server == NULL)
			throw ft::runtime_error("GetBuildPolicy::ApplyConfig - no incoming server config");
		_fmngr.setRoot(server->getRoot());
	}
}