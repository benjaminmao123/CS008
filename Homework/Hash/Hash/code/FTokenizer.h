#pragma once

#include <iostream>
#include <fstream>

#include "STokenizer.h"
#include "FTConstants.h"

class FTokenizer
{
public:
    FTokenizer(const char *fname);

    SMLibrary::Token next_token();
    bool more(); //returns the current value of _more

    friend FTokenizer &operator>>(FTokenizer &f, SMLibrary::Token &t);

private:
    bool get_new_block(); //gets the new block from the file

    std::ifstream _f; //file being tokenized
    STokenizer _stk;  //The STokenizer object to tokenize current block
};