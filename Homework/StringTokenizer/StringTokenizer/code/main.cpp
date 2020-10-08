/*
 * Author: Benjamin Mao
 * Project: STokenizer
 * Purpose: Driver for STokenizer
 *
 * Notes: None.
 */

#include <iostream>
#include <iomanip>

#include "STokenizer.h"

int main()
{
    std::string input = "it was the night of october 17th. pi was still 3.14.";
    STokenizer stk(input.c_str());
    Token t;

    while (true)
    {
        while (stk.more())
        {
            stk >> t;

            std::cout << std::setw(10) << t.type_string()
                << std::setw(10) << t << std::endl;

            t = Token();
        }

        std::cout << std::endl;
        std::getline(std::cin, input);
        stk.set_string(input.c_str());
    }

    return 0;
}
