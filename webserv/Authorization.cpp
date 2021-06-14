#include <Authorization.hpp>

ft::Authorization::Authorization(): map() {
}


ft::Authorization::~Authorization() {
	map.clear();
}

void ft::Authorization::setRealm(std::string key, std::string value) {
	std::string res;
	std::string tmp = (key+":"+value);
	res = ft::base64_encode(reinterpret_cast<const unsigned char *>(tmp.c_str()), tmp.length());
	map[key] = (res);
}

std::string ft::Authorization::getRealmKey(std::string realm) {
	std::string base = ft::base64_decode(realm);
	std::vector<std::string> vec = splitString(base, ":");
	map[vec[0]] = (realm);
	return vec[0];
}

std::string ft::Authorization::getRealm(const char *key)
{
	std::string res;
	res = map.at(key);
	return res;
}

bool ft::Authorization::checkAuth(std::string &request)
{
	bool res = false;
	std::vector<std::string> vec = splitString(request, " ");
	std::map<std::string, std::string>::iterator it = map.begin();
	for (;it != map.end(); ++it) {
		if (it->second == vec[1]){
			res = true;
			break;
		}
	}
	return res;
}

