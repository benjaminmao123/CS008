#pragma once

#include <iostream>

#include "IteratedList.h"

template <class T>
class chained_hash
{
public:
	enum { TABLE_SIZE = 811 };
	// Or: static const int TABLE_SIZE = 811;
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
	int size() const { return total_records; }
	//print entire table with keys, etc.
	template<class TT>
	friend std::ostream& operator<<(std::ostream& outs,
									const chained_hash<TT>& h);
private:
	//table chains
	List<T> _data[TABLE_SIZE];
	//number of keys in the table
	int total_records;

	//hash function
	int hash(int key) const;
	//find this key in the table
	typename List<T>::Iterator find_node(int key) const;
};