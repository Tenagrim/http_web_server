#include <webserv.hpp>
#include <runtime_error.hpp>
namespace ft
{
	std::string			getHeaderKey(header_keys_enum key)
	{
		switch (key)
		{
		case h_accept_charsets: return("Accept-Charsets"); break;
		case h_accept_language: return("Accept-Language"); break;
		case h_allow: return("Allow"); break;
		case h_authorization: return("Authorization"); break;
		case h_content_language: return("Content-Language"); break;
		case h_content_length: return("Content-Length"); break;
		case h_content_location: return("Content-Location"); break;
		case h_content_type: return("Content-Type"); break;
		case h_date: return("Date"); break;
		case h_host: return("Host"); break;
		case h_last_modified: return("Last-Modified"); break;
		case h_location: return("Location"); break;
		case h_referer: return("Referer"); break;
		case h_retry_after: return("Retry-After"); break;
		case h_server: return("Server"); break;
		case h_transfer_encoding: return("Transfer-Encoding"); break;
		case h_user_agent: return("User-Agent"); break;
		case h_www_authenticate: return("WWW-Authenticate"); break;
		default: throw ft::runtime_error("Unrecognized header key"); break;
		}
	}
}