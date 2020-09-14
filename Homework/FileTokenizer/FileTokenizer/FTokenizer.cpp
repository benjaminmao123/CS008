#include "FTokenizer.h"

#include <string>

FTokenizer::FTokenizer(const char* fname) :
	_f(fname),
	_pos(0),
	_blockPos(0),
	_more(true)
{
	if (!_f.is_open())
	{
		std::cout << "Failed to open file." << std::endl;
		_more = false;
	}
}

Token FTokenizer::next_token()
{
	std::string buffer;

	//while (buffer.size() <= MAX_BLOCK && _f >> buffer)
	//{
	//	buffer += 
	//}

	return Token();
}

bool FTokenizer::more()
{
	return _more;
}

int FTokenizer::pos()
{
	return _pos;
}

int FTokenizer::block_pos()
{
	return _blockPos;
}

bool FTokenizer::get_new_block()
{
	return false;
}

FTokenizer& operator>>(FTokenizer& f, Token& t)
{
	t = f.next_token();

	return f;
}
