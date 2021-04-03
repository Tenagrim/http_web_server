#include <ResponseBuilder.hpp>
namespace ft
{
	//ITimeMachine const &ResponseBuilder::_t_machine = FakeTimeMachine();

	#pragma region Copilen

	ResponseBuilder::ResponseBuilder()
	{
		_policies[m_get] = new GetBuildPolicy();
		_policies[m_post] = new PostBuildPolicy();
		_policies[m_put] = new PutBuildPolicy();
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
		IResponse	*resp = nullptr;

		if (_policies.empty())
			throw ft::runtime_error("BUILDER HAS NO BUILD POLICIES");

#ifdef DEBUG_REQ_PRINT
		if (request->getHeader()->isValid())
			std::cout<< "==================\n" << request->to_string() << "=================================\n";
#endif
		if(!request->getHeader()->isValid())
			resp = ((*(_policies.begin())).second->buildErrorPage(400));
		else if (_policies.count(method))
			resp =_policies[method]->buildResponse(request);
		else
			resp =(*(_policies.begin())).second->buildErrorPage(501);

#ifdef DEBUG_RESP_PRINT
		std::cout<< "==================\n" << resp->to_string() << "=================================\n";
#endif
		return resp;

	}
}