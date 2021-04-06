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
		LocationInit *location = getCorrectLocation(request, conf);
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
//			response->getHeader()->setHeader("Allow")
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
		int fd = ft::temporaryBody("<p>Новый файл</p>");
		//		IBody *body = pRequest->getBody();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(), fd);
		//		Пока что я закрываю FD
		close(fd);
	}

	void PutBuildPolicy::mutantExistingFile(IRequest *pRequest)
	{
		int fd = ft::temporaryBody("<!DOCTYPE HTML>\n<html>\n<head>\n<meta charset=\"utf-8\">\n<title>Тег H1 и H2</title>\n</head>\n<body>\n\n<h1>Lorem ipsum dolor sit amet</h1>\n<p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diem \nnonummy nibh euismod tincidunt ut lacreet dolore magna \naliguam erat volutpat.</p>\n\n</body>\n</html>");
		//		IBody *body = pRequest->getBody();
		_fmngr.copyFdToFile(pRequest->getHeader()->getURI(), fd);
		//		Пока что я закрываю FD
		close(fd);
	}

	void PutBuildPolicy::truncExistingFile(IRequest *pRequest)
	{
		_fmngr.getFd(pRequest->getHeader()->getURI(), O_TRUNC);
	}
}