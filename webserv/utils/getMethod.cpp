#include <webserv.hpp>
#include <runtime_error.hpp>
namespace ft
{
	std::string			getMethodStr(const methods_enum key)
	{
		switch (key)
		{
		case m_get: return("GET"); break;
		case m_post: return("POST"); break;
		case m_head: return("HEAD"); break;
		case m_put: return("PUT"); break;
		default: throw ft::runtime_error("Unknown method"); break;
		}
	}
}