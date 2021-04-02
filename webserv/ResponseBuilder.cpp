#include <ResponseBuilder.hpp>
namespace ft
{
	//ITimeMachine const &ResponseBuilder::_t_machine = FakeTimeMachine();

	#pragma region Copilen
	ResponseBuilder::ResponseBuilder()
	{/*  Illegal */}

	ResponseBuilder::ResponseBuilder()
	{
		_policies[m_get] = new GetBuildPolicy(mngr, );
		_policies[m_post] = new PostBuildPolicy(mngr, _t_machine);
		_policies[m_put] = new PutBuildPolicy(mngr, _t_machine);
	}

	ResponseBuilder::~ResponseBuilder()
	{
		for (policy_map::iterator it = _policies.begin(); it!= _policies.end(); it++)
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
		ft::methods_enum method = request->getHeader()->getMethod();

		if (_policies.empty())
			throw ft::runtime_error("BUILDER HAS NO BUILD POLICIES");

		if (_policies.count(method))
		{
			return (_policies[method]->buildResponse(request));
		}
		else
			return ((*(_policies.begin())).second->buildErrorPage(501));
	}
}