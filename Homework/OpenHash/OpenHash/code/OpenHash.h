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
		if (indices.size() < 1)
			throw std::out_of_range("Size of indices was less than 1");

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
		if (indices.size() < 1)
			throw std::out_of_range("Size of indices was less than 1");

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
		if (indices.size() < 2)
			throw std::out_of_range("Size of indices was less than 2");

		int index = *indices.begin();
		int index2 = *(indices.begin() + 1);

		return index + i * index2;
	}
};

template <typename K, typename V, typename H = HTLibrary::Hash<K>, 
	typename H2 = HTLibrary::Hash2<K>>
class open_hash
{
private:
	enum class BucketStatus
	{
		EMPTY,
		OCCUPIED,
		DELETED
	};

public:
	class Iterator
	{
	public:
		Iterator() {}

		Iterator(typename Vector<HTLibrary::record<K, V>>::Iterator vecIt, 
			typename Vector<BucketStatus>::Iterator bIt)
			: vecIt(vecIt), bIt(bIt)
		{
			
		}

		Iterator(const Iterator& other) :
			vecIt(other.vecIt),
			bIt(other.bIt)
		{
		}

		Iterator& operator++()
		{
			++bIt;
			++vecIt;

			while ((vecIt && bIt) && (*bIt == BucketStatus::EMPTY || *bIt == BucketStatus::DELETED))
			{
				++bIt;
				++vecIt;
			}

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp(*this);
			operator++();

			return temp;
		}

		bool operator==(const Iterator& rhs) const
		{
			return vecIt == rhs.vecIt && bIt == rhs.bIt;
		}

		bool operator!=(const Iterator& rhs) const
		{
			return vecIt != rhs.vecIt || bIt != rhs.bIt;
		}

		HTLibrary::record<K, V>& operator*()
		{
			return *vecIt;
		}

		const HTLibrary::record<K, V>& operator*() const
		{
			return *vecIt;
		}

		HTLibrary::record<K, V>* operator->()
		{
			return vecIt.operator->();
		}

		const HTLibrary::record<K, V>* operator->() const
		{
			return vecIt.operator->();
		}

		operator bool() const
		{
			return (vecIt && bIt) && 
				(*bIt != BucketStatus::EMPTY && *bIt != BucketStatus::DELETED);
		}

	private:
		typename Vector<HTLibrary::record<K, V>>::Iterator vecIt;
		typename Vector<BucketStatus>::Iterator bIt;
	};

	//CTOR
	open_hash(const ResolutionFunction& res = DoubleHashing(), int n = 10);

	Iterator begin();
	Iterator end();
	Iterator cbegin() const;
	Iterator cend() const;

	//insert entry
	Iterator insert(const K& key, const V& value);
	//remove this key
	bool remove(const K& key);
	//result <- record with key
	Iterator find(const K& key);
	//is this key present in table?
	bool is_present(const K& key);
	//number of keys in the table
	constexpr int size() const { return total_records; }
	constexpr bool empty() const { return !total_records; }
	constexpr int get_collisions() const { return numCollisions; }

	V& operator[](const K& key);
	const V& operator[](const K& key) const;

	void swap(open_hash& other);

	//print entire table with keys, etc.
	template <typename T, typename U>
	friend std::ostream& operator<<(std::ostream& outs, const open_hash<T, U>& h);

private:
	//hash function
	H hasher;
	H2 hasher2;

	int find_item(const K& key) const;
	int get_free_index(const K& key);

	constexpr double load_factor() const { return (double)total_records / _data.size(); }
	constexpr int compute_capacity() const { return HTLibrary::next_prime(_data.size()); }
	void expand_table();

	const ResolutionFunction& resolution;
	//table chains
	Vector<HTLibrary::record<K, V>> _data;
	Vector<BucketStatus> status;
	//number of keys in the table
	int total_records;

	int numCollisions;
};

template <typename K, typename V, typename H, typename H2>
inline open_hash<K, V, H, H2>::open_hash(const ResolutionFunction& res, int n) :
	total_records(0),
	resolution(res),
	_data(HTLibrary::get_prime(n)),
	status(HTLibrary::get_prime(n)),
	numCollisions(0)
{

}

template<typename K, typename V, typename H, typename H2>
inline typename open_hash<K, V, H, H2>::Iterator open_hash<K, V, H, H2>::begin()
{
	return Iterator(_data.begin(), status.begin());
}

template<typename K, typename V, typename H, typename H2>
inline typename open_hash<K, V, H, H2>::Iterator open_hash<K, V, H, H2>::end()
{
	return Iterator(_data.end(), status.end());
}

template<typename K, typename V, typename H, typename H2>
inline typename open_hash<K, V, H, H2>::Iterator open_hash<K, V, H, H2>::cbegin() const
{
	return Iterator(_data.cbegin(), status.cbegin());
}

template<typename K, typename V, typename H, typename H2>
inline typename open_hash<K, V, H, H2>::Iterator open_hash<K, V, H, H2>::cend() const
{
	return Iterator(_data.cend(), status.cend());
}

template <typename K, typename V, typename H, typename H2>
inline typename open_hash<K, V, H, H2>::Iterator open_hash<K, V, H, H2>::insert(const K& key, const V& value)
{
	if (load_factor() >= 0.75)
		expand_table();

	HTLibrary::record<K, V> entry(key, value);

	int actualIndex = hasher(entry._key) % _data.size();
	int index = get_free_index(entry._key);

	_data[index] = entry;
	_data[index].actualIndex = actualIndex;
	status[index] = BucketStatus::OCCUPIED;
	++total_records;

	return Iterator(_data.begin() + index, status.begin() + index);
}

template <typename K, typename V, typename H, typename H2>
inline bool open_hash<K, V, H, H2>::remove(const K& key)
{
	int index = find_item(key);

	if (index < 0)
		return false;

	status[index] = BucketStatus::DELETED;
	--total_records;

	return true;
}

template <typename K, typename V, typename H, typename H2>
inline typename open_hash<K, V, H, H2>::Iterator open_hash<K, V, H, H2>::find(const K& key)
{
	int index = find_item(key);

	if (index < 0)
		return end();

	return Iterator(_data.begin() + index, status.begin() + index);
}

template <typename K, typename V, typename H, typename H2>
inline bool open_hash<K, V, H, H2>::is_present(const K& key)
{
	return find(key);
}

template<typename K, typename V, typename H, typename H2>
inline V& open_hash<K, V, H, H2>::operator[](const K& key)
{
	auto it = find(key);

	if (!it)
		return insert(key, V())->_value;

	return it->_value;
}

template<typename K, typename V, typename H, typename H2>
inline const V& open_hash<K, V, H, H2>::operator[](const K& key) const
{
	auto it = find(key);

	if (!it)
		return insert(key, V())->_value;

	return it->_value;
}

template <typename K, typename V, typename H, typename H2>
inline void open_hash<K, V, H, H2>::swap(open_hash& other)
{
	std::swap(resolution, other.resolution);
	std::swap(_data, other._data);
	std::swap(total_records, other.total_records);
	std::swap(numCollisions, other.numCollisions);
	std::swap(status, other.status);
}

template <typename K, typename V, typename H, typename H2>
inline int open_hash<K, V, H, H2>::find_item(const K& key) const
{
	int index = hasher(key) % _data.size();
	int index2 = hasher2(key) % _data.size();
	int finalIndex = index;
	int i = 0;

	while (status[finalIndex] != BucketStatus::EMPTY)
	{
		if (status[finalIndex] == BucketStatus::OCCUPIED &&
			_data[finalIndex]._key == key)
			return finalIndex;

		finalIndex = resolution(++i, { index, index2 }) % _data.size();
	}

	return -1;
}

template <typename K, typename V, typename H, typename H2>
inline int open_hash<K, V, H, H2>::get_free_index(const K& key)
{
	int index = hasher(key) % _data.size();
	int index2 = hasher2(key) % _data.size();
	int finalIndex = index;
	int i = 0;

	while (status[finalIndex] == BucketStatus::OCCUPIED)
	{
		if (_data[finalIndex]._key == key)
			return finalIndex;

		++numCollisions;

		finalIndex = resolution(++i, { index, index2 }) % _data.size();
	}

	return finalIndex;
}

template <typename K, typename V, typename H, typename H2>
inline void open_hash<K, V, H, H2>::expand_table()
{
	Vector<HTLibrary::record<K, V>> tempTable(compute_capacity());
	Vector<BucketStatus> tempStatus(tempTable.capacity());

	_data.swap(tempTable);
	status.swap(tempStatus);
	total_records = 0;

	for (int i = 0; i < tempTable.size(); ++i)
	{
		if (tempStatus[i] == BucketStatus::OCCUPIED)
			insert(tempTable[i]._key, tempTable[i]._value);
	}
}

template <typename T, typename U>
inline std::ostream& operator<<(std::ostream& outs, const open_hash<T, U>& h)
{
	auto NumDigits = [](int i)
	{
		return i > 0 ? (int)log10((double)i) + 1 : 1;
	};

	for (int i = 0; i < h._data.size(); ++i)
	{
		outs << "[" << std::setfill('0') << std::setw(NumDigits(h._data.size())) << i << "]"
			<< " ";

		if (h.status[i] == open_hash<T, U>::BucketStatus::OCCUPIED)
		{
			outs << h._data[i] <<
				"(" << std::setfill('0') << std::setw(NumDigits(h._data.size()))
				<< h._data[i].actualIndex << ")";

			if (h._data[i].actualIndex != i)
				outs << "*";
		}
		if (h.status[i] == open_hash<T, U>::BucketStatus::DELETED)
			outs << "------";

		outs << std::endl;
	}

	return outs;
}

