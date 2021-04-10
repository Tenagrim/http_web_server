//
// Created by Skipjack Adolph on 4/10/21.
//

#include <webserv.hpp>

#include <string>
namespace ft
{
	static std::string parsedHeads[] = {
			"accept-charsets",
			"accept-language",
			"allow",
			"authorization",
			"content-language",
			"content-length",
			"content-location",
			"content-type",
			"date",
			"host",
			"last-modified",
			"location",
			"referer",
			"retry-after",
			"server",
			"transfer-encoding",
			"user-agent",
			"www-authenticate",
			"accept-encoding",
			""
	};

	bool isParsedHeader(std::string const &head)
	{
		size_t i = -1;

		while (parsedHeads[++i] != "")
		{
			if (head == parsedHeads[i])
				return true;
		}
		return false;
	}
}