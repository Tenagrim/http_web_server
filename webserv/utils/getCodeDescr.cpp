#include <string>
namespace ft
{
	std::string		getCodeDescr(int code)
	{
		switch (code)
		{
		case 100: return ("Continue"); break;
		case 101: return ("Switching Protocol"); break;
		case 102: return ("Processing"); break;
		case 103: return ("Early Hints"); break;
		case 200: return ("OK"); break;
		case 201: return ("Created"); break;
		case 202: return ("Accepted"); break;
		case 203: return ("Non-Authoritative Information"); break;
		case 204: return ("No Content"); break;
		case 205: return ("Reset Content"); break;
		case 206: return ("Partial Content"); break;
		case 300: return ("Multiple Choice"); break;
		case 301: return ("Moved Permanently"); break;
		case 302: return ("Found"); break;
		case 303: return ("See Other"); break;
		case 304: return ("Not Modified"); break;
		case 305: return ("Use Proxy"); break;
		case 306: return ("Switch Proxy"); break;
		case 307: return ("Temporary Redirect"); break;
		case 308: return ("Permanent Redirect"); break;
		case 400: return ("Bad Request"); break;
		case 401: return ("Unauthorized"); break;
		case 402: return ("Payment Required"); break;
		case 403: return ("Forbidden"); break;
		case 404: return ("Not Found"); break;
		case 405: return ("Method Not Allowed"); break;
		case 406: return ("Not Acceptable"); break;
		case 407: return ("Proxy Authentication Required"); break;
		case 408: return ("Request Timeout"); break;
		case 409: return ("Conflict"); break;
		case 410: return ("Gone"); break;
		case 411: return ("Length Required"); break;
		case 412: return ("Precondition Failed"); break;
		case 413: return ("Request Entity Too Large"); break;
		case 414: return ("Request-URI Too Long"); break;
		case 415: return ("Unsupported Media Type"); break;
		case 416: return ("Requested Range Not Satisfiable"); break;
		case 417: return ("Expectation Failed"); break;
		case 500: return ("Internal Server Error"); break;
		case 501: return ("Not Implemented"); break;
		case 502: return ("Bad Gateway"); break;
		case 503: return ("Service Unavailable"); break;
		case 504: return ("Gateway Timeout"); break;
		case 505: return ("HTTP Version Not Supported"); break;
		
		default: throw std::runtime_error("Urecognized response code"); break;
		}
	}
}