#pragma once

#include <cmath>

#include "HTConstants.h"

namespace HTLibrary
{
	template <typename K, typename V>
	struct record
	{
		record() :
			actualIndex(-1)
		{

		}

		record(const K& k) :
			_key(k), actualIndex(-1)
		{

		}

		record(const K& k, const V& v) :
			_key(k), _value(v), actualIndex(-1)
		{

		}

		friend bool operator==(const record& left, const record& right)
		{
			return left._key == right._key;
		}

		friend std::ostream& operator<<(std::ostream& outs, const record& print_me)
		{
			outs << print_me._key << ":" << print_me._value;

			return outs;
		}

		K _key;
		V _value;
		int actualIndex;
	};

	template <typename T>
	struct Hash;

	template <>
	struct Hash<int>
	{
		int operator()(int key) const
		{
			const long long knuth_alpha = 2654435761;

			return std::abs(key * knuth_alpha >> 32);
		}
	};

	template <>
	struct Hash<std::size_t>
	{
		std::size_t operator()(std::size_t key) const
		{
			const long long knuth_alpha = 2654435761;

			return key * knuth_alpha >> 32;
		}
	};

	template <>
	struct Hash<std::string>
	{
		int operator()(const std::string& key) const
		{
			unsigned int hash = 1315423911;

			for (std::size_t i = 0; i < key.length(); i++)
				hash ^= ((hash << 5) + key[i] + (hash >> 2));

			return (hash & 0x7FFFFFFF);
		}
	};

	template <typename T>
	struct Hash2;

	template <>
	struct Hash2<int>
	{
		int operator()(int key) const
		{
			int prime = 7;

			return std::abs(prime - (key % prime));
		}
	};

	template <>
	struct Hash2<std::size_t>
	{
		std::size_t operator()(std::size_t key) const
		{
			int prime = 7;

			return prime - (key % prime);
		}
	};

	template <>
	struct Hash2<std::string>
	{
		int operator()(const std::string& key) const
		{
			unsigned long hash = 5381;
			int c;
			const char* k = key.c_str();

			while (c = *k++)
				hash = ((hash << 5) + hash) + c;

			return hash;
		}
	};

	constexpr int get_msb(int x);
	constexpr int get_prime(int n);
	constexpr int next_prime(int cap);

	constexpr int get_msb(int x)
	{
		if (!x)
			return 0;

		int msb = 31;

		while (!(x & (1 << msb)))
			--msb;

		return msb;
	}

	constexpr int get_prime(int n)
	{
		int msb = get_msb(n);

		return PRIMES[msb <= 4 ? 0 : msb - 4];
	}

	constexpr int next_prime(int cap)
	{
		int size = sizeof(PRIMES) / sizeof(PRIMES[0]);

		for (int i = 0; i < size; ++i)
			if (cap == PRIMES[i])
			{
				cap = PRIMES[i + 1];
				break;
			}

		return cap;
	}
}