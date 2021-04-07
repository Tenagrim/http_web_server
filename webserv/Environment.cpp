#include "Environment.hpp"

namespace ft{
    Environment::Environment() : _size(0)
    {
    	_vars = new char *[1];
    	if (!_vars)
			throw ft::runtime_error("ENVIRONMENT: ALLOCATION FAILED");
    	_vars[0] = nullptr;
    }
    
    Environment::Environment(const Environment &ref) : _vars(nullptr), _size(0){
        (void)ref;
    }
    
    Environment::~Environment()
    {
    	clear();
    }
    
    Environment &Environment::operator=(const Environment &ref){
    	if (&ref == this)
			return *this;
        (void)ref;
		return (*this);
    }

	char *Environment::makeLine(const char *key, const char *value) {
    	int len1 = static_cast<int>(ft_strlen(key));
    	int len2 = static_cast<int>(ft_strlen(value));
		char *res = new char [len1 + len2 + 2];

		if (!res)
			throw ft::runtime_error("ENVIRONMENT: ADD LINE: ALLOCATION FAILED");
		res[len1 + len2 + 1] = 0;
		res[len1] = '=';
		ft_memcpy(res, key, len1);
		ft_memcpy(res + len1 + 1, value, len2);
		return res;
    }

	void Environment::addLine(char *line) {
    	char **new_res = new char *[_size + 2];

		if (!new_res)
			throw ft::runtime_error("ENVIRONMENT: ADD LINE: ALLOCATION FAILED");
		new_res[_size + 1] = nullptr;
		for (int i = 0; i < _size; i++)
			new_res[i] = _vars[i];
		new_res[_size] = line;
		delete [] _vars;
		_vars = new_res;
		_size++;
	}

	void Environment::clear() {
    	for(int i = 0; i < _size; i++)
    		delete _vars[i];
		delete [] _vars;
	}

	char **Environment::getEnv() {
		return  _vars;
	}

	int Environment::setVar(const std::string &key, const std::string &value) {
		setVar(key.c_str(), value.c_str());
	}

	int Environment::setVar(const char *key, const char *value) {
		char *line = makeLine(key,	value);
		addLine(line);
	}
} // ft