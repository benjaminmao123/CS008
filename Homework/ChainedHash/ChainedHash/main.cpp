/*
 * Author: Benjamin Mao
 * Project: Heap
 * Purpose: Driver
 *
 * Notes: None.
 */

#include <iostream>
#include <cctype>
#include <random>

#include "ChainedHash.h"

void Test();

int main()
{
	Test();

	return 0;
}

void Test()
{
	char input = '\0';
	chained_hash<int> ht;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1000);

	while (input != 'x')
	{
		std::cout << "[R]andom [I]nsert [D]elete [S]earch E[x]it: ";
		std::cin >> input;

		switch (tolower(input))
		{
		case 'r':
		{
			int key = dist(gen), value = dist(gen);
			std::cout << "Insert: " << "(" << key << ", " 
				      << value << ")" << std::endl;

			ht.insert(record<int>(key, value));
			break;
		}
		case 'i':
		{
			int key, value;
			std::cout << "Insert" << std::endl;
			std::cout << "Key: ";
			std::cin >> key;
			std::cout << "Value: ";
			std::cin >> value;
			std::cout << "Insert: " << "(" << key << ", "
				<< value << ")" << std::endl;
			ht.insert(record<int>(key, value));
			break;
		}
		case 'd':
		{
			if (!ht.empty())
			{
				int item;
				std::cout << "Delete: ";
				std::cin >> item;
				
				if (ht.remove(item))
					std::cout << "Deleted: " << item << std::endl;
				else
					std::cout << item << " does not exist." << std::endl;
			}
			break;
		}
		case 's':
		{
			int item;
			std::cout << "Search: ";
			std::cin >> item;

			if (ht.is_present(item))
				std::cout << "Found: " << item << std::endl;
			else
				std::cout << item << " not found." << std::endl;
			break;
		}
		case 'x':
			return;
		default:
			break;
		}

		std::cout << ht << std::endl;
	}
}