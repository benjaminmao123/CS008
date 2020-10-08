/*
 * Author: Benjamin Mao
 * Project: AVL
 * Purpose: AVL class
 *
 * Notes: None.
 */

#pragma once

#include "AVLLibrary.h"
#include "Stack.h"

#include <iostream>
#include <algorithm>

template <typename T>
class AVL
{
public:
    class Iterator
    {
    public:
        Iterator() { }

        Iterator(AVLLibrary::tree_node<T>* ptr) :
            curr(ptr)
        {
            NextInorder();
            SetNext();
        }

        //dereference operator
        T& operator*()
        {
            return curr->_item;
        }

        const T& operator*() const
        {
            return curr->_item;
        }

        //member access operator
        T* operator->()
        {
            return &curr->_item;
        }

        const T* operator->() const
        {
            return &curr->_item;
        }

        //true if left != right
        bool operator!=(const Iterator& rhs) const
        {
            return curr != rhs.curr;
        }

        //true if left == right
        bool operator==(const Iterator& rhs) const
        {
            return curr == rhs.curr;
        }

        //member operator: ++it; or ++it = new_value
        Iterator& operator++()
        {
            if (curr)
            {
                if (curr->_right)
                {
                    curr = stack.pop()->_right;

                    NextInorder();
                    SetNext();
                }
                else
                {
                    if (!stack.empty())
                        stack.pop();

                    SetNext();
                }
            }

            return *this;
        }

    private:
        void NextInorder()
        {
            while (curr)
            {
                stack.push(curr);
                curr = curr->_left;
            }
        }

        void SetNext()
        {
            if (!stack.empty())
                curr = stack.top();
            else
                curr = nullptr;
        }

        AVLLibrary::tree_node<T>* curr;
        Stack<AVLLibrary::tree_node<T>*> stack;
    };

    AVL();
    AVL(const T* sorted_list, int size = -1);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    AVL(const AVL<T>& copy_me);
    AVL<T>& operator=(const AVL<T>& rhs);
    ~AVL();

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    Iterator begin() const;
    Iterator end() const;

    void insert(const T& insert_me);
    void erase(const T& target);
    bool search(const T& target, AVLLibrary::tree_node<T>*& found_ptr);
    void swap(AVL<T>& other);
    void clear();
    bool is_valid() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& outs, const AVL<U>& tree);
    AVL<T>& operator+=(const AVL<T>& rhs);

private:
    AVLLibrary::tree_node<T>* root;
};

template<typename T>
inline AVL<T>::AVL() :
    root(nullptr)
{

}

template<typename T>
inline AVL<T>::AVL(const T* sorted_list, int size) :
    root(AVLLibrary::tree_from_sorted_list(sorted_list, size))
{

}

template<typename T>
inline AVL<T>::AVL(const AVL<T>& copy_me) :
    root(AVLLibrary::tree_copy(copy_me.root))
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
    AVLLibrary::tree_clear(root);
}

template<typename T>
inline typename AVL<T>::Iterator AVL<T>::begin() const
{
    return Iterator(root);
}

template<typename T>
inline typename AVL<T>::Iterator AVL<T>::end() const
{
    return Iterator(nullptr);
}

template<typename T>
inline void AVL<T>::insert(const T& insert_me)
{
    AVLLibrary::tree_insert(root, insert_me);
}

template<typename T>
inline void AVL<T>::erase(const T& target)
{
    if (!AVLLibrary::tree_erase(root, target))
    {
        std::cout << "Item does not exist." << std::endl;

        return;
    }
}

template<typename T>
inline bool AVL<T>::search(const T& target, AVLLibrary::tree_node<T>*& found_ptr)
{
    return AVLLibrary::tree_search(root, target, found_ptr);
}

template<typename T>
inline void AVL<T>::swap(AVL<T>& other)
{
    std::swap(root, other.root);
}

template<typename T>
inline void AVL<T>::clear()
{
    AVLLibrary::tree_clear(root);
}

template<typename T>
inline bool AVL<T>::is_valid() const
{
    return AVLLibrary::is_valid(root);
}

template<typename T>
inline AVL<T>& AVL<T>::operator+=(const AVL<T>& rhs)
{
    AVLLibrary::tree_add(root, rhs.root);

    return *this;
}

template<typename U>
inline std::ostream& operator<<(std::ostream& outs, const AVL<U>& tree)
{
    AVLLibrary::tree_print(tree.root, 0, outs);

    return outs;
}
