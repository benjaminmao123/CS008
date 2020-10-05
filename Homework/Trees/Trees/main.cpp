/*
 * Author: Benjamin Mao
 * Project: Trees
 * Purpose: Driver
 *
 * Notes: None.
 */

#include "FTokenizer.h"
#include "PriorityQueue.h"
#include "Vector.h"

#include <iostream>
#include <string>
#include <iomanip>

int main()
{
	FTokenizer ftk("solitude.txt");
	PQueue<std::string> pq;
	int count = 0;

	auto PrintWordFrequencies = [&](unsigned int n)
	{
		Vector<std::string> wordList;

		for (int i = 0; i < n; ++i)
			wordList.push_back(pq.Pop());

		for (unsigned int i = 0; i < n && i < wordList.size(); ++i)
			std::cout << i + 1 << ". " << wordList[i] << std::endl;
	};

	while (ftk.more())
	{
		Token t;
		ftk >> t;

		if (t.type_string() == "ALPHA")
		{
			std::cout << std::setw(10) << count++
					  << std::setw(3) << std::left << ":" << std::setw(25) << std::left << t.token_str()
				      << t.type_string() << std::endl;

			pq.insert(t.token_str(), 1);
		}
	}

	std::cout << std::endl;
	std::cout << "Top 20 words: " << std::endl;

	PrintWordFrequencies(20);

	return 0;
}
