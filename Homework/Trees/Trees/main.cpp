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

#include "FTokenizer.h"
#include "PriorityQueue.h"
#include "Vector.h"
#include "AVL.h"

template <typename T>
struct info
{
	T item;
	int priority;

	info() :
		priority(0)
	{

	}

	info(const T& i, int p) :
		item(i),
		priority(p)
	{

	}

	friend std::ostream& operator<<(std::ostream& outs, const info<T>& print_me)
	{
		outs << "(" << print_me.item << ", " << print_me.priority << ")";

		return outs;
	}

	friend bool operator<(const info<T>& lhs, const info<T>& rhs)
	{
		return lhs.priority < rhs.priority;
	}

	friend bool operator>(const info<T>& lhs, const info<T>& rhs)
	{
		return lhs.priority > rhs.priority;
	}

	friend bool operator>=(const info<T>& lhs, const info<T>& rhs)
	{
		return lhs.priority >= rhs.priority;
	}

	friend bool operator<=(const info<T>& lhs, const info<T>& rhs)
	{
		return lhs.priority >= rhs.priority;
	}

	info<T>& operator++()
	{
		++priority;

		return *this;
	}

	friend bool operator==(const info<T>& lhs, const info<T>& rhs)
	{
		return lhs.item == rhs.item;
	}
};

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
		outs << "(" << print_me.item << ", " << print_me.freq << ")";

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
		return lhs.item >= rhs.item;
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

auto PrintWordFrequencies = [&](PQueue<info<std::string>>& pq, unsigned int n)
{
	std::cout << "Top " << n << " words: " << std::endl;

	for (unsigned int i = 0; i < n; ++i)
		std::cout << i + 1 << ". " << pq.pop() << std::endl;
};

int main()
{
	FTokenizer ftk("solitude.txt");
	PQueue<info<std::string>> pq;
	AVL<word<std::string>> avl;
	int count = 0;

	while (ftk.more())
	{
		Token t;
		ftk >> t;

		if (t.type_string() == "ALPHA")
		{
			std::cout << std::setw(10) << count++
					  << std::setw(3) << std::left << ":" << std::setw(25) << std::left << t.token_str()
				      << t.type_string() << std::endl;

			avl.insert(word<std::string>(t.token_str(), 1));
		}
	}

	for (const auto& i : avl)
		pq.insert(info<std::string>(i.item, i.freq));

	std::cout << std::endl;

	PrintWordFrequencies(pq, 100);

	return 0;
}
