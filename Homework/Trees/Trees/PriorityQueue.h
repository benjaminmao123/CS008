/*
 * Author: Benjamin Mao
 * Project: Priority Queue
 * Purpose: The priority queue.
 *
 * Notes: None.
 */

#pragma once

#include <iostream>

#include "Heap.h"

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

	friend bool operator==(const info<T>& lhs, const info<T>& rhs)
	{
		return lhs.item == rhs.item;
	}
};

template <typename T>
class PQueue
{
public:
	bool insert(const T& value, int p);
	T Pop();

	bool is_empty() const;
	int size() const;
	void print_tree(std::ostream& outs = std::cout) const;
	void clear();

	template <typename U>
	friend std::ostream& operator<<(std::ostream& outs, const PQueue<U>& print_me);

private:
	Heap<info<T>> heap;
};

template<typename T>
inline bool PQueue<T>::insert(const T& value, int p)
{
	info<T> res;
	bool exists = heap.search(info<T>(value, p), res);

	if (!exists)
		heap.insert(info<T>(value, p));
	else
		res.priority += 1;

	return true;
}

template<typename T>
inline T PQueue<T>::Pop()
{
	return heap.pop().item;
}

template<typename T>
inline bool PQueue<T>::is_empty() const
{
	return heap.is_empty();
}

template<typename T>
inline int PQueue<T>::size() const
{
	return heap.size();
}

template<typename T>
inline void PQueue<T>::print_tree(std::ostream& outs) const
{
	outs << heap;
}

template<typename T>
inline void PQueue<T>::clear()
{
	heap.clear();
}

template<typename U>
inline std::ostream& operator<<(std::ostream& outs, const PQueue<U>& print_me)
{
	print_me.print_tree(outs);

	return outs;
}
