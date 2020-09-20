/*
 * Author: Benjamin Mao
 * Project: STokenizer
 * Purpose: Functions to implement FTokenizer
 *
 * Notes: None.
 */

#include "FTokenizer.h"

#include <string>

FTokenizer::FTokenizer(const char* fname) :
	_more(true),
	_f(fname)
{
	if (!_f.is_open())
		std::cout << "Failed to open file." << std::endl;
}

Token FTokenizer::next_token()
{
	Token t;
	_stk >> t;

	return t;
}

bool FTokenizer::more()
{
	if (_f.eof() && _stk.done())
		_more = false;
	else
		_more = true;

	return _more;
}

bool FTokenizer::get_new_block()
{
	if (!more())
		return false;

	std::string block;
	char charBuf;

	while ((block.size() < MAX_BLOCK - 1) && _f.get(charBuf))
		block += charBuf;

	_stk.set_string(block.c_str());
	
	return true;
}

FTokenizer& operator>>(FTokenizer& f, Token& t)
{
	t = f.next_token();

	if (t.token_str().empty())
		if (f.get_new_block())
			t = f.next_token();

	return f;
}
