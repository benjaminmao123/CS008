/*
 * Author: Benjamin Mao
 * Project: Array Library
 * Purpose: Library functions to use for array
 *			manipulation.
 * Notes: None.
 *
 */

#pragma once

template <typename T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity);

template <typename T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity);

template <typename T>
T* allocate(T* list, int capacity);

template <typename T>
T* reallocate(T* list, int size, int capacity);

template <typename T>
void copy_list(T* dest, const T* src, int size);

template <typename T>
T* search_entry(T* list, const T& find_me, int size, int& index);

template <typename T>
void shift_left(T* start, const T* end);

template <typename T>
void shift_right(T* start, const T* end);

template <typename T>
void delete_array(T*& list);

template <typename T>
void remove_last(T*& list, int& size, int& capacity);

/*
	Appends an element to the given array.

	@param <T *list>: Original array.
	@param <T &new_entry>: Value to append.
	@param <int &size>: Size of the array.
	@param <int &capacity>: Capacity of the array.

	@return <T*>: New array with appended element.
*/
template<typename T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity)
{
	if (size >= capacity)
	{
		//increase capacity by a factor of 2
		capacity *= 2;

		list = reallocate(list, size, capacity);

		//append the element
		T* listWalker = list + size++;
		*listWalker = new_entry;
	}
	else
	{
		//append the element
		T* listWalker = list + size++;
		*listWalker = new_entry;
	}

	return list;
}

/*
	Removes an element from the array.

	@param <T *list>: Original array.
	@param <const T &delete_me>: Value to remove.
	@param <int &size>: Size of the original array.
	@param <int &capacity>: Capacity of the array.

	@return <T*>: A new array without the deleted element.
*/
template<typename T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity)
{
	//find the element to delete
	int index = 0;
	T* deleteEntry = search_entry(list, delete_me, size, index);
	T* newList = list;

	//delete if the element exists
	if (deleteEntry)
	{
		shift_left(deleteEntry, list + size);

		//if the size drops below a certain amount decrease capacity
		if (size <= capacity / 4)
			capacity /= 2;

		--size;

		newList = reallocate(list, size, capacity);
	}

	return newList;
}

/*
	Allocate memory to a given array.

	@param <T *list>: Array to allocate memory for.
	@param <int capacity>: Determines the amount of memory to
		allocate.

	@return <T*>: New array with a given capacity.
*/
template<typename T>
T* allocate(T* list, int capacity)
{
	list = new T[capacity]();

	return list;
}

template<typename T>
T* reallocate(T* list, int size, int capacity)
{
	//allocate memory for new list
	T* newList = nullptr;
	newList = allocate(newList, capacity);
	T* listEnd = list + size;

	//copy elements from the old list to the new list
	copy_list(newList, list, size);
	delete_array(list);

	return newList;
}

/*
	Copies a source array to a destination array.

	@param <T *dest>: The array to copy to.
	@param <T *src>: The array to copy from.
	@param <int size>: Size of the source array.
*/
template<typename T>
void copy_list(T* dest, const T* src, int size)
{
	T* destEnd = dest + size;

	for (T* i = dest; i != destEnd; ++i, ++src)
		*i = *src;
}

/*
	Finds an element containing the given value from
	a given array.

	@param <T *list>: The array to search.
	@param <T &find_me>: The value to search for.
	@param <int size>: Size of the array.

	@return <T*>: If the element is found, return a pointer
		to the first element found. Else, return nullptr.
*/
template<typename T>
T* search_entry(T* list, const T& find_me, int size, int& index)
{
	T* listEnd = list + size;
	index = 0;

	for (T* i = list; i != listEnd; ++i)
	{
		if (*i == find_me)
			return i;

		++index;
	}

	index = -1;

	return nullptr;
}

/*
	Shifts the array elements left starting from a specified index.

	@param <T *start>: position to shift left from.
	@param <int size>: Size of the array.
*/
template<typename T>
void shift_left(T* start, const T* end)
{
	T* next = start + 1;

	for (T* curr = start; curr != end - 1; ++curr, ++next)
		*curr = *next;
}


/*
	Shifts the array elements right starting from a specified index.

	@param <T *start>: position to shift right from.
	@param <int size>: Size of the array.
*/
template<typename T>
void shift_right(T* start, const T* end)
{
	T* next = start + 1;

	for (T* curr = start; curr != end - 1; --curr, --next)
		*next = *curr;
}

template<typename T>
inline void delete_array(T*& list)
{
	delete[] list;
	list = nullptr;
}

template<typename T>
inline void remove_last(T*& list, int& size, int& capacity)
{
	T* newList = nullptr;

	//if the size drops below a certain amount decrease capacity
	if (size <= capacity / 4)
	{
		capacity /= 2;
		newList = reallocate(list, size, capacity);
		list = newList;
	}

	--size;
}
