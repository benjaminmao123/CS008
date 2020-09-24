#include "BST.h"

#include <iostream>

using namespace std;

int main()
{
	int a[] = { 1, 2, 3, 4, 5 };

	BST<int> bst(a, 5);

	cout << bst << endl;

	return 0;
}