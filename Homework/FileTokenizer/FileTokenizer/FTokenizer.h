#pragma once

#include "STokenizer.h"
#include "Token.h"

#include <iostream>
#include <fstream>

#define MAX_BLOCK MAX_BUFFER

class FTokenizer
{
public:
    FTokenizer(const char* fname);

    Token next_token();
    bool more();            //returns the current value of _more
    
    friend FTokenizer& operator>>(FTokenizer& f, Token& t);

private:
    bool get_new_block();   //gets the new block from the file

    std::ifstream _f;       //file being tokenized
    STokenizer _stk;        //The STokenizer object to tokenize current block
    size_t pos;
};