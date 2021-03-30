#include <Client.hpp>

namespace ft
{
	#pragma region Copilen

	Client::Client(int id,int sock) : _id(id), _sock(sock)
	{
		_state_flags = 0;
		_read_flags = 0;
		_write_flags = 0;
		_last_request = 0;
	}

	Client::~Client()
	{
		close(_sock);
		if (_last_request)
			delete _last_request;
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

	bool			Client::needsResponce(void)
	{
		if (hasFlag(state_flags, need_response))
			return true;
		return false;
	}
}