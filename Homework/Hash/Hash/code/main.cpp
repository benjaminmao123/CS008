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

template <typename K, typename V>
bool operator<(const HTLibrary::record<K, V>& first, const HTLibrary::record<K, V>& second);
template <typename T>
void quickSort(T& arr, int low, int high);
void printWordFrequencies(chained_hash<std::string, int>& ht, int n);

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
			HTLibrary::record<std::string, int>* res = nullptr;

			if (!ht.find(t.token_str(), res))
				ht.insert(t.token_str(), 1);
			else
				++res->_value;
		}
	}

	printWordFrequencies(ht, 100);

	return 0;
}

template<typename K, typename V>
bool operator<(const HTLibrary::record<K, V>& first, const HTLibrary::record<K, V>& second)
{
	if (first._value == second._value)
		return first._key < second._key;

	return first._value > second._value;
}

template <typename T>
void quickSort(T& arr, int low, int high)
{
	auto partition = [](T& arr, int low, int high)
	{
		auto pivot = arr[high];
		int i = (low - 1);

		for (int j = low; j <= high - 1; ++j)
		{
			if (arr[j] < pivot)
				std::swap(arr[++i], arr[j]);
		}

		std::swap(arr[i + 1], arr[high]);

		return (i + 1);
	};

	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void printWordFrequencies(chained_hash<std::string, int>& ht, int n)
{
	Vector<HTLibrary::record<std::string, int>> vec;

	for (const auto& i : ht)
		vec.push_back(i);

	quickSort(vec, 0, vec.size() - 1);

	std::cout << "Top " << n << " words: " << std::endl;

	for (int i = 0; i < n && i < vec.size(); ++i)
		std::cout << i + 1 << ". " << vec[i] << std::endl;

	std::cout << "\nLast " << n << " words: " << std::endl;

	for (int i = 0; i < n && i < vec.size(); ++i)
		std::cout << i + 1 << ". " << vec.pop_back() << std::endl;
}
