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
		applyConfig(conf);
		LocationInit *location = getCorrectLocation(request->getHeader()->getPath(), conf);
		if (ifCorrectMethod(request, location))
		{
			IHeader *head = checkCommingURI(request);
			if (head == nullptr)
				return _e_pager.getErrorPage(404);
			BasicResponse *response = new BasicResponse(head, NULL);
			return response;
		}
		else {
			IResponse *response = _e_pager.getErrorPage(405);
			response->getHeader()->setHeader(h_allow, location->getArgs().find("limit_except")->second);
			return  _e_pager.getErrorPage(405);
		}
	}

	IHeader *PutBuildPolicy::checkCommingURI(IRequest *request)
	{
		std::cout<<_fmngr.getRoot()<<std::endl;
		IHeader *head = new Header(response);
		if (!_fmngr.isFileExisting(request->getHeader()->getURI())) {
			head->setResponseCode(201);
			head->setCodeDescription(ft::getCodeDescr(201));
			head->setHeader(h_content_location, request->getHeader()->getURI());
			head->setHeader(h_connection, "close");
			creatFile(request);
		} else {
			if (request->getBody()) {
				head->setResponseCode(200);
				head->setCodeDescription(ft::getCodeDescr(200));
				mutantExistingFile(request);
			} else {
				head->setResponseCode(204);
				head->setCodeDescription(ft::getCodeDescr(204));
				head->setHeader(h_content_location, request->getHeader()->getURI());
				truncExistingFile(request);
			}
		}
		return head;
	}

	void PutBuildPolicy::creatFile(IRequest *pRequest)
	{
		int fd = pRequest->getBody()->getFd();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(),fd);
		close(fd);
	}

	void PutBuildPolicy::mutantExistingFile(IRequest *pRequest)
	{
		int fd = pRequest->getBody()->getFd();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(), fd);
		close(fd);
	}

	void PutBuildPolicy::truncExistingFile(IRequest *pRequest)
	{
		_fmngr.getFd(pRequest->getHeader()->getURI(), O_TRUNC);
	}
}