#include <iostream>

/*
 * Author: Benjamin Mao
 * Project: Priority Queue
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
    std::uniform_int_distribution<> dist(1, 1000);

    for (int i = 0; i < 100; i++) 
        pq.insert(dist(rd), dist(rd));

    std::cout << pq << std::endl;
}