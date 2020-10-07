#pragma once

#include <iostream>
#include <cmath>
#include <functional>

#include "IteratedList.h"
#include "HTConstants.h"

template <class T>
class chained_hash
{
public:
	//CTOR
	chained_hash();

	//insert entry
	bool insert(const T& entry);
	//remove this key
	bool remove(int key);
	//result <- record with key
	bool find(int key, T& result) const;
	//is this key present in table?
	bool is_present(int key) const;
	//number of keys in the table
	constexpr int size() const { return total_records; }
	//print entire table with keys, etc.
	template<class TT>
	friend std::ostream& operator<<(std::ostream& outs,
									const chained_hash<TT>& h);
private:
	//hash function
	int hash(int key) const;
	//find this key in the table
	typename List<T>::Iterator find_node(int key) const;

	//table chains
	List<T> _data[TABLE_SIZE];
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
inline bool chained_hash<T>::insert(const T& entry)
{
	int index = hash(entry._key);
	_data[index].InsertHead(entry);

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

	return true;
}

template<class T>
inline bool chained_hash<T>::find(int key, T& result) const
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
	T res;

	return find(key, res);
}

template<class T>
inline int chained_hash<T>::hash(int key) const
{
	return hasher(key);
}

template<class T>
inline typename List<T>::Iterator chained_hash<T>::find_node(int key) const
{
	int index = hash(key);

	return _data[index].Search(key);
}

template<class TT>
inline std::ostream& operator<<(std::ostream& outs, const chained_hash<TT>& h)
{


	return outs;
}
