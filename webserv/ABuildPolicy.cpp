#include <ABuildPolicy.hpp>
#include <vector>
#include <webserv.hpp>

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
		char buf[TIME_BUFF_RESPONSE];

		//ss << body->size();
		res->setCodeDescription(descr);
		res->setResponseCode(ret_code);
		res->setHTTPV("HTTP/1.1");
		res->setHeader("content-length", ft::to_string(body->size()));
		currentTimeFormatted("%a, %d %b %Y %T GMT", buf, TIME_BUFF_RESPONSE);
		res->setHeader("date", buf);
//		res->setHeader(h_connec, "keep-alive");
		res->setHeader("content-type", body->getContentType());
		res->setHeader("server", DEFAULT_SERVER_HEADER);

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
		FileBody *res = new FileBody(_fmngr.getFullPath(filename), 0);
#ifdef DEBUG
		std::cout << "BUILDER: BUILDING COMPLETED [" << res->size() << "] [" << res->getFd() << "] [" << _fmngr.getFullPath(filename) << "]\n";
#endif
		return (res);
	}

	IBody *ABuildPolicy::bodyFromFile(std::string const &filename)
	{
		std::string type;
		IBody *res;

#ifdef DEBUG
		std::cout << "BUILDER: GOT FILE TYPE [" << type << "]\n";
#endif
		if (type.find("text") != std::string::npos)
			res = buildTextBody(filename);
		else
			res = buildFileBody(filename);
			type = _fmngr.getContentType(filename);
			if (type != "")
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
		(void)request;
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
				throw ft::runtime_error("SOMETHING WENT WRONG - *ABuildPolicy::buildFromDir");
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
		(void)request;
		IResponse *res;
		IBody *body;
		IHeader *header;

#ifdef DEBUG
		std::cout << "BUILDER: BUILD FROM FILE: [" << filename << "]\n";
#endif
		body = bodyFromFile(correct_path);
		header = buildHeader(200, "OK", body);

		//res = new TextResponse(header->to_string() + body->to_string());
		//res = new TextResponse(header, body);  // WHAT ??!!!??
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

	LocationInit *ABuildPolicy::extensionCheck(IRequest *request, ServerInit *conf)
	{
		LocationInit *location = NULL;
		std::string correct_path = checkerPath(request, conf);
//		if(_fmngr.isFileExisting(correct_path)) {
		std::string queri = ft::getFileQueri(correct_path);
		std::string ext;
		if (!queri.empty())
			ext = '.' + ft::getFileExtension(queri);
		else
			ext = '.' + ft::getFileExtension(correct_path);
		if (ext == ".bla" || ext == ".php")
			location = findLocation(ext, conf);
//			if (!location)
//				location = getCorrectLocation(correct_path, conf);
//			return location;
//		}
		return location;
	}

	std::string ABuildPolicy::ifRootArgument(IRequest *request, LocationInit *location)
	{
		std::string res;
		std::map<std::string, std::string> args = location->getArgs();
		std::map<std::string, std::string>::iterator it = args.find("root");
		if (it != args.end()) {
			res = request->getHeader()->getPath();
			int pos = res.rfind(location->getPath());
			res.replace(pos, location->getPath().size(), it->second);
		}
		else
			res = request->getHeader()->getPath();
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
		std::string URI = request->getHeader()->getPath();
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
		if (path.empty())
			path = "/";
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
				if ((*it)->getArgs().find("root") != (*it)->getArgs().end()) {
					res = (*it)->getArgs().find("root")->second;
					return res;
				}
			}
		}
		res = "/" + res;
		return res;
	}

	bool ABuildPolicy::ifCorrectBodySize(IRequest *request, LocationInit *location)
	{
		bool state = true;
		if (!location)
			throw ft::runtime_error("No coorect Location");
		std::map<std::string, std::string> arguments = location->getArgs();
		std::string methods = arguments["client_max_body_size"];
		if(!methods.empty()) {
			unsigned int size = atoi(methods.c_str());
			if (size != 0) {
				if (request->getBody()->size() > size)
					state = false;
			} else {
				throw ft::runtime_error("client_max_body_size argument is not a a number");
			}
		}
		return state;
	}

	IResponse *ABuildPolicy::ifErrorPage(IRequest *request, LocationInit *location, std::basic_string<char,
	        std::char_traits<char>, std::allocator<char> > code)
	{
		(void)request;
		IResponse *response = NULL;
		if (!location)
			throw ft::runtime_error("No coorect Location");
		std::map<std::string, std::string> arguments = location->getArgs();
		std::string methods = arguments["error_page"];
		if(!methods.empty()) {
			std::vector<std::string> vec = ft::splitString(methods, " ");
			if(checkCodePage(vec[0], code)) {
				IBody *body = bodyFromFile(vec[1]);
				IHeader *head = _e_pager.getErrorHead(std::stoi(code));
				head->setHeader("content-length", ft::to_string(body->size()));
				response = new BasicResponse(head, body);
			}
		}
		return response;
	}

	bool ABuildPolicy::checkCodePage(std::string &string, std::string &code)
	{
		bool res = false;
		std::vector<std::string> vec = ft::splitString(string, ",");
		for(size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] == code) {
				res = true;
				break;
			}
		}
		return res;
	}

	IResponse * ABuildPolicy::redirectToCGI(IRequest *request, LocationInit *location)
	{
		IResponse *response = NULL;
		if (!location)
			throw ft::runtime_error("No coorect Location");
		std::map<std::string, std::string> arguments = location->getArgs();
		std::string methods = arguments["fastcgi_pass"];
		std::string script = checkerPath(request, getConfig());
		if(!methods.empty()) {
			_cgi_module.setRoot(_fmngr.getRoot());
			_cgi_module.setExecutable(methods);
			response = _cgi_module.getResponse(request, script);
		}
		return response;
	}

	std::pair<bool, std::string> ABuildPolicy::ifAuthentication(IRequest *request, LocationInit *location)
	{
		std::pair<bool, std::string> res;
		res.first = false;
		res.second = "";
		if (!location)
			throw ft::runtime_error("No coorect Location");
		std::map<std::string, std::string> arguments = location->getArgs();
		std::string methods = arguments["auth_basic"];
		if (methods.empty()) {
			res.first = true;
			return res;
		}
		if (request->getHeader()->isFieldInHeader("authorization")) {
			std::string auth_req = request->getHeader()->getHeader("authorization");
			res.first = _auth.checkAuth(auth_req);
			if (res.first) {
				res.second.clear();
				return res;
			}
		}
		std::map<std::string, std::string>::iterator it = arguments.find("auth_basic");
		std::string tmp = it->second;
		res.second = _auth.getRealmKey(ft::base64_encode(reinterpret_cast<const unsigned char *>(tmp.c_str()), tmp.length
		()));
		res.first = false;
		return res;
	}
}
// namespace ft