#pragma once
#include <stdexcept>	// for runtime error
#include <unistd.h>		// for ft_close
#include <sys/time.h>
#include <IRequest.hpp>
#include <IResponse.hpp>
#include <IClient.hpp>
#include <defines.hpp>
#include <runtime_error.hpp>
#include <BodyReader.hpp>
#include <webserv.hpp>

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
			r_first_line = 1,
			r_headers = 2,
			r_breakline = 4,
			r_head_begin = 8,
			r_head_end = 16,
			r_end = 32,
			r_body_begin = 64,
			r_body_end = 128,
			r_begin = 256
		};

		enum req_r_states
		{
			s_not_begin,
			s_start_header_reading,
			s_header_reading,
			s_header_readed,
			s_start_body_reading,
//			todo do we really need this state???
			s_body_reading,
			s_end_reading
		};


		enum write_flags
		{
			w_head = 1,
			w_body = 2
		};

		enum state_flags
		{
			need_response = 1
		};

		Client(int id, int sock);
		virtual ~Client();
		Client			&operator=(const Client &ref);

		req_r_states	&getStates();
		int				getSock(void) const;
		struct timeval	const &getLastEventTime() const;

		bool			hasFlag(client_flags type, unsigned int flag);
		int				setFlag(client_flags type,unsigned int flag);
		int				unsetFlag(client_flags type,unsigned int flag);
		int				switchFlag(client_flags type,unsigned int flag);
		void			setLastRequest(IRequest *request);
		IRequest		*getLastRequest(void);
		bool			needsResponce(void);
		
		void			setLastResponse(IResponse *response);
		IResponse		*getLastResponse(void);
		std::string &	getReadBuff(void);
		void			resizeReadBuff(std::string::size_type pos);

		bool			requestReceived(void);
		bool			headerSent(void);
		bool			bodySent(void);

		void			sendHeader(void);
		void			sendBody(void);
		void			setStates(req_r_states states);
		BodyReader		*getBReader() const;
		void			setBReader(BodyReader *bReader);
		void			updateEventTime();
		unsigned long	getUsecsFromLastEvent();
		int 			getId();

		void 			reset();
		bool 			left();
		void 			setLeft();
		int 			requests();



	private:
		int 				_requests;
		bool 				_left;
		static unsigned int	_max_id;
		unsigned int		_id;
		int					_sock;
		int					_state_flags;
		int					_read_flags;
		int					_write_flags;
		struct timeval		_last_event;
		IRequest			*_last_request;
		IResponse			*_last_response;
		std::string 		_read_buff;
		req_r_states		_states;
		BodyReader			*_b_reader;

		Client();
		Client(const Client &ref);
		void 			clearResponse();
		void 			clearRequest();

		int				&getflags(client_flags type);

	};



} // namespace ft