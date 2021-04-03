//
// Created by Gerry Shona on 4/3/21.
//

#ifndef WEBSERV_BODYREADER_HPP
#define WEBSERV_BODYREADER_HPP
#include <IHeader.hpp>
#include <unistd.h>
#include <runtime_error.hpp>
#include <errno.h>
namespace ft {
	enum content_encoding
			{
				length,
				chunked
			};
	class BodyReader {
	private:
		char 				*_remainder_of_header;
	public:
		void setRemainderOfHeader(char *remainderOfHeader);

	private:
		int 				_chunk_len;
		content_encoding	_encoding;
		int 				_output_fd;
		int 				_pipe[2];
		bool 				_opened;

		void 				openPipe();
		void 				handle_rem();

		BodyReader(const BodyReader &ref);
	public:

		void setEncoding(content_encoding encoding);
		BodyReader();
		~BodyReader();
		// TODO: Complete copilen form
		int readBody(int & fd);

		int getChunkLen() const;

		void setChunkLen(int chunkLen);
	};

}
#endif //WEBSERV_BODYREADER_HPP
