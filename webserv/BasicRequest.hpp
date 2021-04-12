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
		int 	_port;
	public:
		BasicRequest();
		IHeader					*getHeader(void);
		IBody					*getBody(void);
		std::string				to_string(void) const;
		virtual  ~BasicRequest();
		void setBody(IBody *body);
		void setHeader(IHeader *header);
		BasicRequest(IHeader *head, IBody *body);
		BasicRequest &operator=(const BasicRequest &ref);

		int 					getPort();
		void 					setPort(int port);
	};

} // namespace ft