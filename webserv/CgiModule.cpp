#include <CgiModule.hpp>

namespace ft{
	int CgiModule::_max_id = 0;

	CgiModule::CgiModule() : _av(NULL), _cgi_in(-1), _cgi_out(-1)
	{
		char buff[512];
		if (getcwd(buff, 512) == 0)
			throw ft::runtime_error("Too Long Path");
		_home = std::string(buff);
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
		_tmp_in = _home + "/" + TMP_IN  + ft::to_string(_max_id);
		_tmp_out = _home + "/" + TMP_OUT + ft::to_string(_max_id);
		_max_id++;
		setEnvs(req, envs);
		reset_fd();

		pid = fork();
		if (pid == -1)
			throw ft::runtime_error("CGI MODULE: FORK FAILED");
		else if (pid == 0)
		{
			threadPart(req, envs);
		}
		else
		{
			waitpid(pid, &status,0);
			ret = WEXITSTATUS(status);
			if (ret == 500)
				return _e_pager.getErrorPage(500);
		}
		return getResult();
	}

	void CgiModule::setEnvs(IRequest *req, Environment &env) {
		methods_enum method = req->getHeader()->getMethod();

		env.setVar("REQUEST_METHOD", ft::getMethodStr(req->getHeader()->getMethod()));
		env.setVar("SERVER_PROTOCOL", req->getHeader()->getHTTPVersion());
	//	if(req->getHeader()->isHeadAlreadyExist("content-length"))
	//		env.setVar("CONTENT_LENGTH", req->getHeader()->getHeader("content-length"));

		env.setVar("PATH_INFO", req->getHeader()->getPath());

		req->getHeader()->setEnvs(env);
/*
		if (req->getHeader()->isFieldInHeader("secret"))
			env.setVar("HTTP_X_SECRET_HEADER_FOR_TEST", "1");
*/

	//	env.setVar("REQUEST_TARGET",)
	//	env.setVar("PATH_TRANSLATED", "/123.bla");
	//	env.setVar("SCRIPT_FILENAME", "/123.bla");
	//	env.setVar("SCRIPT_NAME", "/123.bla");

//		char **c = env.getEnv();
//		while (*c)
//		{
//			std::cout << *c << "\n";
//			c++;
//		}

		switch (method) {
			case m_get:
				env.setVar("QUERY_STRING", req->getHeader()->getQuery());
				break;
			case m_post:
				break;
		//	default: throw ft::runtime_error("Method not Allowed");
			case m_put:
				break;
			case m_head:
				break;
			case m_undefined:
				break;
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

	void CgiModule::reset_fd() {
		if (_cgi_in != -1)
			ft_close(_cgi_in);
		if (_cgi_out != -1)
			ft_close(_cgi_out);

		_cgi_in = -1;
		_cgi_out = -1;
	}

	void CgiModule::sendFileBody(FileBody *body) {
		_cgi_in = body->getFd();
	}

	void CgiModule::sendTextBody(TextBody *body) {
		std::string text = body->to_string();

		_cgi_in = open(_tmp_in.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
		write(_cgi_in, text.c_str(), text.size());
		ft_close(_cgi_in);
		_cgi_in = -1;
	}

	void CgiModule::threadPart(IRequest *req, Environment &envs) {
		sendRequest(req);
		char **c = envs.getEnv();
		while (*c)
		{
			std::cout << *c << "\n";
			c++;
		}
		_av = getArgv(_executable, _root + req->getHeader()->getPath());

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

	IResponse * CgiModule::getResult() {
		std::string		head_part;
		IHeader			*header = NULL;
		FileBody		*body = NULL;
		unsigned int	size;

		getHeadString(head_part);
		header = getHeader(head_part);
		if (head_part.empty() || !header)
			return _e_pager.getErrorPage(500);
		size = ft::getFileSize(_tmp_out.c_str());
		if (head_part.size() + 2 < size)
			body = new FileBody(_tmp_out, static_cast<int>(head_part.size() + 2));

		if (body && !header->isFieldInHeader("content-length"))
			header->setHeader("content-length", ft::to_string(body->size()));

		return new BasicResponse(header, body);
	}

	void CgiModule::getHeadString(std::string &head_part) {
		char buff;
		std::string strbuff;
		int readed;
		size_t  pos;

		_cgi_out = open(_tmp_out.c_str(), O_RDONLY );
		if (_cgi_out == -1)
			throw ft::runtime_error("CGI MODULE: GET RESULT: FILE OPEN FAILED");
		do {
			readed = read(_cgi_out, &buff, 1);
			if (readed == -1)
				throw ft::runtime_error("CGI MODULE: GET RESULT: READING FAILED");
			strbuff += buff;
			pos = strbuff.find("\r\n\r\n");
		} while (pos == std::string::npos && strbuff.size() < CGI_HEAD_LIMIT);
		if (pos == std::string::npos || strbuff.size() >= CGI_HEAD_LIMIT)
			head_part = "";
		head_part = strbuff.substr(0, pos + 2);
		ft_close(_cgi_out);
	}

	IHeader *CgiModule::getHeader(std::string header_str) {
		Header			*res = new Header(response);
		size_t 			pos;
		std::string		line;
		Client::req_r_states	s = Client::s_header_reading;

		do{
			pos = header_str.find("\r\n");
			if(pos == std::string::npos)
				return NULL;
			line = header_str.substr(0, pos);
			header_str.erase(0, pos + 2);

			HeaderMaker::fillHeader(line, res);

		} while (!header_str.empty() && !line.empty());
		handleStatusHeader(res);
		return res;
	}

	void CgiModule::reset() {
		_max_id = 0;
	}

	void CgiModule::handleStatusHeader(IHeader *header) {
		std::string str;
		size_t pos;
		if (header->isFieldInHeader("status"))
		{
			str = header->getHeader("status");
			pos = str.find(' ');
			if (pos != std::string::npos)
			{
				header->setResponseCode(atoi(str.substr(0,pos).c_str()));
				header->setCodeDescription(str.substr(pos + 1));
				return ;
			}
		}
		header->setResponseCode(500);
  		header->setCodeDescription(ft::getCodeDescr(500));
	}

} // ft