#pragma once
#include <IRequest.hpp>
#include <IResponse.hpp>
#include <Environment.hpp>
#include <ErrorPager.hpp>
#include <unistd.h>
#include <fcntl.h>
#include <FileBody.hpp>
#include <TextBody.hpp>
#include <iostream>

#define TMP_IN	"tmp_in"
#define TMP_OUT "tmp_out"

namespace ft{
    class CgiModule {
        private:
    		ErrorPager	_e_pager;
    		std::string _root;
    		std::string _executable;
    		std::string _home;
    		std::string _tmp_in;
    		std::string _tmp_out;

    		char 		**_av;

			int 		_cgi_in;
    		int 		_cgi_out;

    		void		setEnvs(IRequest *req, Environment &env);
			char		**getArgv(const std::string &arg0, const std::string &arg1);
			void 		deleteArgv(char ** args);

			void sendRequest(IRequest *req);
    		void 		initFiles();
    		void 		reset();
    		void 		sendFileBody(FileBody	*body);
    		void 		sendTextBody(TextBody	*body);
        public:
		void setExecutable(const std::string &executable);
		void setRoot(const std::string &root);
            CgiModule();
            CgiModule(const CgiModule &ref);
            ~CgiModule();
            CgiModule	&operator=(const CgiModule &ref);

            IResponse	*getResponse(IRequest *req);
    };
} // ft

