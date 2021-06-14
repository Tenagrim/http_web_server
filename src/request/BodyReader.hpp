//
// Created by Gerry Shona on 4/3/21.
//

#ifndef WEBSERV_BODYREADER_HPP
#define WEBSERV_BODYREADER_HPP

#include <IHeader.hpp>
#include <unistd.h>
#include <defines.hpp>
#include <runtime_error.hpp>
#include <errno.h>
#include <fcntl.h>
#include <src/components/FileBody.hpp>
#include <list>
#define  LEN_CHUNKED -1
//#define  B_READER_BUFF_SIZE

#define MIN_NUM_SIZE 4

namespace ft {
	class BodyReader {
		enum r_state
		{
			s_remains,
			s_len,
			s_block,
			s_p_block,
			s_r_ending,
			s_a_len,
			s_a1_len,
			s_pp_block,
			s_end,
			s_r_by_len
		};

	private:

		static unsigned int	_max_id;
		r_state 			_state;
		std::list<r_state>	_prev_state;

		std::string 		_remainder_of_header;
		std::string 		_filename;
		std::string 		_block_size;
		char 				_last_readed;
		int 				_block_size_i;
		char 				*_read_buff; // may be local
		int 				_output_fd; // read / write
		bool 				_ended;
		int 				_written_size;
		int 				_input_fd;
		int 				_offset;
		int 				_content_length;
		int 				_last_readed_bytes;
		int					_readed_bytes;

		int 				readWriteBlock(int size, int offset =0);
		void 				openFile();
		int 				readRem();
		int 				readChunkLen(int n);
		int 				readChunk();
		int 				readPBlock();
		int 				readPPBlock();
		int 				readEnding();


		int					write_block(const char *buff, int len, int offset = 0 );
		int 				endReading(int ret);

		int 				readByLen();
		BodyReader(const BodyReader &ref);
		BodyReader();
		void 				setState(r_state state);
		int					get_resultFd() const;
		unsigned int		getSize() const;
	public:
		static void 		reset();
		int					getWritten() const;
		static unsigned int getMaxId();

		//void setRemainderOfHeader(char *remainderOfHeader);
		const std::string	&getFilename() const;

		// CLIENT fd , ENCODING: LEN_CHUNKED or Content-length
		BodyReader(int input_fd, int content_length, std::string remainder = "");


		~BodyReader();
		// TODO: Complete copilen form

		//return values:  0 - end of body, 1 - readed
		int					readBody();

		IBody				*getBody();

	};
}

#endif //WEBSERV_BODYREADER_HPP
