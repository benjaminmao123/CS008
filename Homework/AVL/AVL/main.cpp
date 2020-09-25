#include "AVL.h"

#include <iostream>
#include <cctype>
#include <random>

int main()
{
	AVL<int> avl;

	for (int i = 1; i <= 5; ++i)
	{
		std::cout << "Iteration: " << i << std::endl;
		avl.insert(i);
		std::cout << avl << std::endl;
	}

	return 0;
}