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

STokenizer::STokenizer(const char str[]) :
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
	return _buffer[_pos] != '\0';
}

void STokenizer::set_string(const char str[])
{
	strcpy_s(_buffer, MAX_BUFFER, str);
	_pos = 0;
}

void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
	char punc[] = ".,\'?!\"-;:/@()[]*";

	for (int i = 0; i < MAX_ROWS; ++i)
	{
		for (int j = 0; j < MAX_COLUMNS; ++j)
			_table[i][j] = -1;
	}

	//init start 
	mark_table(_table, START, 'a', 'z', ALPHA);
	mark_table(_table, START, 'A', 'Z', ALPHA);

	mark_table(_table, START, '0', '9', DIGIT);

	for (int i = 0; i < strlen(punc); ++i)
		mark_table(_table, START, punc[i], punc[i], PUNCT);

	mark_table(_table, START, ' ', ' ', SPACE);

	for (int i = 0; i < MAX_COLUMNS; ++i)
		if (_table[START][i] == -1)
			_table[START][i] = UNKNOWN;

	//init alpha
	mark_table(_table, ALPHA, 'a', 'z', ALPHA);
	mark_table(_table, ALPHA, 'A', 'Z', ALPHA);

	//init digit
	mark_table(_table, DIGIT, '0', '9', DIGIT);
	mark_table(_table, DIGIT, '.', '.', SUB_DIGIT);
	
	//init sub_digit
	mark_table(_table, SUB_DIGIT, '0', '9', SUB_DIGIT);

	//init punct
	for (int i = 0; i < strlen(punc); ++i)
		mark_table(_table, PUNCT, punc[i], punc[i], PUNCT);

	//init space
	mark_table(_table, SPACE, ' ', ' ', SPACE);
}

void STokenizer::mark_table(int _table[][MAX_COLUMNS], int startState, 
							char from, char to, int endState)
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
