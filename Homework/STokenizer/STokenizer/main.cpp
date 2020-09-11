/*
 * Author: Benjamin Mao
 * Project: STokenizer
 * Purpose: Driver for STokenizer
 *
 * Notes: None.
 */

#include "STokenizer.h"

#include <iostream>
#include <iomanip>

int main()
{
    char s[] = "it was the night of october 17th. pi was still 3.14.";

    STokenizer stk(s);
    Token t;

    while (stk.more())
    {
        stk >> t;

        std::cout << std::setw(10) << t.type_string()
                  << std::setw(10) << t << std::endl;

        t = Token();
    }

    return 0;
}
