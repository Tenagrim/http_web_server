#include <ResponseBuilder.hpp>
namespace ft
{
	//ITimeMachine const &ResponseBuilder::_t_machine = FakeTimeMachine();

	#pragma region Copilen

	ResponseBuilder::ResponseBuilder() : _t_machine(new FakeTimeMachine())
	{
		_policies["GET"] = new GetBuildPolicy();
		_policies["POST"] = new PostBuildPolicy();
		_policies["PUT"] = new PutBuildPolicy();
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
//			TODO: Make config serch
//			List configs and find coorect config, if nothing find, return  default config
			ServerInit *serverConfig = findCorrectConfig(request);
//			Server INit = Get config (request->getHost);
//
			ABuildPolicy *policy;
//			return (_policies[method]->buildResponse(request));
			policy = _policies[method];
//			Set police -> set Config;

			return policy->buildResponse(request);
		}
		else
			return ((*(_policies.begin())).second->buildErrorPage(501));
	}

	void ResponseBuilder::getConfigLists(std::list<ServerInit *> *_list)
	{
		if (_list != nullptr)
			_serv_list = _list;
		else
			throw ft::runtime_error("No Lists");
	}

	ServerInit *ResponseBuilder::findCorrectConfig(IRequest *request)
	{
		std::list<ServerInit *>::iterator it = _serv_list->begin();
		ServerInit *server = NULL;
		for (; it != _serv_list->end(); ++it){
			if ((server = checkServer(request, it)))
				break;
		}
		return server;
	}

	ServerInit *ResponseBuilder::checkServer(IRequest *pRequest, std::list<ServerInit *>::iterator config)
	{
		ServerInit *server;
		server = config.operator*();
		std::cout<<server->getRoot()<<std::endl;
		std::list<int> ports = (*config)->getListenPorts();
		return NULL;
	}
}