#pragma once

#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

#include "IteratedList.h"
#include "HTConstants.h"
#include "Vector.h"
#include "HTLibrary.h"

template <class T>
class chained_hash
{
public:
	//CTOR
	chained_hash(int n = 10, int knuth = 2654435761);

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
	constexpr int hash(int key) const;
	//find this key in the table
	typename List<record<T>>::Iterator find_node(int key) const;
	constexpr double load_factor() const { return (double)total_records / _data.size(); }
	constexpr int compute_capacity() const { return next_prime(_data.size()); }
	void expand_table();

	//table chains
	Vector<List<record<T>>> _data;
	//number of keys in the table
	int total_records;
	int knuth_alpha;
};

template<class T>
inline chained_hash<T>::chained_hash(int n, int knuth) :
	total_records(0),
	_data(get_prime(n)),
	knuth_alpha(knuth)
{

}

template<class T>
inline bool chained_hash<T>::insert(const record<T>& entry)
{
	if (is_present(entry._key))
		return false;

	if (load_factor() >= 0.75)
		expand_table();

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
inline constexpr int chained_hash<T>::hash(int key) const
{
	return (key * knuth_alpha >> 32) % _data.size();
}

template<class T>
inline typename List<record<T>>::Iterator chained_hash<T>::find_node(int key) const
{
	int index = hash(key);

	return _data[index].Search(record<T>(key));
}

template<class T>
inline void chained_hash<T>::expand_table()
{
	Vector<List<record<T>>> tempTable(compute_capacity());

	_data.swap(tempTable);
	total_records = 0;

	for (const auto& list : tempTable)
		for (const auto& item : list)
			insert(item);
}

template<class TT>
inline std::ostream& operator<<(std::ostream& outs, const chained_hash<TT>& h)
{
	auto NumDigits = [](int i)
	{
		return i > 0 ? (int)log10((double)i) + 1 : 1;
	};

	for (int i = 0; i < h._data.size(); ++i)
	{
		outs << "[" << std::setfill('0') << std::setw(NumDigits(h._data.size())) << i << "]"
			<< " " << h._data[i] << std::endl;
	}

	return outs;
}
