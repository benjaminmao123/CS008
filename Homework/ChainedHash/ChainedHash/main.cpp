#include <iostream>

#include "ChainedHash.h"

template <typename T>
struct record
{
	record(int k, const T& v) :
		_key(k), _value(v)
	{

	}

	friend bool operator==(const record& left, const record& right)
	{
		return left._key == right._key && left._value == right._value;
	}

	friend std::ostream& operator<<(std::ostream& outs, const record& print_me)
	{
		return outs;
	}

	int _key;
	T _value;
};

int main()
{
	chained_hash<record<double>> ch;

	ch.insert(record<double>(0, 15.0));

	return 0;
}