#pragma once

#include <string>

namespace ft {
	static char const tokenPool[] = "# {};/\t\n\r:";
	class TokenPool {
	private:
	public:
		TokenPool();
		~TokenPool();

		bool checkInPool(int c);
	};
}