#pragma once
#include <IResponseBuilder.hpp>
#include <ABuildPolicy.hpp>

#include <GetBuildPolicy.hpp>
#include <PostBuildPolicy.hpp>
#include <PutBuildPolicy.hpp>
#include <defines.hpp>
#include <map>

namespace ft
{
	class ResponseBuilder : public IResponseBuilder
	{
	private:
		typedef std::map<std::string, ABuildPolicy*> policy_map;
		//IFileManager		*_fmngr;
		ITimeMachine		*_t_machine;

		//GetBuildPolicy		_get_build_pol;	
		//PostBuildPolicy		_post_build_pol;	
		//PostBuildPolicy		_post_build_pol;	

		policy_map			_policies;

		ResponseBuilder(const ResponseBuilder &ref);
	public:
		ResponseBuilder();
		virtual ~ResponseBuilder();
		ResponseBuilder		&operator=(const ResponseBuilder &ref);

		IResponse			*buildResponse(IRequest	*request);
	};

}
