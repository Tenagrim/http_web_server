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
#include <HeaderMaker.hpp>
#include <Header.hpp>

#define TMP_IN			"tmp_cgi_in"
#define TMP_OUT			"tmp_cgi_out"
#define CGI_HEAD_LIMIT	512

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

    		static int	_max_id;

    		void		setEnvs(IRequest *req, Environment &env);
			char		**getArgv(const std::string &arg0, const std::string &arg1);
			void 		deleteArgv(char ** args);

			void		sendRequest(IRequest *req);
    		void 		initFiles();
    		void 		reset_fd();
    		void 		sendFileBody(FileBody	*body);
    		void 		sendTextBody(TextBody	*body);
    		void		threadPart(IRequest *req, Environment &envs);
    		void		getHeadString(std::string &head_part);
    		IHeader		*getHeader(std::string header_str);
    		IResponse	*getResult();
    		void 		handleStatusHeader(IHeader *header);
        public:
            CgiModule(const CgiModule &ref);
            ~CgiModule();
            CgiModule();

            CgiModule	&operator=(const CgiModule &ref);
			void		setExecutable(const std::string &executable);
			void		setRoot(const std::string &root);
			static void reset();

            IResponse	*getResponse(IRequest *req);
    };
} // ft

