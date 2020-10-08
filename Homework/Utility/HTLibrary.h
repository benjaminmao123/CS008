#pragma once

#include "HTConstants.h"

namespace HTLibrary
{
	template <typename T>
	struct record
	{
		record(int k = 0) : _key(k)
		{
		}

		record(int k, const T &v) : _key(k), _value(v)
		{
		}

		friend bool operator==(const record &left, const record &right)
		{
			return left._key == right._key;
		}

		friend std::ostream &operator<<(std::ostream &outs, const record &print_me)
		{
			outs << print_me._key << ":" << print_me._value;

			return outs;
		}

		int _key;
		T _value;
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

		return primes[msb <= 4 ? 0 : msb - 4];
	}

	constexpr int next_prime(int cap)
	{
		int size = sizeof(primes) / sizeof(primes[0]);

		for (int i = 0; i < size; ++i)
			if (cap == primes[i])
			{
				cap = primes[i + 1];
				break;
			}

		return cap;
	}
} // namespace HTLibrary