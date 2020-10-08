#include <iostream>
#include <random>
#include <cctype>
#include <string>
#include <typeinfo>

#include "ChainedHash.h"
#include "OpenHash.h"

void test_hash_table_interactive(open_hash<int>& ht, const std::string& type);
void test_hash_table_interactive(chained_hash<int>& ht, const std::string& type);
void test_hash_table_random(open_hash<int>& ht, int numElements, const std::string& type);
void test_hash_table_random(chained_hash<int>& ht, int numElements, const std::string& type);

int main()
{
    std::cout << std::endl << std::endl << std::endl << "----------------------" << std::endl << std::endl << std::endl;
    const bool RANDOM_CHAINED = false;
    const bool RANDOM_OPEN = false;
    const bool INTERACTIVE_OPEN = false;
    const bool INTERACTIVE_CHAINED = false;

	LinearProbing lp;
	QuadraticProbing qp;
	DoubleHashing dh;

    if (INTERACTIVE_OPEN)
    {
        std::cout << "-------  INTERACTIVE TESTS ---------------------------" << std::endl;
        open_hash<int> open(lp);
        test_hash_table_interactive(open, "open_hash_table");
    }

    if (INTERACTIVE_CHAINED)
    {
        std::cout << "-------  INTERACTIVE TESTS ---------------------------" << std::endl;
        chained_hash<int> chained;
        test_hash_table_interactive(chained, "chained_hash_table");
    }

    if (RANDOM_CHAINED)
    {
        //----------- RANDOM TEST ------------------------------
        //. . . . . .  Chained Hash Table . . . . . . . . . . .;
        chained_hash<int> c_table;
        test_hash_table_random(c_table, 2500, "chained_hash_table<record>");
        std::cout << c_table << std::endl;
    }

    if (RANDOM_OPEN)
    {
        //----------- RANDOM TEST ------------------------------
        //. . . . . .  Simple Hash Table . . . . . . . . . . .;
        open_hash<int> h_table(lp);
        test_hash_table_random(h_table, 500, "hash_table<record>");
        std::cout << h_table << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl << "---------------------------------" << std::endl;

	return 0;
}

void test_hash_table_interactive(open_hash<int>& ht, const std::string& type)
{
	char input = '\0';
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1000);

	std::cout << "Table of {int:int}" << std::endl;

	while (input != 'x')
	{
		std::cout << "[S]ize [R]andom [I]nsert [D]elete [F]ind [E]xists E[x]it: ";
		std::cin >> input;

		switch (tolower(input))
		{
		case 's':
			break;
		case 'r':
		{
			int key = dist(gen), value = dist(gen);

			HTLibrary::record<int> rec(key, value);
			std::cout << "Insert: " << rec << std::endl;

			ht.insert(rec);
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

			HTLibrary::record<int> rec(key, value);
			std::cout << "Insert: " << rec << std::endl;

			ht.insert(rec);
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
		case 'f':
		{
			int item;
			std::cout << "Find: ";
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

void test_hash_table_interactive(chained_hash<int>& ht, const std::string& type)
{
	char input = '\0';
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

			ht.insert(HTLibrary::record<int>(key, value));
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
			ht.insert(HTLibrary::record<int>(key, value));
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

void test_hash_table_random(open_hash<int>& ht, int numElements, const std::string& type)
{
	std::cout << "********************************************************************************" << std::endl;
	std::cout << "R A N D O M   H A S H   T E S T : " << type << std::endl;
	std::cout << "********************************************************************************" << std::endl;
	std::cout << "---- [" << numElements << "]" << " keys inserted." << std::endl << std::endl;

	std::cout << "---------Search for existing keys----------------" << std::endl;
	std::cout << "Search for existing keys : 1250 keys to be tested : " << std::endl;
	std::cout << "EXISTING KEYS LOOKUP : VERIFIED.EXISTING KEYS EXAMINED : 1250 " << std::endl;
}

void test_hash_table_random(chained_hash<int>& ht, int numElements, const std::string& type)
{

}
