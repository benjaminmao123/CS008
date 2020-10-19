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
class PQueue
{
public:
	bool insert(const T& value);
	T pop();
	const T& front() const;

	bool is_empty() const;
	int size() const;
	void print_tree(std::ostream& outs = std::cout) const;
	void clear();

	template <typename U>
	friend std::ostream& operator<<(std::ostream& outs, const PQueue<U>& print_me);

private:
	Heap<T> heap;
};

template<typename T>
inline bool PQueue<T>::insert(const T& value)
{
	heap.insert(value);

	return true;
}

template<typename T>
inline T PQueue<T>::pop()
{
	return heap.pop();
}

template<typename T>
inline const T& PQueue<T>::front() const
{
	return heap.front();
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
