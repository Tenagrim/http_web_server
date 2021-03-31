#include <TokenPool.hpp>

ft::TokenPool::TokenPool() {
}

ft::TokenPool::~TokenPool() {
}

bool ft::TokenPool::checkInPool(int c) {
	if (strchr(tokenPool, c))
		return true;
	return false;
}
