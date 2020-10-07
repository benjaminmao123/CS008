#pragma once

#pragma once

#include <iostream>
#include <cmath>
#include <functional>

#include "HTConstants.h"
#include "Vector.h"
#include "HTLibrary.h"

class ResolutionFunction
{
public:
	virtual unsigned int operator()(int hashVal, int i) const = 0;
};

class LinearProbing : public ResolutionFunction
{
public:
	virtual unsigned int operator()(int hashVal, int i) const override
	{
		return hashVal + i;
	}
};

class QuadraticProbing : public ResolutionFunction
{
public:
	virtual unsigned int operator()(int hashVal, int i) const override
	{
		return hashVal + pow(i, 2);
	}
};

class DoubleHashing : public ResolutionFunction
{
public:
	virtual unsigned int operator()(int hashVal, int i) const override
	{
		return hashVal + (DOUBLE_HASH_PRIME - (i % DOUBLE_HASH_PRIME));
	}
};

template <class T>
class open_hash
{
public:
	//CTOR
	open_hash(const ResolutionFunction& res, int n = 10);
	~open_hash();
	open_hash(const open_hash& other);
	open_hash& operator=(const open_hash& rhs);

	//insert entry
	bool insert(const record<T>& entry);
	//remove this key
	bool remove(int key);
	//result <- record with key
	bool find(int key, record<T>& result) const;
	//is this key present in table?
	bool is_present(int key) const;
	//number of keys in the table
	constexpr int size() const { return total_records; }
	constexpr bool empty() const { return !total_records; }

	void swap(open_hash& other);

	//print entire table with keys, etc.
	template<class TT>
	friend std::ostream& operator<<(std::ostream& outs,
									const open_hash<TT>& h);
private:
	//hash function
	constexpr int hash(int key) const;
	int find_item(int key) const;
	int get_free_index(int key) const;

	constexpr double load_factor() const { return (double)total_records / _data.size(); }
	constexpr int compute_capacity() const { return next_prime(_data.size()); }
	void expand_table();

	const ResolutionFunction& resolution;
	//table chains
	Vector<record<T>*> _data;
	//number of keys in the table
	int total_records;
};

template<class T>
inline open_hash<T>::open_hash(const ResolutionFunction& res, int n) :
	total_records(0), 
	resolution(res),
	_data(get_prime(n))
{

}

template<class T>
inline open_hash<T>::~open_hash()
{
	for (auto& i : _data)
		delete i;
}

template<class T>
inline open_hash<T>::open_hash(const open_hash& other) :
	resolution(other.resolution),
	total_records(other.total_records),
	_data(other.size())
{

	for (int i = 0; i < other._data.size(); ++i)
	{
		if (other._data[i])
		{
			record<T>* item = other._data[i];
			_data[i] = new record<T>(item->_key, item->_value);
		}
		else
			_data[i] = other._data[i];
	}
}

template<class T>
inline open_hash<T>& open_hash<T>::operator=(const open_hash<T>& rhs)
{
	open_hash<T> temp(rhs);
	swap(temp);

	return *this;
}

template<class T>
inline bool open_hash<T>::insert(const record<T>& entry)
{
	if (load_factor() >= 0.75)
		expand_table();

	int index = get_free_index(entry._key);

	if (index == -1)
		return false;

	_data[index] = new record<T>(entry._key, entry._value);
	++total_records;

	return true;
}

template<class T>
inline bool open_hash<T>::remove(int key)
{
	int index = find_item(key);

	if (index == -1)
		return false;

	delete _data[index];
	_data[index] = nullptr;
	--total_records;

	return true;
}

template<class T>
inline bool open_hash<T>::find(int key, record<T>& result) const
{
	int index = find_item(key);

	if (index == -1 || !_data[index])
		return false;

	result = *_data[index];

	return true;
}

template<class T>
inline bool open_hash<T>::is_present(int key) const
{
	record<T> res;

	return find(key, res);
}

template<class T>
inline void open_hash<T>::swap(open_hash& other)
{
	std::swap(resolution, other.resolution);
	std::swap(_data, other._data);
	std::swap(total_records, other.total_records);
}

template<class T>
inline constexpr int open_hash<T>::hash(int key) const
{
	return (key * KNUTH_ALPHA >> 32) % _data.size();
}

template<class T>
inline int open_hash<T>::find_item(int key) const
{
	int index = hash(key);
	int finalIndex = index;
	int i = 0;

	while (true)
	{
		if (i >= _data.size() || !_data[finalIndex])
			return -1;

		if (_data[finalIndex]->_key == key)
			break;

		finalIndex = resolution(index, ++i) % _data.size();
	}

	return finalIndex;
}

template<class T>
inline int open_hash<T>::get_free_index(int key) const
{
	int index = hash(key);
	int finalIndex = index;
	int i = 0;

	while (_data[finalIndex])
	{
		if (i > _data.size() || _data[finalIndex]->_key == key)
			return -1;

		finalIndex =  resolution(index, ++i) % _data.size();
	}

	return finalIndex;
}

template<class T>
inline void open_hash<T>::expand_table()
{
	Vector<record<T>*> tempTable(compute_capacity());

	_data.swap(tempTable);
	total_records = 0;

	for (int i = 0; i < tempTable.size(); ++i)
	{
		if (tempTable[i])
			insert(*tempTable[i]);
		else
			_data[i] = nullptr;
	}

	for (auto& i : tempTable)
		delete i;
}

template<class TT>
inline std::ostream& operator<<(std::ostream& outs, const open_hash<TT>& h)
{
	for (int i = 0; i < h._data.size(); ++i)
	{
		if (h._data[i])
			outs << *h._data[i] << std::endl;
		else
			outs << "NULL" << std::endl;
	}

	return outs;
}
