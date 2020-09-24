#include "BSTLibrary.h"

#include <iostream>

int main()
{
	//tree_node<int>* root = new tree_node<int>(10);

	//tree_insert(root, 5);
	//tree_insert(root, 3);
	//tree_insert(root, 6);
	//tree_insert(root, 4);
	//tree_insert(root, 2);
	//tree_insert(root, 11);
	//tree_insert(root, 1);

	//tree_print_debug(root);

	//tree_erase(root, 3);

	//tree_print_debug(root);

	//tree_node<int>* root2 = tree_copy(root);

	//tree_print(root2);

	int a[] = { 1, 2, 3, 4, 5 };

	tree_node<int> *root = tree_from_sorted_list(a, 5);

	tree_print(root);
	
	tree_clear(root);

	tree_print(root);

	return 0;
}