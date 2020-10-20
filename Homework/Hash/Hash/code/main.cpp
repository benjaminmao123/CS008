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
#include "PriorityQueue.h"

template <typename K, typename V>
bool operator>(const HTLibrary::record<K, V>& first, const HTLibrary::record<K, V>& second);
void printWordFrequencies(PQueue<HTLibrary::record<std::string, int>>& pq, int n);

int main()
{
	FTokenizer ftk("code/solitude.txt");
	chained_hash<std::string, int> ht;

	while (ftk.more())
	{
		SMLibrary::Token t;
		ftk >> t;

		if (t.type_string() == "ALPHA")
		{
			auto it = ht.find(t.token_str());

			if (!it)
				ht.insert(t.token_str(), 1);
			else
				++it->_value;
		}
	}

	PQueue<HTLibrary::record<std::string, int>> pq;

	for (const auto& i : ht)
		pq.insert(i);

	printWordFrequencies(pq, 100);

	return 0;
}

template<typename K, typename V>
bool operator>(const HTLibrary::record<K, V>& first, const HTLibrary::record<K, V>& second)
{
	if (first._value == second._value)
		return first._key < second._key;

	return first._value > second._value;
}

void printWordFrequencies(PQueue<HTLibrary::record<std::string, int>>& pq, int n)
{
	auto NumDigits = [](int i)
	{
		return i > 0 ? (int)log10((double)i) + 1 : 1;
	};

	Vector<HTLibrary::record<std::string, int>> vec;

	while (!pq.is_empty())
		vec.push_back(pq.pop());

	std::cout << "Top " << n << " words: " << std::endl;

	for (int i = 0; i < n && i < vec.size(); ++i)
	{
		std::cout << std::setfill('0') << std::setw(NumDigits(n)) << i + 1;
		std::cout << std::setfill(' ') << ". " << std::setw(10) << std::right << vec[i]._key;
		std::cout << std::setw(10) << std::right << vec[i]._value << std::endl;
	}

	std::cout << "\nLast " << n << " words: " << std::endl;

	int i;

	for (i = 0; i < vec.size() - n; ++i);

	for (int j = 0; i < vec.size(); ++i, ++j)
	{
		std::cout << std::setfill('0') << std::setw(NumDigits(n)) << j + 1;
		std::cout << std::setfill(' ') << ". " << std::setw(15) << std::right << vec[i]._key;
		std::cout << std::setw(10) << std::right << vec[i]._value << std::endl;
	}
}
