#pragma once

#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

#include "IteratedList.h"
#include "HTConstants.h"
#include "Vector.h"
#include "HTLibrary.h"

template <typename K, typename V, typename H = HTLibrary::Hash<K>>
class chained_hash
{
public:
	//CTOR
	chained_hash(int n = 10);

	//insert entry
	bool insert(const HTLibrary::record<K, V>& entry);
	//remove this key
	bool remove(const K& key);
	//result <- record with key
	bool find(const K& key, HTLibrary::record<K, V>& result) const;
	//is this key present in table?
	bool is_present(const K& key) const;
	//number of keys in the table
	constexpr int size() const { return total_records; }
	constexpr bool empty() const { return !total_records; }

	//print entire table with keys, etc.
	template <typename T, typename U>
	friend std::ostream& operator<<(std::ostream& outs, const chained_hash<T, U>& h);

private:
	//hash function
	H hasher;

	//find this key in the table
	typename List<HTLibrary::record<K, V>>::Iterator find_node(const K& key) const;
	constexpr double load_factor() const { return (double)total_records / _data.size(); }
	constexpr int compute_capacity() const { return HTLibrary::next_prime(_data.size()); }
	void expand_table();

	//table chains
	Vector<List<HTLibrary::record<K, V>>> _data;
	//number of keys in the table
	int total_records;
};

template <typename K, typename V, typename H>
inline chained_hash<K, V, H>::chained_hash(int n) :
	total_records(0),
	_data(HTLibrary::get_prime(n))
{

}

template <typename K, typename V, typename H>
inline bool chained_hash<K, V, H>::insert(const HTLibrary::record<K, V>& entry)
{
	if (load_factor() >= 0.75)
		expand_table();

	int index = hasher(entry._key) % _data.size();

	if (_data[index].Search(entry))
		return false;

	_data[index].InsertAfter(entry, _data[index].begin());
	++total_records;

	return true;
}

template <typename K, typename V, typename H>
inline bool chained_hash<K, V, H>::remove(const K& key)
{
	int index = hasher(key) % _data.size();
	auto it = find_node(key);

	if (!it)
		return false;

	_data[index].Delete(it);
	--total_records;

	return true;
}

template <typename K, typename V, typename H>
inline bool chained_hash<K, V, H>::find(const K& key, HTLibrary::record<K, V>& result) const
{
	int index = hasher(key) % _data.size();
	auto it = find_node(key);

	if (!it)
		return false;

	result = *it;

	return true;
}

template <typename K, typename V, typename H>
inline bool chained_hash<K, V, H>::is_present(const K& key) const
{
	HTLibrary::record<K, V> res;

	return find(key, res);
}

template <typename K, typename V, typename H>
inline typename List<HTLibrary::record<K, V>>::Iterator chained_hash<K, V, H>::find_node(const K& key) const
{
	int index = hasher(key) % _data.size();

	return _data[index].Search(HTLibrary::record<K, V>(key));
}

template <typename K, typename V, typename H>
inline void chained_hash<K, V, H>::expand_table()
{
	Vector<List<HTLibrary::record<K, V>>> tempTable(compute_capacity());

	_data.swap(tempTable);
	total_records = 0;

	for (const auto& list : tempTable)
		for (const auto& item : list)
			insert(item);
}

template <typename T, typename U>
inline std::ostream& operator<<(std::ostream& outs, const chained_hash<T, U>& h)
{
	auto NumDigits = [](int i)
	{
		return i > 0 ? (int)log10((double)i) + 1 : 1;
	};

	for (unsigned int i = 0; i < h._data.size(); ++i)
	{
		outs << "[" << std::setfill('0') << std::setw(NumDigits(h._data.size())) << i << "]"
			<< " " << h._data[i] << std::endl;
	}

	return outs;
}
