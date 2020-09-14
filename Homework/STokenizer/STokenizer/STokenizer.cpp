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
		{
			if (!j) 
				_table[i][j] = 0;
			else 
				_table[i][j] = -1;
		}
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
	mark_table(_table, DIGIT, '.', '.', DECIMAL);
	
	//init sub_digit
	mark_table(_table, DECIMAL, '0', '9', DECIMAL_SUCCESS);
	mark_table(_table, DECIMAL_SUCCESS, '0', '9', DECIMAL_SUCCESS);

	//init punct
	for (int i = 0; i < strlen(punc); ++i)
		mark_table(_table, PUNCT, punc[i], punc[i], PUNCT);

	//init space
	mark_table(_table, SPACE, ' ', ' ', SPACE);

	mark_success(0);
	mark_success(1);
	mark_success(2);
	mark_success(3);
	mark_success(4);
	mark_success(6);
	mark_success(7);
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

void STokenizer::mark_success(int state)
{
	_table[state][0] = 1;
}

int STokenizer::get_success(int state) const
{
	return _table[state][0];
}

bool STokenizer::get_token(int& start_state, std::string& token)
{
	if (done())
		return false;

	std::string temp;
	char c = _buffer[_pos];
	int end_state = _table[start_state][c];
	int tempPos = _pos;

	auto increment = [&]() {
		temp += c;
		++tempPos;
		start_state = end_state;
		c = _buffer[tempPos];
		end_state = _table[start_state][c];
	};

	while (_buffer[tempPos] != '\0' && end_state != -1)
	{
		if (!get_success(end_state))
		{
			increment();

			bool success = c != '\0' && 
				end_state != -1 && 
				get_success(end_state);

			if (!success)
				return true;

			while (success)
			{
				increment();

				success = c != '\0' &&
					end_state != -1 &&
					get_success(end_state);
			}

			if (end_state == -1 || c == '\0')
			{
				token += temp;
				_pos = tempPos++;

				return true;
			}
		}
		else
		{
			token += c;
			++_pos;
			start_state = end_state;
		}

		c = _buffer[_pos];
		end_state = _table[start_state][c];
		tempPos = _pos;
	}

	return true;
}

STokenizer& operator>>(STokenizer& s, Token& t)
{
	std::string tokenStr;
	int state = 0;

	s.get_token(state, tokenStr);

	t = Token(tokenStr, state);

	return s;
}
