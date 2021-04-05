#include <Client.hpp>
#include <BasicRequest.hpp>
#ifdef DEBUG
# include <iostream>
#endif

namespace ft
{
	unsigned int Client::_max_id = 0;

	#pragma region Copilen

	Client::Client(int id,int sock) :
		_id(id),
		_sock(sock),
		_b_reader(),
		_last_request()
	{
		_state_flags = 0;
		_read_flags = 0;
		_write_flags = 0;
		_last_request = 0;
		_last_response = 0;
		_states = s_not_begin;
		updateEventTime();
		_id = _max_id++;
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
		if (_last_response)
			delete _last_response;
	}

	Client::Client(const Client &ref)
	{
		(void)ref;
		throw ft::runtime_error("No ipleentation");
	}

	Client &Client::operator=(const Client &ref)
	{
		(void)ref;
		throw ft::runtime_error("No ipleentation");
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
		default: throw ft::runtime_error("Wrong flag type"); break;
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
		if (_last_response)
			delete response;
		_last_response = response;
	}

	IResponse		*Client::getLastResponse()
	{
		return _last_response;
	}
	bool			Client::needsResponce()
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
		#ifdef DEBUG
			std::cout << "CLIENT: NEED TO RESPONSE\n";
		#endif
		return true;
	}
	bool			Client::requestReceived()
	{
		return(hasFlag(read_flags, r_end));
	}
	bool			Client::headerSent()
	{
		return(hasFlag(write_flags, w_head));
	}
	bool			Client::bodySent()
	{
		return(hasFlag(write_flags, w_body));
	}
	
	void			Client::sendHeader()
	{
		setFlag(write_flags, w_head);
	}

	void	Client::sendBody()
	{
		setFlag(write_flags, w_body);
	}

	std::string & Client::getReadBuff()
	{
		return _read_buff;
	}

	Client::req_r_states &Client::getStates() {
		return _states;
	}

	void Client::setStates(Client::req_r_states states) {
		_states = states;
	}

	void Client::resizeReadBuff(std::string::size_type pos) {
		_read_buff.resize(pos);
	}

	BodyReader *Client::getBReader() const {
		return _b_reader;
	}

	void Client::setBReader(BodyReader *bReader) {
		_b_reader = bReader;
	}

	void Client::updateEventTime() {
		gettimeofday(&_last_event, NULL);
	}

	unsigned long Client::getUsecsFromLastEvent() {
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (ft::get_time_udiff(&_last_event, &tv));
	}

	void Client::clearRequest() {
		if (_last_request){
			delete _last_request;
			_last_request = nullptr;
		}
	}

	void Client::clearResponse() {
		if (_last_response) {
			delete _last_response;
			_last_response = nullptr;
		}
	}

	void Client::reset() {
		clearRequest();
		clearResponse();
		_state_flags = 0;
		_read_flags = 0;
		_write_flags = 0;
		_states = s_not_begin;
		_b_reader->reset();
		updateEventTime();

	}
}