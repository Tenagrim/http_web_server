#pragma once
#include <stdexcept>	// for runtime error
#include <unistd.h>		// for close
#include <sys/time.h>
#include <IRequest.hpp>
#include <IClient.hpp>
namespace ft
{
	class Client : public IClient
	{
	public:
		enum client_flags
		{
			state_flags,
			read_flags,
			write_flags
		};

		enum read_flags
		{
			first_line,
			headers,
			breakline,
			body,
			end
		};

		enum state_flags
		{
			need_response = 1
		};

		Client(int id, int sock);
		virtual ~Client();
		Client(const Client &ref);
		Client			&operator=(const Client &ref);
		
		int				getSock(void) const;
		struct timeval	const &getLastEventTime() const;

		bool			hasFlag(client_flags type, unsigned int flag);
		int				setFlag(client_flags type,unsigned int flag);
		int				unsetFlag(client_flags type,unsigned int flag);
		int				switchFlag(client_flags type,unsigned int flag);
		void			setLastRequest(IRequest *request);
		IRequest		*getLastRequest(void);
		bool			needsResponce(void);

	private:
		int					_id;
		int					_sock;
		int					_state_flags;
		int					_read_flags;
		int					_write_flags;
		struct timeval		_last_event;
		IRequest			*_last_request;

		Client();
		int				&getflags(client_flags type);
	};



} // namespace ft