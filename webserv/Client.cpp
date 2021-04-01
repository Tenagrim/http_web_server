#include <Client.hpp>
#include <defines.hpp>

#ifdef DEBUG
# include <iostream>
#endif

namespace ft
{
	#pragma region Copilen

	Client::Client(int id,int sock) : _id(id), _sock(sock)
	{
		_state_flags = 0;
		_read_flags = 0;
		_write_flags = 0;
		_last_request = 0;
		_response = 0;
	}

	Client::~Client()
	{
		int ret;
		ret = close(_sock);
		#ifdef DEBUG
		std::cout << "CLIENT: CLOSING SOCKET[" << _sock << "]\n";
		if (ret == -1)
			std::cout << "CLIENT: FAILED TO CLOSE SOCKET [" << _sock << "]\n";
		#endif
		if (_last_request)
			delete _last_request;
		if (_response)
			delete _response;
	}

	Client::Client(const Client &ref)
	{
		(void)ref;
		throw std::runtime_error("No ipleentation");
	}

	Client &Client::operator=(const Client &ref)
	{
		(void)ref;
		throw std::runtime_error("No ipleentation");
		return (*this);
	}
	#pragma endregion /// Copilen
	
	int			Client::getSock(void) const
	{
		return _sock;
	}

	int				&Client::getflags(client_flags type)
	{
		switch (type)
		{
		case  state_flags:return(_state_flags); break;
		case  read_flags:return(_read_flags); break;
		case  write_flags:return(_write_flags); break;
		default: throw std::runtime_error("Wrong flag type"); break;
		}
	}

	bool			Client::hasFlag(client_flags type, unsigned int flag)
	{
		int &_flags = getflags(type);

		if (_flags & flag)
			return (true);
		else
			return (false);
	}

	int Client::setFlag(client_flags type, unsigned int flag)
	{
		int &_flags = getflags(type);
		_flags |= flag;
		return (1);
	}
	int Client::unsetFlag(client_flags type, unsigned int flag)
	{
		int &_flags = getflags(type);
		_flags &= ~flag;
		return (1);
	}
	int Client::switchFlag(client_flags type, unsigned int flag)
	{
		int	&_flags = getflags(type);
		_flags ^= flag;
		return (1);
	}	

	struct timeval	const &Client::getLastEventTime() const
	{
		return _last_event;
	}
	
	void			Client::setLastRequest(IRequest *request)
	{
		if (_last_request)
			delete _last_request;
		_last_request = request;
	}
	
	IRequest		*Client::getLastRequest(void)
	{
		return _last_request;
	}

	void			Client::setLastResponse(IResponse *response)
	{
		if (_response)
			delete response;
		_response = response;
	}

	IResponse		*Client::getLastResponse(void)
	{
		return _response;
	}
	bool			Client::needsResponce(void)
	{
		if (!hasFlag(read_flags, r_end))
			return (false);

		if (hasFlag(write_flags, w_head) && hasFlag(write_flags, w_body))
		{
			#ifdef DEBUG
				std::cout << "CLIENT: NO NEED TO RESPONSE\n";
			#endif
			return false;
		}
		std::cout << "CLIENT: NEED TO RESPONSE\n";
		return true;
	}
	bool			Client::requestReceived(void)
	{
		return(hasFlag(read_flags, r_end));
	}
	bool			Client::headerSent(void)
	{
		return(hasFlag(write_flags, w_head));
	}
	bool			Client::bodySent(void)
	{
		return(hasFlag(write_flags, w_body));
	}
	
	void			Client::sendHeader(void)
	{
		setFlag(write_flags, w_head);
	}

	void	Client::sendBody(void)
	{
		setFlag(write_flags, w_body);
	}


}