#include "Heap.h"

#include <iostream>

using namespace std;

int main()
{
	Heap<int> heap;

	heap.insert(0);
	heap.insert(1);
	heap.insert(2);
	heap.insert(3);
	heap.insert(4);

	cout << heap << endl;

	return 0;
}