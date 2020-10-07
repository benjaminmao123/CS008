/*
 * Author: Benjamin Mao
 * Project: Queue
 * Purpose: Implementation a FIFO container called
 *		a stack.
 *
 * Notes: None.
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <cassert>

#include "IteratedList.h"

template <typename T>
class queue
{
public:
	class Iterator
	{
	public:
		Iterator() { }
		Iterator(const typename List<T>::Iterator &it) : listIt(it) { }

		T &operator*()
		{
			return *listIt;
		}

		const T &operator*() const
		{
			return *listIt;
		}

		T *operator->()
		{
			return listIt.operator->();
		}

		const T *operator->() const
		{
			return listIt.operator->();
		}

		operator bool() const
		{
			return listIt;
		}

		//true if left != right
		bool operator!=(const Iterator &rhs) const
		{
			return listIt != rhs.listIt;
		}

		//true if left == right
		bool operator==(const Iterator &rhs) const
		{
			return listIt == rhs.listIt;
		}

		//member operator: ++it; or ++it = new_value
		Iterator &operator++()
		{
			++listIt;

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp(listIt);
			operator++();

			return temp;
		}

	private:
		typename List<T>::Iterator listIt;
	};

	queue();
	queue(const queue &other);
	queue &operator=(const queue &rhs);

	void push(const T &item);
	T pop();

	Iterator begin() const;
	Iterator end() const;

	const T &front() const;
	T &front();
	size_t size() const;
	bool empty() const;
	
	void swap(queue &other) noexcept;

	template <typename U>
	friend std::ostream &operator<<(std::ostream &os, const queue<U> &q);
	bool operator==(const queue &rhs) const;
	bool operator!=(const queue &rhs) const;

private:
	void swap(queue &s1, queue &s2) noexcept;

	List<T> list;
	typename List<T>::Iterator tail;
	size_t sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template<typename T>
inline queue<T>::queue()
	: sz(0)
{

}

/*
	@summary: Copy constructor.

	@param <const queue &other>: queue object to copy.
*/
template<typename T>
inline queue<T>::queue(const queue &other)
	: sz(other.sz), list(other.list)
{
	
}

/*
	@summary: Copy assignment operator.

	@param <const queue &rhs>: queue object to copy.
*/
template<typename T>
inline queue<T> &queue<T>::operator=(const queue &rhs)
{
	queue temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Adds an item to the back of the queue and increments size.

	@param <const reference item>: Item to add to the queue.
*/
template<typename T>
inline void queue<T>::push(const T &item)
{
	tail = list.InsertAfter(item, tail);
	++sz;
}

/*
	@summary: Removes an item from the top of the queue and decrements size.
*/
template<typename T>
inline T queue<T>::pop()
{
	if (empty())
	{
		throw std::out_of_range("Pop called on empty stack.");
	}

	T item = *list.begin();

	if (sz == 1) tail = typename List<T>::Iterator(nullptr);

	list.Delete(list.begin());
	--sz;

	return item;
}

template<typename T>
inline typename queue<T>::Iterator queue<T>::begin() const
{
	return Iterator(list.begin());
}

template<typename T>
inline typename queue<T>::Iterator queue<T>::end() const
{
	return Iterator(list.end());
}

/*
	@summary: Returns the item at the top of the queue.

	@return <const reference>: Reference to the item at the top of the queue.
*/
template<typename T>
inline const T &queue<T>::front() const
{
	if (empty())
	{
		throw std::out_of_range("Front called on empty queue.");
	}

	return *list.begin();
}

/*
	@summary: Returns the item at the front of the queue.

	@return <const reference>: Reference to the item at the top of the queue.
*/
template<typename T>
inline T &queue<T>::front()
{
	if (empty())
	{
		throw std::out_of_range("Front called on empty queue.");
	}

	return *list.begin();
}

/*
	@summary: Returns the size of the queue.

	@return <size_type>: The size of the queue.
*/
template<typename T>
inline size_t queue<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether queue is empty.

	@return <bool>: If queue empty return true, else false.
*/
template<typename T>
inline bool queue<T>::empty() const
{
	return sz == 0;
}

/*
	@summary: Swaps contents of this queue with another queue.

	@param <queue &other>: queue to swap with.
*/
template<typename T>
inline void queue<T>::swap(queue &other) noexcept
{
	std::swap(sz, other.sz);
	std::swap(list, other.list);
	std::swap(tail, other.tail);
}

/*
	@summary: Equality to check if two stacks are equal.
		Checks if size is equal, then if contents are equal.

	@param <const queue &rhs>: queue to compare to.

	@return <bool>: True if equal, else false.
*/
template<typename T>
inline bool queue<T>::operator==(const queue &rhs) const
{
	if (sz == rhs.sz)
	{
		return list == rhs.list;
	}

	return false;
}

/*
	@summary: Inequality to check if two stacks are not equal.
		Checks if size is not equal, then if contents are not equal.

	@param <const queue &rhs>: queue to compare to.

	@return <bool>: True if not equal, else false.
*/
template<typename T>
inline bool queue<T>::operator!=(const queue &rhs) const
{
	if (sz != rhs.sz)
	{
		return true;
	}

	return list != rhs.list;
}

/*
	@summary: Swaps contents of two stacks.

	@param <queue &s1>: first queue to swap.
	@param <queue &s2>: second queue to swap.
*/
template<typename T>
inline void queue<T>::swap(queue &s1, queue &s2) noexcept
{
	std::swap(s1.sz, s2.sz);
	std::swap(s1.list, s2.list);
	std::swap(s1.tail, s2.tail);
}

/*
	@summary: Overloaded stream insertion operator to print contents of queue.

	@param <std::ostream &os>: The ostream object.
	@param <const queue<U> &q>: queue to print contents of.

	@return <std::ostream &>: Reference to the ostream object.
*/
template<typename U>
inline std::ostream &operator<<(std::ostream &os, const queue<U> &q)
{
	if (!q.empty())
	{
		for (auto i : q)
		{
			os << "[" << i << "]" << "->";
		}
	}

	os << "|||";

	return os;
}
