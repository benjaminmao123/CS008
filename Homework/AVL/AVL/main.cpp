#include "AVL.h"

#include <iostream>
#include <cctype>
#include <random>

int main()
{
	AVL<int> avl;
	avl.insert(1);
	avl.insert(2);
	avl.insert(3);
	avl.insert(4);
	avl.insert(5);

	std::cout << avl << std::endl;

	return 0;
}