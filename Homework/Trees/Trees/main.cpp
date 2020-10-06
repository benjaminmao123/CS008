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
		outs << print_me.item;

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

int main()
{
	FTokenizer ftk("solitude.txt");
	PQueue<info<std::string>> pq;
	int count = 0;

	auto PrintWordFrequencies = [&](unsigned int n)
	{
		Vector<info<std::string>> wordList;

		for (unsigned int i = 0; i < n; ++i)
			wordList.push_back(pq.pop());

		for (unsigned int i = 0; i < n && i < wordList.size(); ++i)
			std::cout << i + 1 << ". " << "(" << wordList[i].item << ", " 
					  << wordList[i].priority << ")" << std::endl;
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

			pq.insert(info<std::string>(t.token_str(), 1));
		}
	}

	std::cout << std::endl;
	std::cout << "Top 100 words: " << std::endl;

	PrintWordFrequencies(100);

	return 0;
}
