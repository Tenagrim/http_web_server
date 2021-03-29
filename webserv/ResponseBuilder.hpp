#pragma once
#include <IResponseBuilder.hpp>
#include <IFileManager.hpp>

#include <TextResponse.hpp>
#include <webserv.hpp>

namespace ft
{
	class ResponseBuilder : public IResponseBuilder
	{
	private:
		IFileManager		*_fmngr;
		ResponseBuilder();
	public:
		ResponseBuilder(IFileManager	*mngr);
		virtual ~ResponseBuilder();
		ResponseBuilder(const ResponseBuilder &ref);
		ResponseBuilder		&operator=(const ResponseBuilder &ref);


		IResponse			*buildResponse(IRequest	*request);
	};

}