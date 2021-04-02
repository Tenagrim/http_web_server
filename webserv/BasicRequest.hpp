#pragma once

#include <IRequest.hpp>
#include <runtime_error.hpp>

namespace ft
{
	class BasicRequest : public IRequest
	{
	private:
		BasicRequest(const BasicRequest &ref);
		IHeader	*_header;
		IBody	*_body;
	public:
		BasicRequest();
		IHeader					*getHeader(void);
		IBody					*getBody(void);
		std::string				to_string(void) const;
		~BasicRequest();
		BasicRequest(IHeader *head, IBody *body);
		BasicRequest &operator=(const BasicRequest &ref);
	};

} // namespace ft