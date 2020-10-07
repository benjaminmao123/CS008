/*
 * Author: Benjamin Mao
 * Project: Iterated List
 * Purpose: Implements a iterated list data structure using
 *      the Linked List Library.
 *
 * Notes: None.
 */

#pragma once

#include <ostream>
#include <algorithm>

#include "LinkedListLibrary.h"

template <class ITEM_TYPE>
class List
{
public:
    class Iterator 
    {
    public:
        //default ctor
        Iterator() { _ptr = NULL; }     

        //Point Iterator to where p is pointing to
        Iterator(node<ITEM_TYPE> *p) : _ptr(p) { }

        //dereference operator
        ITEM_TYPE &operator*()
        {
            return _ptr->_item;
        }

        const ITEM_TYPE &operator*() const
        {
            return _ptr->_item;
        }

        //member access operator
        ITEM_TYPE *operator->()
        {
            return &_ptr->_item;
        }

        const ITEM_TYPE *operator->() const
        {
            return &_ptr->_item;
        }

        //casting operator: true if _ptr not NULL
        operator bool() const
        {
            return _ptr != nullptr;
        }
        
        //true if left != right
        bool operator!=(const Iterator &rhs) const
        {
            return _ptr != rhs._ptr;
        }

        //true if left == right
        bool operator==(const Iterator &rhs) const
        {
            return _ptr == rhs._ptr;
        }

        //member operator: ++it; or ++it = new_value
        Iterator &operator++()
        {
            _ptr = _ptr->next;

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp(_ptr);
            operator++();

            return temp;
        }

    private:
        //pointer being encapsulated
        node<ITEM_TYPE> *_ptr;                                                  
    };

    //CTOR with default args
    List();
            
    //BIG 3:
    ~List();
    List(const List<ITEM_TYPE> &copyThis);
    List &operator=(const List &RHS);

    //insert at the head of list
    Iterator InsertHead(const ITEM_TYPE &i);
    //insert after marker
    Iterator InsertAfter(const ITEM_TYPE &i, Iterator iMarker);
    //insert before marker
    Iterator InsertBefore(const ITEM_TYPE &i, Iterator iMarker);
    //Insert i in a sorted manner
    Iterator InsertSorted(const ITEM_TYPE &i);                                        
    //delete node pointed to by marker
    ITEM_TYPE Delete(Iterator iMarker);                        
    void Print() const;
    //return Iterator to node [key]
    Iterator Search(const ITEM_TYPE &key) const;           
    //previous node to marker
    Iterator Prev(Iterator iMarker);                                            

    //const version of the operator [ ]
    const ITEM_TYPE &operator[](const int index) const;      
    //return item at position index
    ITEM_TYPE &operator[](const int index);                                           
    //Iterator to the head node
    Iterator begin() const;                     
    //Iterator to NULL
    Iterator end() const;                                       
    //Iterator to the last node
    Iterator LastNode() const;                                                  

    void Swap(List &l);

    //Note the template arg U
    template <class U>                                                          
    friend std::ostream &operator<<(std::ostream &outs, const List<U> &l);

private:
    node<ITEM_TYPE> *_head_ptr;
};

/*
    @summary: Default constructor, initializes head to nullptr.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List()
    : _head_ptr(nullptr)
{

}

/*
    @summary: Destructor, clears list.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::~List()
{
    ClearList(_head_ptr);
}

/*
    @summary: Copy constructor

    @param <const List<ITEM_TYPE> &copyThis>: List to copy.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE>::List(const List<ITEM_TYPE> &copyThis)
    : _head_ptr(CopyList(copyThis._head_ptr))
{

}

/*
    @summary: Overloaded copy assignment operator.

    @param <const List &RHS>: List to copy and assign from.

    @return <List<ITEM_TYPE> &>: Reference to the newly copied list.
*/
template<class ITEM_TYPE>
inline List<ITEM_TYPE> &List<ITEM_TYPE>::operator=(const List &RHS)
{
    List temp(RHS);
    Swap(temp);

    return *this;
}

/*
    @summary: Inserts node at head of the list.

    @param <const ITEM_TYPE &i>: Item to insert.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to node that was inserted.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::InsertHead(const ITEM_TYPE &i)
{
    return Iterator(::InsertHead(_head_ptr, i));
}

/*
    @summary: Inserts node after given node.

    @param <ITEM_TYPE i>: Item to insert.
    @param <Iterator iMarker>: Iterator to node to insert after.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to node that was inserted.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::InsertAfter(const ITEM_TYPE &i, Iterator iMarker)
{
    node<ITEM_TYPE> *mNode = SearchList(_head_ptr, *iMarker);

    return Iterator(::InsertAfter(_head_ptr, mNode, i));
}

/*
    @summary: Inserts node before given node.

    @param <ITEM_TYPE i>: Item to insert.
    @param <Iterator iMarker>: Iterator to node to insert before.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to node that was inserted.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::InsertBefore(const ITEM_TYPE &i, Iterator iMarker)
{
    node<ITEM_TYPE> *mNode = SearchList(_head_ptr, *iMarker);

    return Iterator(::InsertBefore(_head_ptr, mNode, i));
}

/*
    @summary: Inserts an item depending on the sorting order.

    @param <const ITEM_TYPE &i>: Item to insert.

    @return <List<ITEM_TYPE>::Iterator>: Returns iterator to the newly inserted item.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::InsertSorted(const ITEM_TYPE &i)
{
    return Iterator(::InsertSorted(_head_ptr, i));
}

/*
    @summary: Deletes a given node.

    @param <Iterator iMarker>: Iterator to the node to delete.

    @return <ITEM_TYPE>: Returns the item of the deleted node.
*/
template<class ITEM_TYPE>
inline ITEM_TYPE List<ITEM_TYPE>::Delete(Iterator iMarker)
{
    if (!iMarker)
    {
        throw std::invalid_argument("iMarker contained nullptr");
    }

    node<ITEM_TYPE> *mNode = SearchList(_head_ptr, *iMarker);
    ITEM_TYPE item = DeleteNode(_head_ptr, mNode);

    return item;
}

/*
    @summary: Prints the contents of the list.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Print() const
{
    PrintList(_head_ptr);
}

/*
    @summary: Searches the list for a given key.

    @param <const ITEM_TYPE &key>: Key to search for.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the node containing the item.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Search(const ITEM_TYPE &key) const
{
    return Iterator(SearchList(_head_ptr, key));
}

/*
    @summary: Gets the previous node of a given node.

    @param <Iterator iMarker>: Iterator to the node to get previous node of.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the previous node.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::Prev(Iterator iMarker)
{
    auto prev = begin();
    node<ITEM_TYPE> *mNode = nullptr;

    for (auto curr = begin(); curr != end(); ++curr)
    {
        if (curr == iMarker)
        {
            return prev;
        }

        prev = curr;
    }

    return end();
}

/*
    @summary: Gets the item at the given index.

    @param <int index>: Index of the item in the list.

    @return <const ITEM_TYPE &>: const Reference to the item.
*/
template<class ITEM_TYPE>
inline const ITEM_TYPE &List<ITEM_TYPE>::operator[](const int index) const
{
    return At(_head_ptr, index);
}

/*
    @summary: Gets the item at the given index.

    @param <int index>: Index of the item in the list.

    @return <ITEM_TYPE &>: Reference to the item.
*/
template<class ITEM_TYPE>
inline ITEM_TYPE &List<ITEM_TYPE>::operator[](const int index)
{
    return At(_head_ptr, index);
}

/*
    @summary: Gets the head node of the list.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the head node.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::begin() const
{
    return Iterator(_head_ptr);
}

/*
    @summary: Gets the element after the last element in the list.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to nullptr.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::end() const
{
    return Iterator(nullptr);
}

/*
    @summary: Gets the tail node of the list.

    @return <List<ITEM_TYPE>::Iterator>: Iterator to the tail node.
*/
template<class ITEM_TYPE>
inline typename List<ITEM_TYPE>::Iterator List<ITEM_TYPE>::LastNode() const
{
    return Iterator(::LastNode(_head_ptr));
}

/*
    @summary: Swaps the current list with another list.

    @param <List &l>: List to swap with.
*/
template<class ITEM_TYPE>
inline void List<ITEM_TYPE>::Swap(List &l)
{
    std::swap(_head_ptr, l._head_ptr);
}

/*
    @summary: Overloaded stream insertion operator.

    @param <std::ostream &outs>: The ostream object.
    @param <const List<U> &l>: List to print contents of.

    @return <std::ostream &>: Reference to the ostream object.
*/
template<class U>
inline std::ostream &operator<<(std::ostream &outs, const List<U> &l)
{
    for (auto i : l)
    {
        outs << i << " ";
    }

    return outs;
}
