#include "OpenHash.h"

int main()
{
	LinearProbing lp;
	open_hash<int> ht(lp);

	for (int i = 0; i < 10000; ++i)
		ht.insert(record<int>(i, i));

	std::cout << ht;

	return 0;
}