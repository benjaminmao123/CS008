/*
 * Author: Benjamin Mao
 * Project: AVL
 * Purpose: Driver
 *
 * Notes: None.
 */

#include "AVL.h"

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
	const int a[] = { 22, 30, 33, 43, 45, 56, 62, 77, 82, 85, 92, 94, 95 };
	AVL<int> avl(a, sizeof(a) / sizeof(a[0]));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1000);

	while (input != 'x')
	{
		std::cout << "[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: ";
		std::cin >> input;

		switch (tolower(input))
		{
		case 'r':
		{
			int item = dist(gen);
			std::cout << "Insert: " << item << std::endl;

			avl.insert(item);
			avl.is_valid();
			break;
		}
		case 'i':
		{
			int item;
			std::cout << "Insert: ";
			std::cin >> item;
			std::cout << std::endl;

			avl.insert(item);
			avl.is_valid();
			break;
		}
		case 'c':
			avl.clear();
			break;
		case 's':
		{
			tree_node<int>* fptr;
			int item;
			std::cout << "Search: ";
			std::cin >> item;
			std::cout << std::endl;

			if (avl.search(item, fptr))
				std::cout << "Item is found." << std::endl;
			else
				std::cout << "Item is not found." << std::endl;
			break;
		}
		case 'e':
		{
			int item;
			std::cout << "Erase: ";
			std::cin >> item;
			std::cout << std::endl;

			avl.erase(item);
			avl.is_valid();
			break;
		}
		case 'x':
			return;
		default:
			break;
		}

		std::cout << avl << std::endl;
	}
}