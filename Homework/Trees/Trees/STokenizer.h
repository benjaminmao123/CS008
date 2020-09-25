#pragma once

#include "Token.h"
#include "SMConstants.h"

#include <string>

#define MAX_BUFFER 2048

class STokenizer
{
public:
    STokenizer();
    STokenizer(const char str[]);

    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator>>(STokenizer& s, Token& t);

    //set a new string as the input string
    void set_string(const char str[]);

private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int& start_state, std::string& token);
    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    size_t _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};