#include <GetBuildPolicy.hpp>

namespace ft
{
	GetBuildPolicy::GetBuildPolicy()
	{/* Illegal */}

	GetBuildPolicy::~GetBuildPolicy()
	{}

	GetBuildPolicy::GetBuildPolicy(IFileManager *mngr, ITimeMachine *machine) : ABuildPolicy(mngr, machine)
	{}

	GetBuildPolicy::GetBuildPolicy(const GetBuildPolicy &ref)
	{(void)ref; /* Illegal */}

	GetBuildPolicy &GetBuildPolicy::operator=(const GetBuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IResponse *GetBuildPolicy::buildResponse(IRequest *request)
	{
		_fmngr->setRoot("resources/sites/particles"); // HARDCODED SERVER ROOT
		//_fmngr->setRoot("resources/sites/trump");   // HARDCODED SERVER ROOT
		IResponse *res = 0;
		#ifdef DEBUG
			std::cout << "URI ::::::::::: [" << request->getURI() << "]\n";
		#endif

		if (_fmngr->isADirectory(request->getHeader()->getURI()))
			return (buildFromDir(request));

		if (_fmngr->isFileExisting(request->getHeader()->getURI()))
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