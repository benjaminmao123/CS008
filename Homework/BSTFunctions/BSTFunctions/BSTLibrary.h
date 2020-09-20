#pragma once

#include <iostream>

template <typename T>
struct tree_node 
{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;

    int balance_factor() 
    {
        //balance factor = height of the right subtree 
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0

        
    }

    int height()
    {
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)
    }

    int update_height() 
    {
        //set the _height member variable (call height();)
    }

    tree_node(T item = T(), tree_node* left = NULL,
              tree_node* right = NULL) :
        _item(item), _left(left), _right(right)
    {

        //don't forget to set the _height.
    }

    friend std::ostream& operator<<(std::ostream& outs,
                                    const tree_node<T>& t_node) 
    {
        outs << "|" << t_node._item << "|";

        return outs;
    }
};

template <typename T>
void tree_insert(tree_node<T>*& root, const T& insert_me);

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target);

template <typename T>
bool tree_search(tree_node<T>* root, const T& target,
                 tree_node<T>*& found_ptr);

template<typename T>
void tree_print(tree_node<T>* root, int level = 0,
                std::ostream& outs = std::cout);

//prints detailes info about each node
template<typename T>       
void tree_print_debug(tree_node<T>* root, int level = 0,
                      std::ostream& outs = std::cout);

//clear the tree
template <typename T>       
void tree_clear(tree_node<T>*& root);

//erase target from the tree
template <typename T>       
bool tree_erase(tree_node<T>*& root, const T& target);

//erase rightmost node from the tree
// store the item in max_value
template <typename T>       
void tree_remove_max(tree_node<T>*& root, T& max_value); 

//return copy of tree pointed to by root
template <typename T>       
tree_node<T>* tree_copy(tree_node<T>* root);

//Add tree src to dest
template <typename T>       
void tree_add(tree_node<T>*& dest, const tree_node<T>* src);

//sorted array -> tree
template <typename T>       
tree_node<T>* tree_from_sorted_list(const T* a, int size);