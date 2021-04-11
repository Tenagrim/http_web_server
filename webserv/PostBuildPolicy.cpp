#include <PostBuildPolicy.hpp>

namespace ft
{
	PostBuildPolicy::PostBuildPolicy()
	{
	}
	
	PostBuildPolicy::~PostBuildPolicy()
	{
	}

	PostBuildPolicy::PostBuildPolicy(const PostBuildPolicy &ref)
	{(void)ref;}

	PostBuildPolicy &PostBuildPolicy::operator=(const PostBuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IResponse		*PostBuildPolicy::buildResponse(IRequest *request)
	{
		(void) request;
		IResponse *response = NULL;
		std::cout<<request->getHeader()->to_string()<<std::endl;
		ServerInit *conf = getConfig();
		applyConfig(conf);
		LocationInit *location = extensionCheck(request, conf);
		if (!location)
			location = getCorrectLocation(request->getHeader()->getPath(), conf);
		if (ifCorrectMethod(request, location))
		{
			std::pair<bool, std::string> author = ifAuthentication(request, location);
			if (author.first && author.second == "")
			{
				if (ifCorrectBodySize(request, location))
				{
					response = redirectToCGI(request, location);
					if (!response)
					{
						response = generateFile(request);
					}
				} else
				{
					response = _e_pager.getErrorPage(413);
				}
			} else {
				response = _e_pager.getErrorPage(401);
				response->getHeader()->setHeader("WWW-Authenticate", "Basic realm=\""+author.second+"\"");
				return response;
			}
		} else {
			IResponse *response = _e_pager.getErrorPage(405);
			response->getHeader()->setHeader("allow", location->getArgs().find("limit_except")->second);
			response = _e_pager.getErrorPage(405);
			response->getHeader()->setHeader("allow", location->getArgs().find("limit_except")->second);
			return response;
		}
		return response;
	}

	IResponse *PostBuildPolicy::generateFile(IRequest *request)
	{
		std::cout<<_fmngr.getRoot()<<std::endl;
		IHeader *head = new Header(response);
		head->setHTTPV(request->getHeader()->getHTTPVersion());
		head->setResponseCode(405);
		head->setCodeDescription(ft::getCodeDescr(405));
		head->setHeader("allow", "GET, HEAD");
		head->setHeader("connection", "close");
		if (!_fmngr.isFileExisting(request->getHeader()->getURI())) {
			head->setResponseCode(201);
			head->setCodeDescription(ft::getCodeDescr(201));
			head->setHeader("content-location", request->getHeader()->getURI());
			head->setHeader("content-length", std::to_string(request->getBody()->size()));
			head->setHeader("connection", "close");
			creatFile(request);
		} else {
			if (request->getBody()) {
				head->setResponseCode(303);
				head->setCodeDescription(ft::getCodeDescr(303));
				head->setHeader("location", "/post_body");
				head->setHeader("content-length", std::to_string(request->getBody()->size()));
				head->setHeader("connection", "close");
				mutantExistingFile(request);
			} else {
				head->setResponseCode(204);
				head->setCodeDescription(ft::getCodeDescr(204));
				head->setHeader("content-location", request->getHeader()->getURI());
				head->setHeader("content-length", std::to_string(request->getBody()->size()));
				head->setHeader("connection", "close");
				truncExistingFile(request);
			}
		}
		BasicResponse *response = new BasicResponse(head, NULL);
		return response;
	}

	void PostBuildPolicy::creatFile(IRequest *pRequest)
	{
		int fd = pRequest->getBody()->getFd();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(),fd);
		ft_close(fd);
	}

	void PostBuildPolicy::mutantExistingFile(IRequest *pRequest)
	{
		int fd = pRequest->getBody()->getFd();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(), fd);
		ft_close(fd);
	}

	void PostBuildPolicy::truncExistingFile(IRequest *pRequest)
	{
		_fmngr.getFd(pRequest->getHeader()->getURI(), O_TRUNC);
	}
}