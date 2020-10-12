/*
 * Author: Benjamin Mao
 * Project: Heap
 * Purpose: Driver
 *
 * Notes: None.
 */

#include "PriorityQueue.h"

#include <iostream>
#include <cctype>
#include <random>

void Test();

int main()
{
	Test();

	return 0;
}

void Test()
{
	PQueue<int> pq;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1000);

	for (int i = 0; i < 100; ++i)
		pq.insert(dist(rd));

	for (int i = 0; i < 100; ++i)
		std::cout << pq.pop() << std::endl;
}