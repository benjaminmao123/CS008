/*
 * Author: Benjamin Mao
 * Project: Stack
 * Purpose: Implementation a LIFO container called
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
class Stack
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

	Stack();
	Stack(const Stack &other);
	Stack &operator=(const Stack &rhs);

	void push(const T &item);
	T pop();

	Iterator begin() const;
	Iterator end() const;

	const T &top() const;
	T &top();
	size_t size() const;
	bool empty() const;
	
	void swap(Stack &other) noexcept;

	template <typename U>
	friend std::ostream &operator<<(std::ostream &os, const Stack<U> &s);
	bool operator==(const Stack &rhs) const;
	bool operator!=(const Stack &rhs) const;

private:
	void swap(Stack &s1, Stack &s2);

	List<T> list;
	size_t sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template<typename T>
inline Stack<T>::Stack()
	: sz(0)
{

}

/*
	@summary: Copy constructor.

	@param <const stack &other>: stack object to copy.
*/
template<typename T>
inline Stack<T>::Stack(const Stack &other)
	: sz(other.sz)
{

}

/*
	@summary: Copy assignment operator.

	@param <const stack &rhs>: stack object to copy.
*/
template<typename T>
inline Stack<T> &Stack<T>::operator=(const Stack &rhs)
{
	Stack temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Adds an item to the front of the stack and increments size.

	@param <const value_type &item>: Item to add to the stack.
*/
template<typename T>
inline void Stack<T>::push(const T &item)
{
	list.InsertHead(item);
	++sz;
}

/*
	@summary: Removes an item from the top of the stack and decrements size.
*/
template<typename T>
inline T Stack<T>::pop()
{
	if (empty())
		throw std::out_of_range("Pop called on empty stack.");

	T item = *list.begin();

	list.Delete(list.begin());
	--sz;

	return item;
}

template<typename T>
inline typename Stack<T>::Iterator Stack<T>::begin() const
{
	return Iterator(list.begin());
}

template<typename T>
inline typename Stack<T>::Iterator Stack<T>::end() const
{
	return Iterator(list.end());
}

/*
	@summary: Returns the item at the top of the stack.

	@return <const reference>: Reference to the item at the top of the stack.
*/
template<typename T>
inline const T &Stack<T>::top() const
{
	if (empty())
		throw std::out_of_range("Top called on empty stack.");

	return *list.begin();
}

/*
	@summary: Returns the item at the top of the stack.

	@return <const reference>: Reference to the item at the top of the stack.
*/
template<typename T>
inline T &Stack<T>::top()
{
	if (empty())
		throw std::out_of_range("Top called on empty stack.");

	return *list.begin();
}

/*
	@summary: Returns the size of the stack.

	@return <size_type>: The size of the stack.
*/
template<typename T>
inline size_t Stack<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether stack is empty.

	@return <bool>: If stack empty return true, else false.
*/
template<typename T>
inline bool Stack<T>::empty() const
{
	return sz == 0 || !list.begin();
}

/*
	@summary: Swaps contents of this stack with another stack.

	@param <stack &other>: stack to swap with.
*/
template<typename T>
inline void Stack<T>::swap(Stack &other) noexcept
{
	std::swap(sz, other.sz);
	std::swap(list, other.list);
}

/*
	@summary: Equality to check if two stacks are equal.
		Checks if size is equal, then if contents are equal.

	@param <const stack &rhs>: stack to compare to.

	@return <bool>: True if equal, else false.
*/
template<typename T>
inline bool Stack<T>::operator==(const Stack &rhs) const
{
	if (sz == rhs.sz)
		return list == rhs.list;

	return false;
}

/*
	@summary: Inequality to check if two stacks are not equal.
		Checks if size is not equal, then if contents are not equal.

	@param <const stack &rhs>: stack to compare to.

	@return <bool>: True if not equal, else false.
*/
template<typename T>
inline bool Stack<T>::operator!=(const Stack &rhs) const
{
	if (sz != rhs.sz)
		return true;

	return list != rhs.list;
}

/*
	@summary: Swaps contents of two stacks.

	@param <stack &s1>: first stack to swap.
	@param <stack &s2>: second stack to swap.
*/
template<typename T>
inline void Stack<T>::swap(Stack &s1, Stack &s2)
{
	std::swap(s1.sz, s2.sz);
	std::swap(s1.list, s2.list);
}

/*
	@summary: Overloaded stream insertion operator to print contents of stack.

	@param <std::ostream &os>: The ostream object.
	@param <const stack<U> &s>: stack to print contents of.

	@return <std::ostream &>: Reference to the ostream object.
*/
template<typename U>
inline std::ostream &operator<<(std::ostream &os, const Stack<U> &s)
{
	if (!s.empty())
	{
		for (auto i : s)
			os << "[" << i << "]" << "->";
	}

	os << "|||";

	return os;
}
