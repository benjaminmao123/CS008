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
inline AVL<T>::AVL()
{

}

template<typename T>
inline AVL<T>::AVL(const T* sorted_list, int size)
{

}

template<typename T>
inline AVL<T>::AVL(const AVL<T>& copy_me)
{

}

template<typename T>
inline AVL<T>& AVL<T>::operator=(const AVL<T>& rhs)
{
    return *this;
}

template<typename T>
inline AVL<T>::~AVL()
{

}

template<typename T>
inline void AVL<T>::insert(const T& insert_me)
{

}

template<typename T>
inline void AVL<T>::erase(const T& target)
{

}

template<typename T>
inline bool AVL<T>::search(const T& target, tree_node<T>*& found_ptr)
{
    return false;
}

template<typename T>
inline void AVL<T>::swap(AVL<T>& other)
{

}

template<typename T>
inline AVL<T>& AVL<T>::operator+=(const AVL<T>& rhs)
{
    return *this;
}

template<typename U>
inline std::ostream& operator<<(std::ostream& outs, const AVL<U>& tree)
{
    return outs;
}
