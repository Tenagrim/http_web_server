#include <PutBuildPolicy.hpp>

namespace ft
{
	PutBuildPolicy::PutBuildPolicy()
	{
	}

	PutBuildPolicy::~PutBuildPolicy()
	{
	}

	PutBuildPolicy::PutBuildPolicy(const PutBuildPolicy &ref)
	{(void)ref;}

	PutBuildPolicy &PutBuildPolicy::operator=(const PutBuildPolicy &ref)
	{
		(void)ref;
		return (*this);
	}

	IResponse		*PutBuildPolicy::buildResponse(IRequest *request)
	{
		(void) request;
		ServerInit *conf = getConfig();
		IResponse *response;
		applyConfig(conf);
		LocationInit *location = getCorrectLocation(request->getHeader()->getPath(), conf);
		if (ifCorrectMethod(request, location))
		{
			std::pair<bool, std::string> author = ifAuthentication(request, location);
			if (author.first && author.second == "")
			{
				IHeader *head = checkCommingURI(request);
				if (head == nullptr)
					return _e_pager.getErrorPage(404);
				response = new BasicResponse(head, NULL);
				return response;
			}
			else {
				response = _e_pager.getErrorPage(401);
				response->getHeader()->setHeader("WWW-Authenticate", "Basic realm=\""+author.second+"\"");
				return response;
			}
		}
		else {
			IResponse *response = _e_pager.getErrorPage(405);
			response->getHeader()->setHeader("allow", location->getArgs().find("limit_except")->second);
			return  _e_pager.getErrorPage(405);
		}
	}

	IHeader *PutBuildPolicy::checkCommingURI(IRequest *request)
	{
		//std::cout<<_fmngr.getRoot()<<std::endl;
		IHeader *head = new Header(response);
		if (!_fmngr.isFileExisting(request->getHeader()->getURI())) {
			head->setResponseCode(201);
			head->setCodeDescription(ft::getCodeDescr(201));
			head->setHeader("content-location", request->getHeader()->getURI());
			head->setHeader("connection", "close");
			creatFile(request);
		} else {
			if (request->getBody()) {
				head->setResponseCode(200);
				head->setCodeDescription(ft::getCodeDescr(200));
				head->setHeader("connection", "close");
				mutantExistingFile(request);
			} else {
				head->setResponseCode(204);
				head->setCodeDescription(ft::getCodeDescr(204));
				head->setHeader("content-location", request->getHeader()->getURI());
				head->setHeader("connection", "close");
				truncExistingFile(request);
			}
		}
		return head;
	}

	void PutBuildPolicy::creatFile(IRequest *pRequest)
	{
		int fd = pRequest->getBody()->getFd();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(),fd);
		ft_close(fd);
	}

	void PutBuildPolicy::mutantExistingFile(IRequest *pRequest)
	{
		int fd = pRequest->getBody()->getFd();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(), fd);
		ft_close(fd);
	}

	void PutBuildPolicy::truncExistingFile(IRequest *pRequest)
	{
		_fmngr.getFd(pRequest->getHeader()->getURI(), O_TRUNC);
	}
}