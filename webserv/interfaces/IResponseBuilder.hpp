#pragma once
#include <IRequest.hpp>
#include <IResponse.hpp>
namespace ft
{
	class IResponseBuilder
	{
	public:
	virtual		IResponse	*buildResponse(IRequest	*request) = 0;
	virtual		~IResponseBuilder(){};
	};
}