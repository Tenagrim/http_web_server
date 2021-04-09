#pragma once
#include <string>
#include <webserv.hpp>
#include <runtime_error.hpp>
namespace ft{
    class Environment {
        private:
    		char	**_vars;
    		int 	_size;
    		char 	*makeLine(const char* key, const char *value);
    		void 	addLine(char *line);
    		void 	clear();
        public:
        	Environment();
        	Environment(const Environment &ref);
        	~Environment();
        	Environment &operator=(const Environment &ref);

        	char 	**getEnv();
        	void setVar(std::string const &key, std::string const &value);
        	void setVar(char const *key, char const *value);
    };
} // ft

