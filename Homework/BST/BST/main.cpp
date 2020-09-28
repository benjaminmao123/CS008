/*
 * Author: Benjamin Mao
 * Project: BST
 * Purpose: Driver
 *
 * Notes: None.
 */

#include "BST.h"

#include <iostream>
#include <string>
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
	BST<int> bst;
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

			bst.insert(item);
			break;
		}
		case 'i':
		{
			int item;
			std::cout << "Insert: ";
			std::cin >> item;
			std::cout << std::endl;

			bst.insert(item);
			break;
		}
		case 'c':
		{
			BST<int> temp;
			bst.swap(temp);
			break;
		}
		case 's':
		{
			tree_node<int>* fptr;
			int item;
			std::cout << "Search: ";
			std::cin >> item;
			std::cout << std::endl;

			if (bst.search(item, fptr))
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

			bst.erase(item);
			break;
		}
		case 'x':
			return;
		default:
			break;
		}

		std::cout << bst << std::endl;
	}
}
