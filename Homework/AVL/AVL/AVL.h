#pragma once

#include "BSTLibrary.h"

#include <iostream>
#include <algorithm>

template <typename T>
class AVL 
{
public:
    AVL();
    AVL(const T* sorted_list, int size = -1);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    AVL(const AVL<T>& copy_me);
    AVL<T>& operator=(const AVL<T>& rhs);
    ~AVL();

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    void insert(const T& insert_me);
    void erase(const T& target);
    bool search(const T& target, tree_node<T>*& found_ptr);
    void swap(AVL<T>& other);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& outs, const AVL<U>& tree);
    AVL<T>& operator+=(const AVL<T>& rhs);

private:
    tree_node<T>* root;
};

template<typename T>
inline AVL<T>::AVL() :
    root(nullptr)
{

}

template<typename T>
inline AVL<T>::AVL(const T* sorted_list, int size) :
    root(tree_from_sorted_list(sorted_list, size))
{

}

template<typename T>
inline AVL<T>::AVL(const AVL<T>& copy_me) :
    root(tree_copy(copy_me.root))
{

}

template<typename T>
inline AVL<T>& AVL<T>::operator=(const AVL<T>& rhs)
{
    AVL<T> temp(rhs);
    swap(temp);

    return *this;
}

template<typename T>
inline AVL<T>::~AVL()
{
    tree_clear(root);
}

template<typename T>
inline void AVL<T>::insert(const T& insert_me)
{
    tree_insert(root, insert_me);
}

template<typename T>
inline void AVL<T>::erase(const T& target)
{
    if (!tree_erase(root, target))
    {
        std::cout << "Item does not exist." << std::endl;
        return;
    }
}

template<typename T>
inline bool AVL<T>::search(const T& target, tree_node<T>*& found_ptr)
{
    return tree_search(root, target, found_ptr);
}

template<typename T>
inline void AVL<T>::swap(AVL<T>& other)
{
    std::swap(root, other.root);
}

template<typename T>
inline AVL<T>& AVL<T>::operator+=(const AVL<T>& rhs)
{
    tree_add(root, rhs.root);

    return *this;
}

template<typename U>
inline std::ostream& operator<<(std::ostream& outs, const AVL<U>& tree)
{
    tree_print_debug(tree.root, 0, outs);

    return outs;
}
