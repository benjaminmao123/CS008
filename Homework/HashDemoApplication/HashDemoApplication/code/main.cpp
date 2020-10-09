#include <iostream>
#include <random>
#include <cctype>
#include <string>
#include <typeinfo>
#include <unordered_map>

#include "ChainedHash.h"
#include "OpenHash.h"

void test_hash_table_interactive(open_hash<int>& ht, const std::string& type);
void test_hash_table_interactive(chained_hash<int>& ht, const std::string& type);
void test_hash_table_random(open_hash<int>& ht, int numElements, const std::string& type);
void test_hash_table_random(chained_hash<int>& ht, int numElements, const std::string& type);

int main()
{
    std::cout << std::endl << std::endl << std::endl << "----------------------" << std::endl << std::endl << std::endl;
    const bool RANDOM_CHAINED = true;
    const bool RANDOM_OPEN = true;
    const bool INTERACTIVE_OPEN = true;
    const bool INTERACTIVE_CHAINED = true;

	LinearProbing lp;
	QuadraticProbing qp;
	DoubleHashing dh;

    if (INTERACTIVE_OPEN)
    {
        std::cout << "-------  INTERACTIVE TESTS ---------------------------" << std::endl;
        open_hash<int> open(dh);
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
        open_hash<int> h_table(dh);
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

	std::cout << typeid(ht).name() << std::endl;

	while (input != 'x')
	{
		std::cout << "[S]ize [R]andom [I]nsert [D]elete [F]ind [E]xists E[x]it: ";
		std::cin >> input;

		switch (tolower(input))
		{
		case 's':
			std::cout << "Size: " << ht.size() << std::endl;
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
				int key;
				std::cout << "Delete: ";
				std::cin >> key;

				if (ht.remove(key))
					std::cout << "Deleted: " << key << std::endl;
				else
					std::cout << key << " does not exist." << std::endl;
			}
			break;
		}
		case 'f':
		{
			int key;
			std::cout << "Find: ";
			std::cin >> key;

			HTLibrary::record<int> rec;

			if (ht.find(key, rec))
				std::cout << "Found: " << rec << std::endl;
			else
				std::cout << key << " not found." << std::endl;
			break;
		}
		case 'e':
			int key;
			std::cout << "Find: ";
			std::cin >> key;

			if (ht.is_present(key))
				std::cout << "Found: " << key << std::endl;
			else
				std::cout << key << " not found." << std::endl;
			break;
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

	std::cout << typeid(ht).name() << std::endl;

	while (input != 'x')
	{
		std::cout << "[S]ize [R]andom [I]nsert [D]elete [F]ind [E]xists E[x]it: ";
		std::cin >> input;

		switch (tolower(input))
		{
		case 's':
			std::cout << "Size: " << ht.size() << std::endl;
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
				int key;
				std::cout << "Delete: ";
				std::cin >> key;

				if (ht.remove(key))
					std::cout << "Deleted: " << key << std::endl;
				else
					std::cout << key << " does not exist." << std::endl;
			}
			break;
		}
		case 'f':
		{
			int key;
			std::cout << "Find: ";
			std::cin >> key;

			HTLibrary::record<int> rec;

			if (ht.find(key, rec))
				std::cout << "Found: " << rec << std::endl;
			else
				std::cout << key << " not found." << std::endl;
			break;
		}
		case 'e':
			int key;
			std::cout << "Find: ";
			std::cin >> key;

			if (ht.is_present(key))
				std::cout << "Found: " << key << std::endl;
			else
				std::cout << key << " not found." << std::endl;
			break;
		case 'x':
			return;
		default:
			break;
		}

		std::cout << std::endl << ht << std::endl;
	}
}

void test_hash_table_random(open_hash<int>& ht, int numElements, const std::string& type)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 10000);

	Vector<HTLibrary::record<int>> records;

	for (int i = 0; i < numElements; ++i)
		records.push_back(HTLibrary::record<int>(dist(rd), dist(rd)));

	for (const auto& i : records)
		ht.insert(i);

	std::cout << "********************************************************************************" << std::endl;
	std::cout << "R A N D O M   H A S H   T E S T : " << type << std::endl;
	std::cout << "********************************************************************************" << std::endl;
	std::cout << "---- [" << numElements << "]" << " keys inserted." << std::endl << std::endl;

	std::cout << "---------Search for existing keys----------------" << std::endl;
	std::cout << "Search for existing keys : " << numElements / 2 << " keys to be tested : " << std::endl;

	int foundRecords = 0, notFoundRecords = 0;
	int searchSize = numElements / 2;
	std::uniform_int_distribution<> dist2(0, searchSize);

	for (int i = 0; i < searchSize; ++i)
	{
		int key = records[dist2(rd)]._key;

		if (ht.is_present(key))
			++foundRecords;
		else
			++notFoundRecords;
	}

	std::cout << "EXISTING KEYS LOOKUP : VERIFIED. EXISTING KEYS EXAMINED : " << foundRecords << std::endl;

	std::cout << "------------------ END RANDOM TEST ----------------------" << std::endl;
}

void test_hash_table_random(chained_hash<int>& ht, int numElements, const std::string& type)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 10000);

	Vector<HTLibrary::record<int>> records;

	for (int i = 0; i < numElements; ++i)
		records.push_back(HTLibrary::record<int>(dist(rd), dist(rd)));

	for (const auto& i : records)
		ht.insert(i);

	std::cout << "********************************************************************************" << std::endl;
	std::cout << "R A N D O M   H A S H   T E S T : " << type << std::endl;
	std::cout << "********************************************************************************" << std::endl;
	std::cout << "---- [" << numElements << "]" << " keys inserted." << std::endl << std::endl;

	std::cout << "---------Search for existing keys----------------" << std::endl;
	std::cout << "Search for existing keys : " << numElements / 2 << " keys to be tested : " << std::endl;

	int foundRecords = 0, notFoundRecords = 0;
	int searchSize = numElements / 2;
	std::uniform_int_distribution<> dist2(0, searchSize);

	for (int i = 0; i < searchSize; ++i)
	{
		int key = records[dist2(rd)]._key;

		if (ht.is_present(key))
			++foundRecords;
		else
			++notFoundRecords;
	}

	std::cout << "EXISTING KEYS LOOKUP : VERIFIED. EXISTING KEYS EXAMINED : " << foundRecords << std::endl;

	std::cout << "------------------ END RANDOM TEST ----------------------" << std::endl;
}
