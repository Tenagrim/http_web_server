#pragma once
#include <IResponse.hpp>
#include <stdexcept>
namespace ft
{

	class BasicResponse : public IResponse
	{
	private:
		IHeader			*_header;
		IBody			*_body;
		BasicResponse();
		BasicResponse(const BasicResponse &ref);
		BasicResponse &operator=(const BasicResponse &ref);
	public:
		BasicResponse(IHeader *head, IBody *body);
		virtual ~BasicResponse();
		
		IHeader					*getHeader(void);
		IBody					*getBody(void);
		std::string				to_string(void) const;
		unsigned long			size() const;
	};


} // namespace ft
