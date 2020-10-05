/*
 * Author: Benjamin Mao
 * Project: Heap
 * Purpose: Driver
 *
 * Notes: None.
 */

#include "Heap.h"

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
	char input = '\0';
	Heap<int> heap;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1000);

	while (input != 'x')
	{
		std::cout << "[R]andom [I]nsert [C]lear [P]op E[x]it: ";
		std::cin >> input;

		switch (tolower(input))
		{
		case 'r':
		{
			int item = dist(gen);
			std::cout << "Insert: " << item << std::endl;

			heap.insert(item);
			break;
		}
		case 'i':
		{
			int item;
			std::cout << "Insert: ";
			std::cin >> item;
			std::cout << std::endl;

			heap.insert(item);
			break;
		}
		case 'c':
			heap.clear();
			break;
		case 'p':
		{
			if (!heap.is_empty())
			{
				int item = heap.pop();
				std::cout << "Pop: " << item << std::endl;
			}
			break;
		}
		case 'x':
			return;
		default:
			break;
		}

		std::cout << heap << std::endl;
	}
}