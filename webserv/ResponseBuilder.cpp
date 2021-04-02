#include <ResponseBuilder.hpp>
namespace ft
{
	//ITimeMachine const &ResponseBuilder::_t_machine = FakeTimeMachine();

	#pragma region Copilen
	ResponseBuilder::ResponseBuilder()
	{/*  Illegal */}

	ResponseBuilder::ResponseBuilder(IFileManager *mngr) : _t_machine(new FakeTimeMachine())
	{
		_policies["GET"] = new GetBuildPolicy(mngr, _t_machine);
		_policies["POST"] = new PostBuildPolicy(mngr, _t_machine);
		_policies["PUT"] = new PutBuildPolicy(mngr, _t_machine);
	}

	ResponseBuilder::~ResponseBuilder()
	{
		for(policy_map::iterator it = _policies.begin(); it!= _policies.end(); it++)
			delete (*it).second;
		//delete _t_machine;
	}

	ResponseBuilder::ResponseBuilder(const ResponseBuilder &ref)
	{
		(void)ref;
		throw ft::runtime_error("Not implemented");
	}

	ResponseBuilder &ResponseBuilder::operator=(const ResponseBuilder &ref)
	{
		(void)ref;
		throw ft::runtime_error("Not implemented");
		return (*this);
	}
	#pragma endregion

	IResponse			*ResponseBuilder::buildResponse(IRequest	*request)
	{
		std::string const & method = request->getMethod();

		if (!_policies.size())
			throw ft::runtime_error("BUILDER HAS NO BUILD POLICIES");

		if (_policies.count(method))
		{
			return (_policies[method]->buildResponse(request));
		}
		else
			return ((*(_policies.begin())).second->buildErrorPage(501));
	}
}