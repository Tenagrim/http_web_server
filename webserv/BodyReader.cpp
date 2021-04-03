//
// Created by Gerry Shona on 4/3/21.
//

#include "BodyReader.hpp"

int ft::BodyReader::getChunkLen() const {
	return _chunk_len;
}

void ft::BodyReader::setChunkLen(int chunkLen) {
	_chunk_len = chunkLen;
}

void ft::BodyReader::setEncoding(ft::content_encoding encoding) {
	_encoding = encoding;
}

ft::BodyReader::BodyReader() :
_remainder_of_header(0),
_chunk_len(0),
_output_fd(-1),
_pipe(), _opened(false),
_encoding(length)
{
}

ft::BodyReader::~BodyReader() {

}

ft::BodyReader::BodyReader(const ft::BodyReader &ref) : _remainder_of_header(), _chunk_len(), _output_fd(), _pipe() {
	(void) ref;
}



int ft::BodyReader::readBody(int &fd) {
	openPipe();
	if (_remainder_of_header)
		handle_rem();
	return 0;
}

void ft::BodyReader::openPipe() {
	if (!_opened)
	{
		if( pipe(_pipe) == -1)
			throw ft::runtime_error("CANT OPEN PIPE: " +std::string(strerror(errno)));
		_output_fd = _pipe[1];
	}
}

void ft::BodyReader::handle_rem() {
	int  len;

	len = ft::ft_strlen(_remainder_of_header);

	_remainder_of_header = nullptr;
}

void ft::BodyReader::setRemainderOfHeader(char *remainderOfHeader) {
	_remainder_of_header = remainderOfHeader;
}
