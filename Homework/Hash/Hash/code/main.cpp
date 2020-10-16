/*
 * Author: Benjamin Mao
 * Project: Trees
 * Purpose: Driver
 *
 * Notes: None.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

#include "FTokenizer.h"
#include "ChainedHash.h"

int main()
{
	FTokenizer ftk("code/solitude2.txt");
	chained_hash<std::string, int> ht;

	while (ftk.more())
	{
		SMLibrary::Token t;
		ftk >> t;

		if (t.type_string() == "ALPHA")
		{


			ht.insert(t.token_str(), 1);
		}
	}

	

	return 0;
}
