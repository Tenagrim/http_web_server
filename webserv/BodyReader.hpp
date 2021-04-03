//
// Created by Gerry Shona on 4/3/21.
//

#ifndef WEBSERV_BODYREADER_HPP
#define WEBSERV_BODYREADER_HPP

#include <IHeader.hpp>
#include <unistd.h>
#include <runtime_error.hpp>
#include <errno.h>
#define  LEN_CHUNKED -1

#define MIN_NUM_SIZE 4

namespace ft {
	class BodyReader {


		enum r_state
		{
			s_remains,
			s_len,
			s_block,
			s_end
		};

	private:
		r_state 			_state;

		std::string 		_remainder_of_header;

		std::string 		_block_size;
		char 				_last_readed;
		int 				_block_size_i;
		char 				*_read_buff;
		int 				_output_fd;
		int 				_pipe[2];
		bool 				_ended;
		int 				_readed_size;
		int 				_input_fd;
		int 				_content_length;

		int 				readWriteBlock(int size, int offset =0);

		void 				openPipe();

		int 				readRem();
		int 				readChunkLen();
		int 				readChunk();


		void 				write_block(const char *buff, int len, int offset = 0 );

		int 				getBlockLen();

		void 				endReading();


		BodyReader(const BodyReader &ref);
		BodyReader();
	public:
		void setRemainderOfHeader(char *remainderOfHeader);

		// CLIENT fd , ENCODING: LEN_CHUNKED or Content-length
		BodyReader(int input_fd, int content_length, std::string remainder = "");


		~BodyReader();
		// TODO: Complete copilen form

		//return values:  0 - end of body, 1 - readed
		int readBody();

		int get_resultFd() const;
		unsigned int	getSize() const;


	};

}

#endif //WEBSERV_BODYREADER_HPP
