/*
 * Author: Benjamin Mao
 * Project: BST Functions
 * Purpose: Driver
 *
 * Notes: None.
 */

#include "BSTLibrary.h"

#include <iostream>

void Test();
void TestInsert(tree_node<int>*& root);
void TestErase(tree_node<int>* root);
tree_node<int>* TestCopy(tree_node<int>* root);
void TestSearch(tree_node<int>* root);
void TestClear(tree_node<int>*& root);

int main()
{
    //Test();

    tree_node<int>* root = nullptr;

    tree_insert(root, 20);
    tree_insert(root, 22);
    tree_insert(root, 7);
    tree_insert(root, 5);
    tree_insert(root, 9);
    tree_insert(root, 8);

    tree_print(root);

    std::cout << std::endl;

    tree_erase(root, 7);
    tree_print(root);

	return 0;
}

void Test()
{
    tree_node<int>* root = nullptr;

    TestInsert(root);
    tree_node<int> *copy = TestCopy(root);
    TestSearch(root);
    TestErase(root);
    TestClear(copy);
}

void TestInsert(tree_node<int>*& root)
{
    std::cout << "Insert 5" << std::endl;
    tree_insert(root, 5);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 10" << std::endl;
    tree_insert(root, 10);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 2" << std::endl;
    tree_insert(root, 2);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 4" << std::endl;
    tree_insert(root, 4);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 50" << std::endl;
    tree_insert(root, 50);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 7" << std::endl;
    tree_insert(root, 7);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 12" << std::endl;
    tree_insert(root, 12);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 1" << std::endl;
    tree_insert(root, 1);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Insert 3" << std::endl;
    tree_insert(root, 3);
    tree_print(root);
    std::cout << std::endl;
}

void TestErase(tree_node<int>* root)
{
    std::cout << "Erase 5" << std::endl;
    tree_erase(root, 5);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 10" << std::endl;
    tree_erase(root, 10);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 2" << std::endl;
    tree_erase(root, 2);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 4" << std::endl;
    tree_erase(root, 4);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 50" << std::endl;
    tree_erase(root, 50);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 7" << std::endl;
    tree_erase(root, 7);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 12" << std::endl;
    tree_erase(root, 12);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 1" << std::endl;
    tree_erase(root, 1);
    tree_print(root);
    std::cout << std::endl;

    std::cout << "Erase 3" << std::endl;
    tree_erase(root, 3);
    tree_print(root);
    std::cout << std::endl;
}

tree_node<int>* TestCopy(tree_node<int>* root)
{
    tree_node<int>* copy = nullptr;

    std::cout << "Original: " << std::endl;
    tree_print(root);
    std::cout << std::endl;

    copy = tree_copy(root);

    std::cout << "Copy: " << std::endl;
    tree_print(copy);
    std::cout << std::endl;

    return copy;
}

void TestSearch(tree_node<int>* root)
{
    std::cout << "Search 1" << std::endl;
    tree_search(root, 1);
    tree_print(root);
    std::cout << "Found" << std::endl;;

    std::cout << "Search 1000" << std::endl;
    tree_search(root, 1000);
    tree_print(root);
    std::cout << "Not Found" << std::endl;
}

void TestClear(tree_node<int>*& root)
{
    std::cout << "Clear" << std::endl;
    tree_clear(root);
    tree_print(root);
}
