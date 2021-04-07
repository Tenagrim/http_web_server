#include <CgiModule.hpp>

namespace ft{
    CgiModule::CgiModule()
    {
    	char buff[512];

    	if (getcwd(buff, 512) == 0)
			throw ft::runtime_error("Too Long Path");
    	_home = std::string(buff);
    	_tmp_in = _home + "/" + TMP_IN;
    	_tmp_out = _home + "/" + TMP_OUT;
    }
    
    CgiModule::CgiModule(const CgiModule &ref){
        (void)ref;
    }
    
    CgiModule::~CgiModule()
    {}
    
    CgiModule &CgiModule::operator=(const CgiModule &ref){
        (void)ref;
        return (*this);
    }

	IResponse *CgiModule::getResponse(IRequest *req) {
    	int pid, status, ret;
    	Environment envs;
    	setEnvs(req, envs);
    	reset();

    	pid = fork();
    	if (pid == -1)
			throw ft::runtime_error("CGI MODULE: FORK FAILED");
    	else if (pid == 0)
		{

			sendRequest(req);

			char **c = envs.getEnv();
			while (*c)
			{
				std::cout << *c << "\n";
				c++;
			}


			//if (chdir(_root.c_str()) == -1)
			//	exit(500);

			_av = getArgv(_executable, _root + "/123.bla");

			std::cout << "AV 0:" << _av[0] << "\n";
			std::cout << "AV 1:" << _av[1] << "\n";

			if (_cgi_in == -1)
				_cgi_in = open(_tmp_in.c_str(), O_RDONLY);
			_cgi_out = open(_tmp_out.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (_cgi_in == -1 || _cgi_out == -1) {
				dprintf(2, "FILE CAN T BE OPENED\n"); /////////// ATTENTION
				exit(500);
			}
			char buff[300];

			getcwd(buff,300);
			std::cout << "[[[[[[ " << buff<< "\n";

			dup2(_cgi_in, 0);
			dup2(_cgi_out, 1);
			execve(_executable.c_str(), _av, envs.getEnv());
			dprintf(2, "EXECVE FAILED\n"); ////////// ATTENTION
			exit(500);
		}
    	else
		{
			waitpid(pid, &status,0);
			ret = WEXITSTATUS(status);
			if (ret == 500)
				return _e_pager.getErrorPage(500);
		}
		return nullptr; /////////////////////// ARR
	}

	void CgiModule::setEnvs(IRequest *req, Environment &env) {
    	methods_enum method;

    	env.setVar("REQUEST_METHOD", ft::getMethodStr(req->getHeader()->getMethod()));
    	env.setVar("SERVER_PROTOCOL", req->getHeader()->getHTTPVersion());
    //	if(req->getHeader()->isHeadAlreadyExist(h_content_length))
    //		env.setVar("CONTENT_LENGTH", req->getHeader()->getHeader(h_content_length));


    	env.setVar("PATH_INFO", req->getHeader()->getPath());

	//	env.setVar("REQUEST_TARGET",)
    //	env.setVar("PATH_TRANSLATED", "/123.bla");
    //	env.setVar("SCRIPT_FILENAME", "/123.bla");
    //	env.setVar("SCRIPT_NAME", "/123.bla");

//    	char **c = env.getEnv();
//    	while (*c)
//		{
//    		std::cout << *c << "\n";
//    		c++;
//		}

		switch (method) {
			case m_get:
				env.setVar("QUERY_STRING", req->getHeader()->getQuery());
				break;
			case m_post:
				break;
		//	default: throw ft::runtime_error("Method not Allowed");
		}
	}

	void CgiModule::setRoot(const std::string &root) {
		_root = root;
	}

	void CgiModule::setExecutable(const std::string &executable) {
		_executable = executable;
	}

	char **CgiModule::getArgv(const std::string &arg0, const std::string &arg1) {
		char **res = new char *[3];
		char *arg = new char [arg0.size() + 1];
		char *arg_1 = new char [arg1.size() + 1];
		if (!res || !arg || !arg_1)
			throw ft::runtime_error("ALLOCATION FAILED");
		ft::ft_memcpy(arg, arg0.c_str(), arg0.size());
		ft::ft_memcpy(arg_1, arg1.c_str(), arg1.size());
		arg[arg0.size()] = 0;
		arg_1[arg1.size()] = 0;
		res[0] = arg;
		res[1] = arg_1;
		res[2] = nullptr;
		return res;
	}

	void CgiModule::deleteArgv(char **args) {
		delete [] args[0];
		delete [] args;
	}

	void CgiModule::sendRequest(IRequest *req) {
    	//_cgi_in = open(TMP_IN, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		IBody	*body = req->getBody();
		if (!body)
		{
			_cgi_in = open(_tmp_in.c_str(), O_CREAT  | O_RDONLY | O_TRUNC, 0666);
			return;
		}
    	if (dynamic_cast<FileBody*>(body))
    		sendFileBody(dynamic_cast<FileBody*>(body));
    	else if (dynamic_cast<TextBody*>(body))
    		sendTextBody(dynamic_cast<TextBody*>(body));
	}

	void CgiModule::initFiles() {

	}

	void CgiModule::reset() {
    	_cgi_in = -1;
    	_cgi_out = -1;
	}

	void CgiModule::sendFileBody(FileBody *body) {
		_cgi_in = body->getFd();
	}

	void CgiModule::sendTextBody(TextBody *body) {
		int ret;
		std::string text = body->to_string();

    	_cgi_in = open(_tmp_in.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
		write(_cgi_in, text.c_str(), text.size());
		close(_cgi_in);
		_cgi_in = -1;
	}
} // ft