//
// Created by Gerry Shona on 4/3/21.
//

#include <BodyReader.hpp>

ft::BodyReader::BodyReader()
{/* Illegal */}

ft::BodyReader::BodyReader(int input_fd, int content_length, std::string rem) :
		_remainder_of_header(rem),
		_read_buff(),
		_output_fd(-1),
		_pipe(),
		_ended(false),
		_readed_size(0),
		_input_fd(input_fd),
		_content_length(content_length)
{
	if (!rem.empty())
		_state = s_remains;
	else
		_state = s_len;
	openPipe();
}
ft::BodyReader::~BodyReader()
{}


void
ft::BodyReader::openPipe() {
	int ret = pipe(_pipe);
		if( ret == -1)
			throw ft::runtime_error("CANT OPEN PIPE: " +std::string(strerror(errno)));
		_output_fd = _pipe[0];
}

void ft::BodyReader::setRemainderOfHeader(char *remainderOfHeader) {
	_remainder_of_header = remainderOfHeader;
}

void ft::BodyReader::write_block(const char *buff, int len, int offset) {
	int ret = write(_pipe[1], buff + offset, len - offset);
	if (ret != len - offset)
		throw ft::runtime_error("Error in writing block:" + std::string(strerror(errno)));
}


int ft::BodyReader::get_resultFd() const {
	if (!_ended)
		throw ft::runtime_error("Body was not fully readed\n");
	return _output_fd;
}

unsigned int ft::BodyReader::getSize() const {
	return  _readed_size;
}

void ft::BodyReader::endReading() {
	if (!_ended)
	{
		_ended = true;
		close(_pipe[1]);
		_output_fd = _pipe[0];
	}
}

int ft::BodyReader::readBody() {
	int ret;
	if (_state == s_remains) {
		ret = readRem();
		if (ret != 1) {
			endReading();
			return (ret);
		}
	}

	switch(_state) {
		case s_len: return (readChunkLen()); break;
		case s_block: return(readChunk()); break;
		case s_end: return 0; break;
	}
	return 0;
}

int ft::BodyReader::getBlockLen()
{

}


int ft::BodyReader::readRem()
{
	int pos ;
	int len;
	while (!_remainder_of_header.empty())
	{
		pos = _remainder_of_header.find("\r\n");
		//_block_size = _remainder_of_header;
		if (pos == std::string::npos)
		{                // В остатке нет длины блока
			_state = s_len;

			read(1, &_last_readed, _input_fd);
			if (_last_readed == '\r')
				_state = s_block;
			else
				_block_size += _last_readed;
			return 1;
		}
		else
		{
			_block_size = _remainder_of_header.substr(0, pos);
			if (_block_size == "0")
				return 0;
			len = std::stoi(_block_size); //         !!!!!!!!!!!  ATTENTION !!!!!!!!!
			_remainder_of_header.erase(0, pos + 2);
			if (len > _remainder_of_header.size())
			{
				write_block(_remainder_of_header.c_str(), _remainder_of_header.size());
				try {
					readWriteBlock( len - _remainder_of_header.size() + 2);
				}
				catch (ft::runtime_error)
				{
					return -1;
				}
				_state = s_len;
				_block_size.clear();
				return 1;
			}
			else
			{
				//pos = _remainder_of_header.find("\r\n");

				//if (pos == std::string::npos)
				//	throw ft::runtime_error("AAAAAAAAAAAAAAAAAAAA");
				try {
					write_block(_remainder_of_header.c_str(), len);
				}
				catch (ft::runtime_error){return  -1;}
				_state = s_len;
				_remainder_of_header.erase(0, len + 2);
			}
		}
	}
}

int ft::BodyReader::readChunkLen()
{
	read(_input_fd, &_last_readed, 1);
	if (_last_readed == '\r')
	{
		_state = s_block;
		if (_block_size == "0")
		{
			endReading();
			return (0);
		}
		if (_block_size == "")
			return -1;
		_block_size_i = std::stoi(_block_size);  // !!!!!!!!!!!! ATTENTION !!!!!!!!!!!!!!!!!!!
		_block_size.clear();
		return 1;
	}else
	{
		_block_size += _last_readed;
		_state = s_len;
		return 1;
	}
}

int ft::BodyReader::readChunk()
{
	try {
	if (readWriteBlock(_block_size_i + 3, 1) == -1)
		return (-1);
	}catch (ft::runtime_error){return -1;}
	_state = s_len;
	return (1);
}

int ft::BodyReader::readWriteBlock(int size, int offset) {
	int ret;

	_read_buff = (char*)malloc(size);
	if (!_read_buff)
		throw ft::runtime_error("Malloc failed");
	ret =  read(_input_fd, _read_buff, size);
	if (ret != size) {
		free(_read_buff);
		return -1;
	}
	if (offset == 1 && _read_buff[0] != '\n')
	{
		free(_read_buff);
		return (-1);
	}
	if (_read_buff[size -1] == '\n' && _read_buff[size -2] == '\r')
		size -= 2;
	write_block(_read_buff, size, offset);
	free(_read_buff);
	_read_buff = nullptr;
	return 1;
}

