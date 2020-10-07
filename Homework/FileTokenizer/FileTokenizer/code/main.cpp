/*
 * Author: Benjamin Mao
 * Project: STokenizer
 * Purpose: Driver for FTokenizer
 *
 * Notes: None.
 */

#include "FTokenizer.h"

#include <iostream>
#include <iomanip>

void test_f_tokenize_simple();

int main()
{
    test_f_tokenize_simple();

	return 0;
}

void test_f_tokenize_simple() 
{
    Token t;

    FTokenizer ftk("solitude.txt");
    ftk >> t;

    int token_count = 0;

    while (ftk.more()) 
    {
        if (t.type_string() == "ALPHA") 
        {
            token_count++;

            std::cout << std::setw(10) << token_count
                << std::setw(3) << std::left << ":" << std::setw(25) << std::left << t.token_str()
                << t.type_string() << std::endl;
        }

        ftk >> t;
    }

    std::cout << "Tokens Found: " << token_count << std::endl;
    std::cout << "==========" << std::endl;
}