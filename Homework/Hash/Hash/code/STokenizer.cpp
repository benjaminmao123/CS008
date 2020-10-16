/*
 * Author: Benjamin Mao
 * Project: STokenizer
 * Purpose: Functions to implement tokenizer
 *
 * Notes: None.
 */

#include <algorithm>
#include <cmath>

#include "STokenizer.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer() : _buffer(),
						   _pos(0)
{
	make_table(_table);
}

STokenizer::STokenizer(const char str[]) : _pos(0)
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

	SMLibrary::init_table(_table);

	//init start
	SMLibrary::mark_cells(START, _table, 'a', 'z', ALPHA);
	SMLibrary::mark_cells(START, _table, 'A', 'Z', ALPHA);

	SMLibrary::mark_cells(START, _table, '0', '9', DIGIT);

	SMLibrary::mark_cells(START, _table, punc, PUNCT);

	SMLibrary::mark_cell(START, _table, ' ', SPACE);

	for (int i = 0; i < MAX_COLUMNS; ++i)
		if (_table[START][i] == -1)
			_table[START][i] = UNKNOWN;

	//init alpha
	SMLibrary::mark_cells(ALPHA, _table, 'a', 'z', ALPHA);
	SMLibrary::mark_cells(ALPHA, _table, 'A', 'Z', ALPHA);

	//init digit
	SMLibrary::mark_cells(DIGIT, _table, '0', '9', DIGIT);
	SMLibrary::mark_cell(DIGIT, _table, '.', DECIMAL);

	//init sub_digit
	SMLibrary::mark_cells(DECIMAL, _table, '0', '9', DECIMAL_SUCCESS);
	SMLibrary::mark_cells(DECIMAL_SUCCESS, _table, '0', '9', DECIMAL_SUCCESS);

	//init punct
	SMLibrary::mark_cells(PUNCT, _table, punc, PUNCT);

	//init space
	SMLibrary::mark_cell(SPACE, _table, ' ', SPACE);

	SMLibrary::mark_success(_table, 0);
	SMLibrary::mark_success(_table, 1);
	SMLibrary::mark_success(_table, 2);
	SMLibrary::mark_success(_table, 3);
	SMLibrary::mark_success(_table, 4);
	SMLibrary::mark_fail(_table, 5);
	SMLibrary::mark_success(_table, 6);
	SMLibrary::mark_success(_table, 7);
}

bool STokenizer::get_token(int &start_state, std::string &token)
{
	if (done())
		return false;

	std::string tokenBuffer;
	int tokenBufferPos = _pos;

	char ch = _buffer[_pos];

	if (ch < 0 || ch > 127)
	{
		++_pos;
		start_state = UNKNOWN;
		token += ch;

		return true;
	}

	int endState = _table[start_state][ch];

	auto increment = [&]() {
		tokenBuffer += ch;
		start_state = endState;
		ch = _buffer[++tokenBufferPos];
		endState = _table[start_state][ch];
	};

	while (_buffer[tokenBufferPos] != '\0' && endState != -1)
	{
		if (!SMLibrary::is_success(_table, endState))
		{
			increment();

			if (!(ch != '\0' &&
				  endState != -1 &&
				  SMLibrary::is_success(_table, endState)))
				return true;

			while (ch != '\0' &&
				   endState != -1 &&
				   SMLibrary::is_success(_table, endState))
				increment();

			if (endState == -1 || ch == '\0')
			{
				token += tokenBuffer;
				_pos = tokenBufferPos++;

				return true;
			}
		}
		else
		{
			token += ch;
			++_pos;
			start_state = endState;
		}

		ch = _buffer[_pos];
		endState = _table[start_state][ch];
		tokenBufferPos = _pos;
	}

	return true;
}

STokenizer &operator>>(STokenizer &s, SMLibrary::Token &t)
{
	std::string tokenStr;
	int state = 0;

	s.get_token(state, tokenStr);

	t = SMLibrary::Token(tokenStr, state);

	return s;
}
