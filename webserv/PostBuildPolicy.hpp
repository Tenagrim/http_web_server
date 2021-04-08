#pragma once
#include <ABuildPolicy.hpp>
namespace ft
{

	class PostBuildPolicy : public ABuildPolicy
	{
	private:
		PostBuildPolicy(const PostBuildPolicy &ref);

	public:
		PostBuildPolicy();
		virtual ~PostBuildPolicy();
		PostBuildPolicy &operator=(const PostBuildPolicy &ref);
		IResponse		*buildResponse(IRequest *request);

		IResponse * redirectToCGI(IRequest *request, LocationInit *location);

		IResponse *generateFile(IRequest *request);

		void creatFile(IRequest *pRequest);

		void mutantExistingFile(IRequest *pRequest);

		void truncExistingFile(IRequest *pRequest);
	};


} // namespace ft