//
// Created by Skipjack Adolph on 4/4/21.
//

#include <string>

namespace ft {
	std::string 		strToLower(const std::string & s) {
		std::string		res;
		size_t			i = -1;

		while (s[++i])
			res += std::tolower(s[i]);
		return res;
	}
}
