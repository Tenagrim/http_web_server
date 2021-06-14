#pragma once
#include <string>
#include <map>
#include <webserv.hpp>
#include <vector>

namespace ft {
	class Authorization {
	private:
		std::map<std::string, std::string> map;
	public:
		Authorization();
		~Authorization();

		void setRealm(std::string key, std::string value);
		std::string getRealmKey(std::string realm);
		std::string getRealm(const char *key);
		bool checkAuth(std::string &request);
	};
}

