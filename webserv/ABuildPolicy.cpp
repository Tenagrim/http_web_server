#include <ABuildPolicy.hpp>
#include <vector>

namespace ft
{
	ABuildPolicy::ABuildPolicy(const ABuildPolicy &ref)
	{ (void)ref; /* Illegal */}

	ABuildPolicy::ABuildPolicy()
	{
		_t_machine = new FakeTimeMachine();
	}

	ABuildPolicy::~ABuildPolicy()
	{
		delete _t_machine;
	}
	ABuildPolicy &ABuildPolicy::operator=(const ABuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IHeader *ABuildPolicy::buildHeader(int ret_code, std::string descr, IBody *body)
	{
		//std::stringstream ss;
		IHeader *res = new Header(response);

		//ss << body->size();
		res->setCodeDescription(descr);
		res->setResponseCode(ret_code);
		res->setHTTPV("HTTP/1.1");
		res->setHeader(h_content_length, ft::to_string(body->size()));
		//res->setHeader(h_date, _t_machine->getTimestamp());
//		res->setHeader(h_connec, "keep-alive");
		res->setHeader(h_content_type, body->getContentType());
		res->setHeader(h_server, DEFAULT_SERVER_HEADER);

		//std::string type =
		return res;
	}
	int ABuildPolicy::findIndexFile(std::list<std::string> &priority)
	{
		(void)priority;
		int fd = 0;
		throw ft::runtime_error("Not implemented");
		return fd;
	}

	TextBody *ABuildPolicy::buildTextBody(std::string const &filename)
	{
		//int					fd;
		//unsigned int		size;
		//char				*buff;
		//int					ret;
		TextBody *res;
		std::stringstream ss;
		std::string str;
		std::ifstream fin(_fmngr.getFullPath(filename), std::ios::binary);
#ifdef DEBUG
		std::cout << "BODY FROM FILE: [" << filename << "]\n";
#endif

		if (!fin.good())
			throw ft::runtime_error("Cannot open file: " + filename);

		//fd = _fmngr->getFd(filename, 0);
		//size = _fmngr->getFileSize(filename);

		ss << fin.rdbuf();
		str = ss.str();

#ifdef DEBUG
		std::cout << "SIZE:" << str.size() << "\n";
#endif
		//buff = new char[size + 1];
		//ret = read(fd, buff, size);
		//buff[ret] = 0;

		res = new TextBody(str);
		//delete[] buff;
		fin.close();
		return (res);
	}

	FileBody *ABuildPolicy::buildFileBody(std::string const &filename)
	{
#ifdef DEBUG
		std::cout << "BUILDER: BUILD FILE BODY [" << filename << "]\n";
#endif
		FileBody *res = new FileBody( _fmngr.getFullPath(filename));
#ifdef DEBUG
		std::cout << "BUILDER: BUILDING COMPLETED [" << res->size() << "] [" << res->getFd() << "] [" << _fmngr.getFullPath(filename) << "]\n";
#endif
		return (res);
	}

	IBody *ABuildPolicy::bodyFromFile(std::string const &filename)
	{
		std::string type;
		IBody *res;

		try {
			type = _fmngr.getContentType(filename);
		} catch (FileManager::NoSuchType) {
			type = "";
		}
#ifdef DEBUG
		std::cout << "BUILDER: GOT FILE TYPE [" << type << "]\n";
#endif
		if (type.find("text") != std::string::npos)
			res = buildTextBody(filename);
		else
			res = buildFileBody(filename);
		res->setContentType(type);
		return (res);
	}

	IResponse *ABuildPolicy::buildFromFile(std::string const &filename)
	{
		IResponse *res;
		IBody *body;
		IHeader *header;

#ifdef DEBUG
		std::cout << "BUILDER: BUILD FROM FILE: [" << filename << "]\n";
#endif
//		TODO: Check If file get CGI extencion;
		body = bodyFromFile(filename);
		header = buildHeader(200, "OK", body);

		//res = new TextResponse(header->to_string() + body->to_string());
		res = new BasicResponse(header, body);
		//delete header;
		//delete body;
		return (res);
	}

	IResponse *ABuildPolicy::buildAutoindex(IRequest *request)
	{
		(void)request;
		throw ft::runtime_error("Not implemented");
		return (0);
	}

	IResponse *ABuildPolicy::buildFromDir(IRequest *request, std::string const &correct_path, LocationInit *location)
	{
//		(void)request; // FIXME
//		if (_fmngr.isFileExisting(correct_path + "index.html"))
//		{
//#ifdef DEBUG
//			std::cout << "FILE EXISTS\n";
//#endif
//			return buildFromFile(correct_path + "index.html");
//		}
//		return _e_pager.getErrorPage(404);
		IBody *body;
		try {
			body = _index_module.getHtmlPage(location, _fmngr.getRoot(), correct_path);
		} catch (IndexModule::ErrorException &e)
		{
			if (e.whatCode() == 404)
				return  _e_pager.getErrorPage(404);
			else if (e.whatCode() == 403)
				return  _e_pager.getErrorPage(403);
			else
				throw ft::runtime_error("SOMETHING WENT WRONG");
		}
		if (!body)
			return _e_pager.getErrorPage(404);
		IHeader *header = buildHeader(200, "OK", body);
		BasicResponse *res = new BasicResponse(header, body);
		return res;
	}

	IResponse	*ABuildPolicy::buildErrorPage(int code)
	{
		return (_e_pager.getErrorPage(code));
	}

	ServerInit *ABuildPolicy::getConfig() const
	{
		return config;
	}

	void ABuildPolicy::setConfig(ServerInit *config)
	{
		ABuildPolicy::config = config;
	}

	LocationInit *ABuildPolicy::getCorrectLocation(IRequest *request, ServerInit *server)
	{
		LocationInit *location = NULL;
		std::list<LocationInit *> list = server->getLocationInits();
		std::list<LocationInit *>::iterator it = list.begin();
		for (unsigned int i = 0; i < server->getLocationCount(); i++){
			if ((*it)->getPath() == request->getHeader()->getURI()) {
				location = it.operator*();
				break;
			}
		}
		return location;
	}

	LocationInit *ABuildPolicy::getCorrectLocation(std::string URI, ServerInit *server)
	{
		LocationInit *location;
		if (URI.empty())
			throw ft::runtime_error("*ABuildPolicy::getCorrectLocation - NOT FOUND");
//		if (URI == "/")
//			location = findLocation(URI, server);
		location = findLocation(URI, server);
		if (!location){
			std::string new_uri = URI.substr(0, URI.rfind('/'));
			if (new_uri.empty())
				new_uri = "/";
			location = getCorrectLocation(new_uri, server);
		}
//		if ( _fmngr.isADirectory(URI)) {
//			location = findLocation(URI , server);
//		} else {
//			location = findLocation(URI , server);
//			if (!location) {
//				std::string dir_name = URI.substr(0,URI.rfind("/"));
//				location = findLocation(dir_name , server);
//			}
//		}
		return location;
	}

	void ABuildPolicy::applyConfig(ServerInit *server)
	{
		if (server == NULL)
			throw ft::runtime_error("GetBuildPolicy::ApplyConfig - no incoming server config");
		_fmngr.setRoot(server->getRoot());
	}

	LocationInit *ABuildPolicy::getLocationFile(IRequest *request, ServerInit *server)
	{
		LocationInit *location = NULL;
		location = getCorrectLocation(request, server);
		if (location)
			return location;
		else {
			std::string new_location = request->getHeader()->getURI();
			std::string::reverse_iterator rit;
			rit = std::find(new_location.rbegin(), new_location.rend(), '/');
			std::string::iterator it = rit.base();
			if (rit == new_location.rend())
				return location;
			else {
				new_location.erase(it, new_location.end());
				location = getCorrectLocation(new_location, server);
				return location;
			}
		}
	}

	IResponse *ABuildPolicy::buildFromFile(IRequest *request, std::string const &correct_path)
	{
		IResponse *res;
		IBody *body;
		IHeader *header;

#ifdef DEBUG
		std::cout << "BUILDER: BUILD FROM FILE: [" << filename << "]\n";
#endif

		body = bodyFromFile(correct_path);
		header = buildHeader(200, "OK", body);

		//res = new TextResponse(header->to_string() + body->to_string());
		res = new TextResponse(header, body);  // WHAT ??!!!??
		res = new BasicResponse(header, body);
		//delete header;
		//delete body;
		return (res);
	}

	bool ABuildPolicy::ifCorrectMethod(IRequest *request, LocationInit *location)
	{
		bool res = false;
		if (!location)
			throw ft::runtime_error("No coorect Location");
		std::map<std::string, std::string> arguments = location->getArgs();
		std::string methods = arguments["limit_except"];
		if (methods.empty()){
			return true;
		}
		std::vector<std::string> vec = splitString(methods, " ");
		for (size_t i = 0; i != vec.size(); ++i) {
			if (ft::getMethodStr(request->getHeader()->getMethod()) == vec[i])
				res = true;
		}
		return  res;
	}

	std::string ABuildPolicy::ifRootArgument(IRequest *request, LocationInit *location)
	{
		std::string res;
		std::map<std::string, std::string> args = location->getArgs();
		std::map<std::string, std::string>::iterator it = args.find("root");
		if (it != args.end()) {
			res = request->getHeader()->getURI();
			int pos = res.rfind(location->getPath());
			res.replace(pos, location->getPath().size(), it->second);
		}
		else
			res = request->getHeader()->getURI();
		return res;
	}

	LocationInit *ABuildPolicy::findLocation(const std::string &URI, ServerInit *server)
	{
		LocationInit *location = NULL;
		std::list<LocationInit *> list = server->getLocationInits();
		std::list<LocationInit *>::reverse_iterator rit = list.rbegin();
		for (; rit != list.rend() ; ++rit){
			LocationInit *tmp = *rit;
			if (tmp->getPath() == URI || (tmp->getPath()) == URI+"/") {
				location = *rit;
				break;
			}
		}
		return location;
	}

	std::string ABuildPolicy::checkerPath(IRequest *request,ServerInit *conf)
	{
		std::string path;
		std::string URI = request->getHeader()->getURI();
		if (!URI.empty()) {
			std::vector<std::string> vec = splitString(URI, "/");
			std::cout<<vec.size()<<std::endl;
			vec.erase(vec.begin());
			std::list<LocationInit *> list = conf->getLocationInits();
			for (size_t i = 0; i != vec.size(); i++){
				std::string part = findPart(list, vec[i]);
				if (!part.empty())
					path += part;
			}
		}
		return path;
	}

	std::string ABuildPolicy::findPart(std::list<LocationInit *> list, const std::string &string)
	{
		std::string res = string;
		if(string.empty())
			return res;
		std::list<LocationInit *>::iterator it = list.begin();
		for (; it != list.end(); ++it) {
			if ((*it)->getPath() == ("/" + string)) {
				res = (*it)->getArgs().find("root")->second;
				return res;
			}
		}
		res = "/" + res;
		return res;
	}
}
// namespace ft