//
// Created by Skipjack Adolph on 4/4/21.
//

#include <string>

namespace ft {
	bool isNumber(std::string s) {
		size_t i = -1;

		while (s[++i])
			if (!isdigit(s[i]))
				return false;
		return true;
	}
}