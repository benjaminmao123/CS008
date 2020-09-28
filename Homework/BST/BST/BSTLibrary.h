/*
 * Author: Benjamin Mao
 * Project: BST Functions
 * Purpose: Functions to implement BST
 *
 * Notes: None.
 */

#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
struct tree_node 
{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;

    int balance_factor()
    {
        //root->balance_factor() factor = height of the right subtree 
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        if (_left && _right)
            return _left->_height - _right->_height;
        else if (_left)
            return _left->_height - -1;
        else if (_right)
            return -1 - _right->_height;

        return 0;
    }

    int height()
    {
        // Height of a root is 1 + height of the "taller" child
        //A leaf root has a height of zero: 1 + max(-1,-1)
        if (_left && _right)
            return std::max(_left->_height, _right->_height) + 1;
        else if (_left)
            return _left->_height + 1;
        else if (_right)
            return _right->_height + 1;

        return 0;
    }

    int update_height() 
    {
        //set the _height member variable (call height();)
        _height = height();

        return _height;
    }

    tree_node(T item = T(), tree_node* left = NULL,
              tree_node* right = NULL) :
        _item(item), _left(left), _right(right), _height(0)
    {

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
template <typename T>
void tree_print_inorder(tree_node<T>* root,
                        std::ostream& outs = std::cout);
template <typename T>
void tree_print_preorder(tree_node<T>* root,
                         std::ostream& outs = std::cout);
template <typename T>
void tree_print_postorder(tree_node<T>* root,
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
template <typename T>
void tree_remove_min(tree_node<T>*& root, T& min_value);

//return copy of tree pointed to by root
template <typename T>       
tree_node<T>* tree_copy(tree_node<T>* root);

//Add tree src to dest
template <typename T>       
void tree_add(tree_node<T>*& dest, const tree_node<T>* src);

//sorted array -> tree
template <typename T>       
tree_node<T>* tree_from_sorted_list(const T* a, int size);
template <typename T>
tree_node<T>* tree_from_sorted_list(const T* a, int l, int r);

template<typename T>
inline void tree_insert(tree_node<T>*& root, const T& insert_me)
{
    if (!root)
    {
        root = new tree_node<T>(insert_me);

        return;
    }

    if (insert_me < root->_item)
        tree_insert(root->_left, insert_me);
    else if (insert_me > root->_item)
        tree_insert(root->_right, insert_me);
    else
        return;

    root->update_height();
}

template<typename T>
inline tree_node<T>* tree_search(tree_node<T>* root, const T& target)
{
    if (!root)
        return nullptr;

    if (target == root->_item)
        return root;
    else if (target < root->_item)
        return tree_search(root->_left, target);

    return tree_search(root->_right, target);
}

template<typename T>
inline bool tree_search(tree_node<T>* root, const T& target, tree_node<T>*& found_ptr)
{
    found_ptr = tree_search(root, target);

    return found_ptr;
}

template<typename T>
inline void tree_print(tree_node<T>* root, int level, std::ostream& outs)
{ 
    if (!root)
    {
        std::cout << "Tree is empty" << std::endl;
        
        return;
    }

    if (root->_right)
        tree_print(root->_right, level + 5, outs);

    outs << std::endl;
    for (int i = 0; i < level; ++i)
        outs << " ";
    outs << "{" << root->_item << "}" << std::endl;
    
    if (root->_left)
        tree_print(root->_left, level + 5, outs);
}

template<typename T>
inline void tree_print_debug(tree_node<T>* root, int level, std::ostream& outs)
{
    if (!root)
    {
        std::cout << "Tree is empty" << std::endl;

        return;
    }

    if (root->_right)
        tree_print_debug(root->_right, level + 5, outs);

    outs << std::endl;
    for (int i = 0; i < level; ++i)
        outs << " ";
    outs << "[H: " << root->_height <<
        ", B: " << root->balance_factor() << "]" <<
        "{" << root->_item << "}" << std::endl;

    if (root->_left)
        tree_print_debug(root->_left, level + 5, outs);
}

template<typename T>
inline void tree_print_inorder(tree_node<T>* root, std::ostream& outs)
{
    if (!root)
        return;

    tree_print_inorder(root->_left, outs);
    outs << "{" << root->_item << "}" << std::endl;
    tree_print_inorder(root->_right, outs);
}

template<typename T>
inline void tree_print_preorder(tree_node<T>* root, std::ostream& outs)
{
    if (!root)
        return;

    outs << "{" << root->_item << "}" << std::endl;
    tree_print_inorder(root->_left, outs);
    tree_print_inorder(root->_right, outs);
}

template<typename T>
inline void tree_print_postorder(tree_node<T>* root, std::ostream& outs)
{
    if (!root)
        return;

    tree_print_inorder(root->_left, outs);
    tree_print_inorder(root->_right, outs);
    outs << "{" << root->_item << "}" << std::endl;
}

template<typename T>
inline void tree_clear(tree_node<T>*& root)
{
    if (!root)
        return;

    tree_clear(root->_left);
    tree_clear(root->_right);

    delete root;
    root = nullptr;
}

template<typename T>
inline bool tree_erase(tree_node<T>*& root, const T& target)
{
    if (!root)
        return false;

    if (target < root->_item)
        tree_erase(root->_left, target);
    else if (target > root->_item)
        tree_erase(root->_right, target);
    else
    {
        if (!root->_left)
        {
            tree_node<T>* temp = root->_right;
            delete root;
            root = temp;
        }
        else
        {
            T value;
            tree_remove_max(root->_left, value);
            root->_item = value;
        }
    }

    if (root)
        root->update_height();

    return true;
}

template<typename T>
inline void tree_remove_max(tree_node<T>*& root, T& max_value)
{
    if (!root)
        return;

    if (root->_right)
        tree_remove_max(root->_right, max_value);
    else
    {
        max_value = root->_item;
        tree_node<T>* left = root->_left;
        delete root;
        root = left;
    }

    if (root)
        root->update_height();
}

template<typename T>
inline void tree_remove_min(tree_node<T>*& root, T& min_value)
{
    if (!root)
        return;

    if (root->_left)
        tree_remove_min(root->_left, min_value);
    else
    {
        min_value = root->_item;
        tree_node<T>* right = root->_right;
        delete root;
        root = right;
    }

    if (root)
        root->update_height();
}

template<typename T>
inline tree_node<T>* tree_copy(tree_node<T>* root)
{
    if (!root)
        return nullptr;

    tree_node<T>* newNode = new tree_node<T>(root->_item);

    newNode->_height = root->_height;

    newNode->_left = tree_copy(root->_left);
    newNode->_right = tree_copy(root->_right);

    return newNode;
}

template<typename T>
inline void tree_add(tree_node<T>*& dest, const tree_node<T>* src)
{
    if (!src)
        return;

    tree_insert(dest, src->_item);

    tree_add(dest, src->_left);
    tree_add(dest, src->_right);
}

template<typename T>
inline tree_node<T>* tree_from_sorted_list(const T* a, int size)
{
    tree_node<T>* root = tree_from_sorted_list(a, 0, size - 1);

    root->update_height();

    return root;
}

template<typename T>
inline tree_node<T>* tree_from_sorted_list(const T* a, int l, int r)
{
    if (l > r)
        return nullptr;

    int mid = l + (r - l) / 2;

    tree_node<T>* root = new tree_node<T>(a[mid]);

    root->_left = tree_from_sorted_list(a, l, mid - 1);
    root->_right = tree_from_sorted_list(a, mid + 1, r);

    return root;
}
