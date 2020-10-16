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

template <typename T>
struct word
{
	T item;
	int freq;

	word() :
		freq(0)
	{

	}

	word(const T& i, int f) :
		item(i),
		freq(f)
	{

	}

	friend std::ostream& operator<<(std::ostream& outs, const word<T>& print_me)
	{
		outs << "(" << print_me.item << ", " << print_me.freq << print_me.order << ")";

		return outs;
	}

	friend bool operator<(const word<T>& lhs, const word<T>& rhs)
	{
		return lhs.item < rhs.item;
	}

	friend bool operator>(const word<T>& lhs, const word<T>& rhs)
	{
		return lhs.item > rhs.item;
	}

	friend bool operator>=(const word<T>& lhs, const word<T>& rhs)
	{
		return lhs.item >= rhs.item;
	}

	friend bool operator<=(const word<T>& lhs, const word<T>& rhs)
	{
		return lhs.item <= rhs.item;
	}

	word<T>& operator++()
	{
		++freq;

		return *this;
	}

	friend bool operator==(const word<T>& lhs, const word<T>& rhs)
	{
		return lhs.item == rhs.item;
	}
};

int main()
{
	FTokenizer ftk("code/solitude2.txt");
	chained_hash<std::string, int> ht;

	while (ftk.more())
	{
		SMLibrary::Token t;
		ftk >> t;

		if (t.type_string() == "ALPHA")
			ht.insert(t.token_str());
	}



	return 0;
}
