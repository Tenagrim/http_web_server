//
// Created by Skipjack Adolph on 4/5/21.
//

#include <vector>
#include <string>

namespace ft {
	std::vector<std::string> splitString(std::string const & basicString,
									  			std::string const & delim) {
		std::string::size_type		posStart = 0, posEnd;
		std::vector<std::string>	split;

		while ((posEnd = basicString.find(delim, posStart)) != std::string::npos) {
			split.push_back(basicString.substr(posStart, posEnd - posStart));
			posStart = posEnd + delim.size();
		}
		split.push_back(basicString.substr(posStart));
		return split;
	}
}
