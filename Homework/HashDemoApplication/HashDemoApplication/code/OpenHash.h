#pragma once

#pragma once

#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>
#include <initializer_list>

#include "HTConstants.h"
#include "Vector.h"
#include "HTLibrary.h"

class ResolutionFunction
{
public:
	virtual unsigned int operator()(int i, 
									const std::initializer_list<int>& indices) const = 0;
};

class LinearProbing : public ResolutionFunction
{
public:
	virtual unsigned int operator()(int i, 
									const std::initializer_list<int>& indices) const override
	{
		int index = *indices.begin();

		return index + i;
	}
};

class QuadraticProbing : public ResolutionFunction
{
public:
	virtual unsigned int operator()(int i, 
									const std::initializer_list<int>& indices) const override
	{
		int index = *indices.begin();

		return index + (unsigned int)pow(i, 2);
	}
};

class DoubleHashing : public ResolutionFunction
{
public:
	virtual unsigned int operator()(int i, 
									const std::initializer_list<int>& indices) const override
	{
		int index = *indices.begin();
		int index2 = *(indices.begin() + 1);

		return index + i * index2;
	}
};

template <class T>
class open_hash
{
public:
	//CTOR
	open_hash(const ResolutionFunction& res, 
			  int n = 10, 
			  long long knuth = 2654435761,
			  int prime = 7);

	//insert entry
	bool insert(const HTLibrary::record<T>& entry);
	//remove this key
	bool remove(int key);
	//result <- record with key
	bool find(int key, HTLibrary::record<T>& result) const;
	//is this key present in table?
	bool is_present(int key) const;
	//number of keys in the table
	constexpr int size() const { return total_records; }
	constexpr bool empty() const { return !total_records; }
	constexpr int get_collisions() const { return numCollisions; }

	void swap(open_hash& other);

	//print entire table with keys, etc.
	template<class TT>
	friend std::ostream& operator<<(std::ostream& outs,
									const open_hash<TT>& h);
private:
	enum class BucketStatus
	{
		EMPTY,
		OCCUPIED,
		DELETED
	};

	//hash function
	constexpr int hash(int key) const;
	constexpr int hash2(int key) const;
	int find_item(int key) const;
	int get_free_index(int key);

	constexpr double load_factor() const { return (double)total_records / _data.size(); }
	constexpr int compute_capacity() const { return HTLibrary::next_prime(_data.size()); }
	void expand_table();

	const ResolutionFunction& resolution;
	//table chains
	Vector<HTLibrary::record<T>> _data;
	Vector<BucketStatus> status;
	//number of keys in the table
	int total_records;
	long long knuth_alpha;
	int prime;
	int numCollisions;
};

template<class T>
inline open_hash<T>::open_hash(const ResolutionFunction& res, 
							   int n, long long knuth, 
							   int prime) :
	total_records(0), 
	resolution(res),
	_data(HTLibrary::get_prime(n)),
	status(HTLibrary::get_prime(n)),
	knuth_alpha(knuth),
	prime(prime),
	numCollisions(0)
{

}

template<class T>
inline bool open_hash<T>::insert(const HTLibrary::record<T>& entry)
{
	if (load_factor() >= 0.75)
		expand_table();

	int actualIndex = hash(entry._key);
	int index = get_free_index(entry._key);

	if (index == -1)
		return false;

	_data[index] = entry;
	_data[index].actualIndex = actualIndex;
	status[index] = BucketStatus::OCCUPIED;
	++total_records;

	return true;
}

template<class T>
inline bool open_hash<T>::remove(int key)
{
	int index = find_item(key);

	if (index == -1)
		return false;

	status[index] = BucketStatus::DELETED;
	--total_records;

	return true;
}

template<class T>
inline bool open_hash<T>::find(int key, HTLibrary::record<T>& result) const
{
	int index = find_item(key);

	if (index == -1)
		return false;

	result = _data[index];

	return true;
}

template<class T>
inline bool open_hash<T>::is_present(int key) const
{
	HTLibrary::record<T> res;

	return find(key, res);
}

template<class T>
inline void open_hash<T>::swap(open_hash& other)
{
	std::swap(resolution, other.resolution);
	std::swap(_data, other._data);
	std::swap(total_records, other.total_records);
	std::swap(knuth_alpha, other.knuth_alpha);
	std::swap(prime, other.prime);
	std::swap(numCollisions, other.numCollisions);
	std::swap(status, other.status);
}

template<class T>
inline constexpr int open_hash<T>::hash(int key) const
{
	return (key * knuth_alpha >> 32) % _data.size();
}

template<class T>
inline constexpr int open_hash<T>::hash2(int key) const
{
	return (prime - (key % prime)) % _data.size();
}

template<class T>
inline int open_hash<T>::find_item(int key) const
{
	int index = hash(key);
	int index2 = hash2(key);
	int finalIndex = index;
	int i = 0;

	while (status[finalIndex] != BucketStatus::EMPTY &&
		   status[finalIndex] != BucketStatus::DELETED)
	{
		if (i >= _data.size())
			return -1;

		if (status[finalIndex] == BucketStatus::OCCUPIED &&
			_data[finalIndex]._key == key)
			return finalIndex;

		finalIndex = resolution(++i, { index, index2 }) % _data.size();
	}

	return -1;
}

template<class T>
inline int open_hash<T>::get_free_index(int key)
{
	int index = hash(key);
	int index2 = hash2(key);
	int finalIndex = index;
	int i = 0;

	while (status[finalIndex] == BucketStatus::OCCUPIED)
	{
		if (_data[finalIndex]._key == key)
			return -1;

		++numCollisions;

		finalIndex =  resolution(++i, { index, index2 }) % _data.size();
	}

	return finalIndex;
}

template<class T>
inline void open_hash<T>::expand_table()
{
	Vector<HTLibrary::record<T>> tempTable(compute_capacity());
	Vector<BucketStatus> tempStatus(tempTable.capacity());

	_data.swap(tempTable);
	status.swap(tempStatus);
	total_records = 0;

	for (int i = 0; i < tempTable.size(); ++i)
	{
		if (tempStatus[i] == BucketStatus::OCCUPIED)
			insert(tempTable[i]);
	}
}

template<class TT>
inline std::ostream& operator<<(std::ostream& outs, const open_hash<TT>& h)
{
	auto NumDigits = [](int i)
	{
		return i > 0 ? (int)log10((double)i) + 1 : 1;
	};

	for (int i = 0; i < h._data.size(); ++i)
	{
		outs << "[" << std::setfill('0') << std::setw(NumDigits(h._data.size())) << i << "]"
			<< " ";

		if (h.status[i] == open_hash<TT>::BucketStatus::OCCUPIED)
		{
			outs << h._data[i] <<
				"(" << std::setfill('0') << std::setw(NumDigits(h._data.size())) << i << ")";

			if (h._data[i].actualIndex != i)
				outs << "*";
		}
		if (h.status[i] == open_hash<TT>::BucketStatus::DELETED)
			outs << "------";

		outs << std::endl;
	}

	return outs;
}
