#include <webserv.hpp>
#include <runtime_error.hpp>
namespace ft
{
	std::string			getHeaderKey(header_keys key)
	{
		switch (key)
		{
		case h_accept_charsets: return("Accept-Charsets");
		case h_accept_language: return("Accept-Language");
		case h_allow: return("Allow");
		case h_authorization: return("Authorization");
		case h_content_language: return("Content-Language");
		case h_content_length: return("Content-Length");
		case h_content_location: return("Content-Location");
		case h_content_type: return("Content-Type");
		case h_date: return("Date");
		case h_host: return("Host");
		case h_last_modified: return("Last-Modified");
		case h_location: return("Location");
		case h_referer: return("Referer");
		case h_retry_after: return("Retry-After");
		case h_server: return("Server");
		case h_transfer_encoding: return("Transfer-Encoding");
		case h_user_agent: return("User-Agent");
		case h_www_authenticate: return("WWW-Authenticate");
		case h_connection: return("Connection");
		case h_status: return("Status");
		case h_secret: return("X-Secret-Header-for-Test");
		default: return "";
		}
	}
}