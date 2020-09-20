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

#include "LinkedListLibrary.h"

template <typename T>
class stack
{
public:
	class Iterator
	{
	public:
		Iterator() { }
		Iterator(node<T> *ptr) : ptr(ptr) { };

		const T &operator*() const
		{
			return ptr->_item;
		}

		T &operator*()
		{
			return ptr->_item;
		}

		const T *operator->() const
		{
			return &ptr->_item;
		}

		T *operator->()
		{
			return &ptr->_item;
		}

		//casting operator: true if _ptr not NULL
		operator bool() const
		{
			return ptr != nullptr;
		}

		//true if left != right
		bool operator!=(const Iterator &rhs) const
		{
			return ptr != rhs.ptr;
		}

		//true if left == right
		bool operator==(const Iterator &rhs) const
		{
			return ptr == rhs.ptr;
		}

		//member operator: ++it; or ++it = new_value
		Iterator &operator++()
		{
			ptr = ptr->next;

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp(ptr);
			operator++();

			return temp;
		}

	private:
		node<T> *ptr;
	};

	stack();
	stack(const stack &other);
	stack &operator=(const stack &rhs);
	~stack();

	void push(const T &item);
	T pop();

	Iterator begin() const;
	Iterator end() const;

	const T &top() const;
	T &top();
	size_t size() const;
	bool empty() const;
	
	void swap(stack &other) noexcept;

	template <typename U>
	friend std::ostream &operator<<(std::ostream &os, const stack<U> &s);
	bool operator==(const stack &rhs) const;
	bool operator!=(const stack &rhs) const;

private:
	void swap(stack &s1, stack &s2);

	node<T> *head;
	size_t sz;
};

/*
	@summary: Default constructor, initializes size to 0.
*/
template<typename T>
inline stack<T>::stack()
	: sz(0), head(nullptr)
{

}

/*
	@summary: Copy constructor.

	@param <const stack &other>: stack object to copy.
*/
template<typename T>
inline stack<T>::stack(const stack &other)
	: sz(other.sz), head(CopyList(other.head))
{

}

/*
	@summary: Copy assignment operator.

	@param <const stack &rhs>: stack object to copy.
*/
template<typename T>
inline stack<T> &stack<T>::operator=(const stack &rhs)
{
	stack temp(rhs);
	swap(temp);

	return *this;
}

/*
	@summary: Destructor.
*/
template<typename T>
inline stack<T>::~stack()
{
	ClearList(head);
}

/*
	@summary: Adds an item to the front of the stack and increments size.

	@param <const value_type &item>: Item to add to the stack.
*/
template<typename T>
inline void stack<T>::push(const T &item)
{
	InsertHead(head, item);
	++sz;
}

/*
	@summary: Removes an item from the top of the stack and decrements size.
*/
template<typename T>
inline T stack<T>::pop()
{
	if (empty())
	{
		throw std::out_of_range("Pop called on empty stack.");
	}

	T item = head->_item;

	DeleteNode(head, head);
	--sz;

	return item;
}

template<typename T>
inline typename stack<T>::Iterator stack<T>::begin() const
{
	return Iterator(head);
}

template<typename T>
inline typename stack<T>::Iterator stack<T>::end() const
{
	return Iterator(nullptr);
}

/*
	@summary: Returns the item at the top of the stack.

	@return <const reference>: Reference to the item at the top of the stack.
*/
template<typename T>
inline const T &stack<T>::top() const
{
	if (empty())
	{
		throw std::out_of_range("Top called on empty stack.");
	}

	return head->_item;
}

/*
	@summary: Returns the item at the top of the stack.

	@return <const reference>: Reference to the item at the top of the stack.
*/
template<typename T>
inline T &stack<T>::top()
{
	if (empty())
	{
		throw std::out_of_range("Top called on empty stack.");
	}

	return head->_item;
}

/*
	@summary: Returns the size of the stack.

	@return <size_type>: The size of the stack.
*/
template<typename T>
inline size_t stack<T>::size() const
{
	return sz;
}

/*
	@summary: Returns whether stack is empty.

	@return <bool>: If stack empty return true, else false.
*/
template<typename T>
inline bool stack<T>::empty() const
{
	return sz == 0 || head == nullptr;
}

/*
	@summary: Swaps contents of this stack with another stack.

	@param <stack &other>: stack to swap with.
*/
template<typename T>
inline void stack<T>::swap(stack &other) noexcept
{
	std::swap(sz, other.sz);
	std::swap(head, other.head);
}

/*
	@summary: Equality to check if two stacks are equal.
		Checks if size is equal, then if contents are equal.

	@param <const stack &rhs>: stack to compare to.

	@return <bool>: True if equal, else false.
*/
template<typename T>
inline bool stack<T>::operator==(const stack &rhs) const
{
	if (sz == rhs.sz)
	{
		return head == rhs.head;
	}

	return false;
}

/*
	@summary: Inequality to check if two stacks are not equal.
		Checks if size is not equal, then if contents are not equal.

	@param <const stack &rhs>: stack to compare to.

	@return <bool>: True if not equal, else false.
*/
template<typename T>
inline bool stack<T>::operator!=(const stack &rhs) const
{
	if (sz != rhs.sz)
	{
		return true;
	}

	return head != rhs.head;
}

/*
	@summary: Swaps contents of two stacks.

	@param <stack &s1>: first stack to swap.
	@param <stack &s2>: second stack to swap.
*/
template<typename T>
inline void stack<T>::swap(stack &s1, stack &s2)
{
	std::swap(s1.sz, s2.sz);
	std::swap(s1.head, s2.head);
}

/*
	@summary: Overloaded stream insertion operator to print contents of stack.

	@param <std::ostream &os>: The ostream object.
	@param <const stack<U> &s>: stack to print contents of.

	@return <std::ostream &>: Reference to the ostream object.
*/
template<typename U>
inline std::ostream &operator<<(std::ostream &os, const stack<U> &s)
{
	PrintList(s.head);

	return os;
}
