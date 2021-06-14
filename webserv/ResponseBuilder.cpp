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
		_policies[m_head] = new HeadBuildPolicy();
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

		if (!request->getHeader()->isValid())
			return (*(_policies.begin())).second->buildErrorPage(400);
		if (_policies.empty())
			throw ft::runtime_error("BUILDER HAS NO BUILD POLICIES");

		if (_policies.count(method))
		{
//			TODO: Make config serch
			ServerInit *serverConfig = findCorrectConfig(request);
			ABuildPolicy *policy;
			policy = _policies[method];
			policy->setConfig(serverConfig);
			return (_policies[method]->buildResponse(request));
		}
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
		++it;
		ServerInit *server = _serv_list->front();
		for (; it != _serv_list->end(); it++){
			if ((checkServer(request, it))) {
				server = it.operator*();
				break;
			}
		}
		return server;
	}

	bool ResponseBuilder::checkServer(IRequest *pRequest, std::list<ServerInit *>::iterator config)
	{
		bool state = false;
		ServerInit *server = NULL;
		server = config.operator*();
		state = checkServerName(pRequest, server);
		state *= checkPort(pRequest, server);
		return state;
	}

	bool ResponseBuilder::checkPort(IRequest *pRequest, ServerInit *pServer)
	{
		bool state = true;
		std::list<int> list = pServer->getListenPorts();
		std::list<int>::iterator it;
		int port = findPort(pRequest);
		it = std::find(list.begin(), list.end(), port);
		if (it == list.end())
			state = false;
		return state;
	}

	bool ResponseBuilder::checkServerName(IRequest *pRequest, ServerInit *pServer)
	{
		bool state = true;
		std::list<std::string> list = pServer->getServerNames();
		std::list<std::string>::iterator it;
		it = std::find(list.begin(), list.end(), pRequest->getHeader()->getHeader("host"));
		if (it == list.end())
			state = false;
		return state;
	}

	int ResponseBuilder::findPort(IRequest *pRequest)
	{
		int res = 0;
		std::string tmp = pRequest->getHeader()->getHeader("host");
		size_t pos = tmp.find(':');
		if (pos == std::string::npos)
			res = 80;
		else {
			res = strtol(tmp.c_str()+pos+1, NULL, 10);
		}
		return res;
	}
}