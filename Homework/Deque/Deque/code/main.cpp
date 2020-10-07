#include "Deque.h"

#include <iostream>

int main()
{
	deque<int> d;

	for (int i = 0; i < 10; ++i)
		d.push_back(i);

	std::cout << d << std::endl;

	d.push_front(10);

	std::cout << d << std::endl;

	d.pop_back();

	std::cout << d << std::endl;

	d.push_back(20);

	std::cout << d << std::endl;

	while (!d.empty())
	{
		d.pop_front();
		std::cout << d << std::endl;
	}

	d.push_back(1);

	std::cout << d << std::endl;

	return 0;
}