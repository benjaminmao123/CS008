/*
 * Author: Benjamin Mao
 * Project: Deque
 * Purpose: Double ended queue
 *
 * Notes: None.
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <cassert>

#include "IteratedList.h"

template <typename T>
class deque
{
public:
	class Iterator
	{
	public:
		Iterator() { }
		Iterator(const typename List<T>::Iterator& it) : listIt(it) { }

		T& operator*()
		{
			return *listIt;
		}

		const T& operator*() const
		{
			return *listIt;
		}

		T* operator->()
		{
			return listIt.operator->();
		}

		const T* operator->() const
		{
			return listIt.operator->();
		}

		operator bool() const
		{
			return listIt;
		}

		//true if left != right
		bool operator!=(const Iterator& rhs) const
		{
			return listIt != rhs.listIt;
		}

		//true if left == right
		bool operator==(const Iterator& rhs) const
		{
			return listIt == rhs.listIt;
		}

		//member operator: ++it; or ++it = new_value
		Iterator& operator++()
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

	deque();
	deque(const deque& other);
	deque& operator=(const deque& rhs);

	void push_back(const T& item);
	void push_front(const T& item);
	T pop_front();
	T pop_back();

	Iterator begin() const;
	Iterator end() const;

	const T& front() const;
	T& front();
	const T& back() const;
	T& back();
	size_t size() const;
	bool empty() const;

	void swap(deque& other) noexcept;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const deque<U>& q);
	bool operator==(const deque& rhs) const;
	bool operator!=(const deque& rhs) const;

private:
	void swap(deque& s1, deque& s2) noexcept;

	List<T> list;
	typename List<T>::Iterator tail;
	size_t sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template<typename T>
inline deque<T>::deque()
	: sz(0)
{

}

/*
	@summary: Copy constructor.

	@param <const queue &other>: queue object to copy.
*/
template<typename T>
inline deque<T>::deque(const deque& other)
	: sz(other.sz), list(other.list)
{

}

/*
	@summary: Copy assignment operator.

	@param <const queue &rhs>: queue object to copy.
*/
template<typename T>
inline deque<T>& deque<T>::operator=(const deque& rhs)
{
	deque temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Adds an item to the back of the queue and increments size.

	@param <const reference item>: Item to add to the queue.
*/
template<typename T>
inline void deque<T>::push_back(const T& item)
{
	tail = list.InsertAfter(item, tail);
	++sz;
}

/*
	@summary: Adds an item to the front of the queue and increments size.

	@param <const reference item>: Item to add to the queue.
*/
template<typename T>
inline void deque<T>::push_front(const T& item)
{
	list.InsertHead(item);
	++sz;
}

/*
	@summary: Removes an item from the top of the queue and decrements size.
*/
template<typename T>
inline T deque<T>::pop_front()
{
	if (empty())
		throw std::out_of_range("Pop called on empty stack.");

	T item = *list.begin();

	if (sz == 1) tail = typename List<T>::Iterator(nullptr);

	list.Delete(list.begin());
	--sz;

	return item;
}


/*
	@summary: Removes an item from the back of the queue and decrements size.
*/
template<typename T>
inline T deque<T>::pop_back()
{
	if (empty())
		throw std::out_of_range("Pop called on empty stack.");

	T item = *tail;

	auto temp = tail--;
	list.Delete(temp);

	if (sz == 1) tail = typename List<T>::Iterator(nullptr);

	--sz;

	return item;
}

template<typename T>
inline typename deque<T>::Iterator deque<T>::begin() const
{
	return Iterator(list.begin());
}

template<typename T>
inline typename deque<T>::Iterator deque<T>::end() const
{
	return Iterator(list.end());
}

/*
	@summary: Returns the item at the top of the queue.

	@return <const reference>: Reference to the item at the top of the queue.
*/
template<typename T>
inline const T& deque<T>::front() const
{
	if (empty())
		throw std::out_of_range("Front called on empty queue.");

	return *list.begin();
}

/*
	@summary: Returns the item at the front of the queue.

	@return <const reference>: Reference to the item at the top of the queue.
*/
template<typename T>
inline T& deque<T>::front()
{
	if (empty())
		throw std::out_of_range("Front called on empty queue.");

	return *list.begin();
}

template<typename T>
inline const T& deque<T>::back() const
{
	if (empty())
		throw std::out_of_range("Back called on empty queue.");

	return *tail;
}

template<typename T>
inline T& deque<T>::back()
{
	if (empty())
		throw std::out_of_range("Back called on empty queue.");

	return *tail;
}

/*
	@summary: Returns the size of the queue.

	@return <size_type>: The size of the queue.
*/
template<typename T>
inline size_t deque<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether queue is empty.

	@return <bool>: If queue empty return true, else false.
*/
template<typename T>
inline bool deque<T>::empty() const
{
	return !tail;
}

/*
	@summary: Swaps contents of this queue with another queue.

	@param <queue &other>: queue to swap with.
*/
template<typename T>
inline void deque<T>::swap(deque& other) noexcept
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
inline bool deque<T>::operator==(const deque& rhs) const
{
	if (sz == rhs.sz)
		return list == rhs.list;

	return false;
}

/*
	@summary: Inequality to check if two stacks are not equal.
		Checks if size is not equal, then if contents are not equal.

	@param <const queue &rhs>: queue to compare to.

	@return <bool>: True if not equal, else false.
*/
template<typename T>
inline bool deque<T>::operator!=(const deque& rhs) const
{
	if (sz != rhs.sz)
		return true;

	return list != rhs.list;
}

/*
	@summary: Swaps contents of two stacks.

	@param <queue &s1>: first queue to swap.
	@param <queue &s2>: second queue to swap.
*/
template<typename T>
inline void deque<T>::swap(deque& s1, deque& s2) noexcept
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
inline std::ostream& operator<<(std::ostream& os, const deque<U>& q)
{
	if (!q.empty())
	{
		for (auto i : q)
			os << "[" << i << "]" << "->";
	}

	os << "|||";

	return os;
}
