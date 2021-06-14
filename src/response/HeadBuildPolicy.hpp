#pragma once
#include "ABuildPolicy.hpp"
namespace ft
{

	class HeadBuildPolicy : public ABuildPolicy
	{
	private:
		HeadBuildPolicy(const HeadBuildPolicy &ref);
	public:
		HeadBuildPolicy();
		virtual ~HeadBuildPolicy();
		HeadBuildPolicy	&operator=(const HeadBuildPolicy &ref);
		IResponse		*buildResponse(IRequest *request);
	};

} //