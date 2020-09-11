/*
 * Author: Benjamin Mao
 * Project: STokenizer
 * Purpose: Functions to implement tokenizer
 *
 * Notes: None.
 */

#include "STokenizer.h"

#include <algorithm>

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer() :
	_buffer(),
	_pos(0)
{
	make_table(_table);
}

STokenizer::STokenizer(char str[]) :
	_pos(0)
{
	set_string(str);
	make_table(_table);
}

bool STokenizer::done()
{
	return !more();
}

bool STokenizer::more()
{
	return _pos < strlen(_buffer);
}

void STokenizer::set_string(char str[])
{
	strcpy_s(_buffer, MAX_BUFFER, str);
}

void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		for (int j = 0; j < MAX_COLUMNS; ++j)
			this->_table[i][j] = -1;
	}

	//init start 
	mark_table(START, 'a', 'z', ALPHA);
	mark_table(START, 'A', 'Z', ALPHA);
	
	mark_table(START, '0', '9', DIGIT);
	
	mark_table(START, '.', '.', PUNCT);
	mark_table(START, ',', ',', PUNCT);
	mark_table(START, '\'', '\'', PUNCT);
	mark_table(START, '?', '?', PUNCT);
	mark_table(START, '!', '!', PUNCT);
	mark_table(START, '\"', '\"', PUNCT);
	mark_table(START, '-', '-', PUNCT);
	mark_table(START, ';', ';', PUNCT);
	mark_table(START, ':', ':', PUNCT);
	mark_table(START, '/', '/', PUNCT);
	mark_table(START, '@', '@', PUNCT);
	mark_table(START, '(', '(', PUNCT);
	mark_table(START, ')', ')', PUNCT);
	mark_table(START, '[', '[', PUNCT);
	mark_table(START, ']', ']', PUNCT);
	mark_table(START, '*', '*', PUNCT);

	mark_table(START, ' ', ' ', SPACE);

	//init alpha
	mark_table(ALPHA, 'a', 'z', ALPHA);
	mark_table(ALPHA, 'A', 'Z', ALPHA);

	//init digit
	mark_table(DIGIT, '0', '9', DIGIT);
	mark_table(DIGIT, '.', '.', SUB_DIGIT);
	
	//init sub_punct
	mark_table(SUB_DIGIT, '0', '9', SUB_DIGIT);

	//init punct
	mark_table(PUNCT, '.', '.', PUNCT);
	mark_table(PUNCT, ',', ',', PUNCT);
	mark_table(PUNCT, '\'', '\'', PUNCT);
	mark_table(PUNCT, '?', '?', PUNCT);
	mark_table(PUNCT, '!', '!', PUNCT);
	mark_table(PUNCT, '\"', '\"', PUNCT);
	mark_table(PUNCT, '-', '-', PUNCT);
	mark_table(PUNCT, ';', ';', PUNCT);
	mark_table(PUNCT, ':', ':', PUNCT);
	mark_table(PUNCT, '/', '/', PUNCT);
	mark_table(PUNCT, '@', '@', PUNCT);
	mark_table(PUNCT, '(', '(', PUNCT);
	mark_table(PUNCT, ')', ')', PUNCT);
	mark_table(PUNCT, '[', '[', PUNCT);
	mark_table(PUNCT, ']', ']', PUNCT);
	mark_table(PUNCT, '*', '*', PUNCT);

	//init space
	mark_table(SPACE, ' ', ' ', SPACE);
}

void STokenizer::mark_table(int startState, char from, char to, int endState)
{
	while (from <= to)
	{
		_table[startState][from] = endState;
		++from;
	}
}

bool STokenizer::get_token(int& start_state, std::string& token)
{
	int endState = _table[start_state][_buffer[_pos]];

	if (endState == -1)
		return false;

	start_state = endState;
	token += _buffer[_pos];
	++_pos;

	return true;
}

STokenizer& operator>>(STokenizer& s, Token& t)
{
	std::string tokenStr;
	int state = 0;

	while (s.get_token(state, tokenStr));

	t = Token(tokenStr, state);

	return s;
}
