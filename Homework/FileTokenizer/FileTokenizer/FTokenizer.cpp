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
	_f(fname, std::ifstream::binary)
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
	return !(_f.eof() && _stk.done());
}

bool FTokenizer::get_new_block()
{
	if (!more())
		return false;

	char block[MAX_BUFFER];
	_f.read(block, MAX_BLOCK - 1);
	block[MAX_BLOCK] = '\0';

	_stk.set_string(block);
	
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
