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
#include "PriorityQueue.h"
#include "Vector.h"
#include "AVL.h"

template <typename T>
struct info
{
	T item;
	int priority;
	int order;

	info() :
		priority(0), order(0)
	{

	}

	info(const T& i, int p, int order) :
		item(i),
		priority(p),
		order(order)
	{

	}

	friend std::ostream& operator<<(std::ostream& outs, const info<T>& print_me)
	{
		outs << "(" << print_me.item << ", " << print_me.priority << ", " << print_me.order << ")";

		return outs;
	}

	friend bool operator<(const info<T>& lhs, const info<T>& rhs)
	{
		if (lhs.priority == rhs.priority)
			return lhs.order > rhs.order;

		return lhs.priority < rhs.priority;
	}

	friend bool operator>(const info<T>& lhs, const info<T>& rhs)
	{
		if (lhs.priority == rhs.priority)
			return lhs.order < rhs.order;

		return lhs.priority > rhs.priority;
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

auto PrintWordFrequencies = [](PQueue<info<std::string>>& pq, unsigned int n)
{
	std::cout << "Top " << n << " words: " << std::endl;

	for (unsigned int i = 0; i < n && !pq.is_empty(); ++i)
		std::cout << i + 1 << ". " << pq.pop() << std::endl;

	std::cout << "\nLast " << n << " words: " << std::endl;

	while (pq.size() > 100)
		pq.pop();

	for (unsigned int i = 0; i < n && !pq.is_empty(); ++i)
		std::cout << i + 1 << ". " << pq.pop() << std::endl;
};

int main()
{
	FTokenizer ftk("code/solitude.txt");
	PQueue<info<std::string>> pq;
	AVL<word<std::string>> avl;
	int count = 0;

	while (ftk.more())
	{
		Token t;
		ftk >> t;

		if (t.type_string() == "ALPHA")
		{
			tree_node<word<std::string>>* fptr;
			word<std::string> token(t.token_str(), 1);

			if (!avl.search(token, fptr))
				avl.insert(token);
			else
				++fptr->_item;
		}
	}

	int order = 0;

	for (const auto& i : avl)
		pq.insert(info<std::string>(i.item, i.freq, order++));

	std::cout << std::endl;

	PrintWordFrequencies(pq, 100); 

	return 0;
}
