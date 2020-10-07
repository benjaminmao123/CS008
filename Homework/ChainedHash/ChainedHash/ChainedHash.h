#pragma once

#include <iostream>
#include <cmath>
#include <functional>

#include "IteratedList.h"
#include "HTConstants.h"

template <typename T>
struct record
{
	record(int k = 0) :
		_key(k)
	{

	}

	record(int k, const T& v) :
		_key(k), _value(v)
	{

	}

	friend bool operator==(const record& left, const record& right)
	{
		return left._key == right._key;
	}

	friend std::ostream& operator<<(std::ostream& outs, const record& print_me)
	{
		outs << print_me._key << ", " << print_me._value;

		return outs;
	}

	int _key;
	T _value;
};

template <class T>
class chained_hash
{
public:
	//CTOR
	chained_hash();

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
	//print entire table with keys, etc.
	template<class TT>
	friend std::ostream& operator<<(std::ostream& outs,
									const chained_hash<TT>& h);
private:
	//hash function
	int hash(int key) const;
	//find this key in the table
	typename List<record<T>>::Iterator find_node(int key) const;

	//table chains
	List<record<T>> _data[TABLE_SIZE];
	//number of keys in the table
	int total_records;
	std::hash<int> hasher;
};

template<class T>
inline chained_hash<T>::chained_hash() :
	total_records(0)
{

}

template<class T>
inline bool chained_hash<T>::insert(const record<T>& entry)
{
	if (is_present(entry._key))
		return false;

	int index = hash(entry._key);
	_data[index].InsertAfter(entry, _data[index].begin());
	++total_records;

	return true;
}

template<class T>
inline bool chained_hash<T>::remove(int key)
{
	int index = hash(key);
	auto it = find_node(key);

	if (!it)
		return false;

	_data[index].Delete(it);
	--total_records;

	return true;
}

template<class T>
inline bool chained_hash<T>::find(int key, record<T>& result) const
{
	int index = hash(key);
	auto it = find_node(key);

	if (!it)
		return false;

	result = *it;

	return true;
}

template<class T>
inline bool chained_hash<T>::is_present(int key) const
{
	record<T> res;

	return find(key, res);
}

template<class T>
inline int chained_hash<T>::hash(int key) const
{
	return hasher(key) % TABLE_SIZE;
}

template<class T>
inline typename List<record<T>>::Iterator chained_hash<T>::find_node(int key) const
{
	int index = hash(key);

	return _data[index].Search(record<T>(key));
}

template<class TT>
inline std::ostream& operator<<(std::ostream& outs, const chained_hash<TT>& h)
{
	for (int i = 0; i < TABLE_SIZE; ++i)
		outs << h._data[i] << std::endl;

	return outs;
}
