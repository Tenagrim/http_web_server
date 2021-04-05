//
// Created by Gerry Shona on 4/5/21.
//
#include <webserv.hpp>
namespace ft
{
	bool				methodNeedsBody(methods_enum method) {
		return (method == m_post || method == m_put);
	}
}
