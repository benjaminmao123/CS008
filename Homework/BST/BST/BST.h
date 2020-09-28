/*
 * Author: Benjamin Mao
 * Project: BST
 * Purpose: BST class
 *
 * Notes: None.
 */

#pragma once

#include "BSTLibrary.h"

#include <algorithm>
#include <iostream>

template <typename T>
class BST {
public:
    BST();
    BST(const T* sorted_list, int size = -1);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    BST(const BST<T>& copy_me);
    BST<T>& operator =(const BST<T>& rhs);
    ~BST();

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    void insert(const T& insert_me);
    void erase(const T& target);
    bool search(const T& target, tree_node<T>*& found_ptr);
    void swap(BST<T>& tree);
    void clear();

    template <typename U>
    friend std::ostream& operator<<(std::ostream& outs, const BST<U>& tree);
    BST<T>& operator +=(const BST<T>& rhs);

private:
    tree_node<T>* root;
};

template<typename T>
inline BST<T>::BST() :
    root(nullptr)
{

}

template<typename T>
inline BST<T>::BST(const T* sorted_list, int size) :
    root(tree_from_sorted_list(sorted_list, size))
{

}

template<typename T>
inline BST<T>::BST(const BST<T>& copy_me) :
    root(tree_copy(copy_me.root))
{

}

template<typename T>
inline BST<T>& BST<T>::operator=(const BST<T>& rhs)
{
    BST<T> temp(rhs);
    swap(temp);

    return *this;
}

template<typename T>
inline BST<T>::~BST()
{
    clear();
}

template<typename T>
inline void BST<T>::insert(const T& insert_me)
{
    tree_insert(root, insert_me);
}

template<typename T>
inline void BST<T>::erase(const T& target)
{
    if (!tree_erase(root, target))
    {
        std::cout << "Item does not exist." << std::endl;
        return;
    }
}

template<typename T>
inline bool BST<T>::search(const T& target, tree_node<T>*& found_ptr)
{
    return tree_search(root, target, found_ptr);
}

template<typename T>
inline void BST<T>::swap(BST<T>& tree)
{
    std::swap(root, tree.root);
}

template<typename T>
inline void BST<T>::clear()
{
    tree_clear(root);
}

template<typename T>
inline BST<T>& BST<T>::operator+=(const BST<T>& rhs)
{
    tree_add(root, rhs.root);

    return *this;
}

template <typename U>
std::ostream& operator<<(std::ostream& outs, const BST<U>& tree)
{
    tree_print(tree.root, 0, outs);

    return outs;
}