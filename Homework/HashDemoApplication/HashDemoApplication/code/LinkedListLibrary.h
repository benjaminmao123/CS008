/*
 * Author: Benjamin Mao
 * Project: Linked List Functions
 * Purpose: Provide easy access to linked list functions
 *      to act as an API for developing list classes.
 *
 * Notes: None.
 */

#pragma once

#include <iostream>
#include <cassert>

template <typename ITEM_TYPE>
struct node
{
public:
    /*
        @summary: Default constructor for node. Initializes item to default
            value and next to nullptr.
    */
    node()
        : _item(), next(nullptr), prev(nullptr)
    {

    }

    /*
        @summary: Overloaded constructor. Initializes item to a given item and
            next to nullptr.

        @param <const ITEM_TYPE &item>: Item to initialize member variable.
    */
    node(const ITEM_TYPE& item)
        : _item(item), next(nullptr), prev(nullptr)
    {

    }

    /*
        @summary: Overloaded insertion operator to print contents of node.

        @param <std::ostream &outs>: The ostream object.
        @param <const node<T> &printMe>: The node to print.

        @return <std::ostream &>: ostream reference.
    */
    friend std::ostream& operator<<(std::ostream& outs, const node<ITEM_TYPE>& printMe)
    {
        outs << printMe._item;

        return outs;
    }

    ITEM_TYPE _item;
    node* next;
    node* prev;
};

//Linked List General Functions:
template <typename ITEM_TYPE>
void PrintList(const node<ITEM_TYPE>* head);

template <typename ITEM_TYPE>
void PrintList_backwards(const node<ITEM_TYPE>* head,       //recursive fun! :)
                         const int depth);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* SearchList(node<ITEM_TYPE>* head,          //return ptr to key or NULL
                            const ITEM_TYPE& key);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* InsertHead(node<ITEM_TYPE>*& head,         //insert at the head of list
                            const ITEM_TYPE& insertThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* InsertAfter(node<ITEM_TYPE>*& head,        //insert after ptr
                             node<ITEM_TYPE>* afterThis,
                             const ITEM_TYPE& insertThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* InsertBefore(node<ITEM_TYPE>*& head,       //insert before ptr
                              const node<ITEM_TYPE>* beforeThis,
                              const ITEM_TYPE& insertThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* PreviousNode(node<ITEM_TYPE>* head,        //ptr to previous node
                              const node<ITEM_TYPE>* prevToThis);

template <typename ITEM_TYPE>
ITEM_TYPE DeleteNode(node<ITEM_TYPE>*& head,                //delete, return item
                     node<ITEM_TYPE>* deleteThis);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* CopyList(node<ITEM_TYPE>* head);           //duplicate the list...

template <typename ITEM_TYPE>
void ClearList(node<ITEM_TYPE>*& head);                     //delete all the nodes

template <typename ITEM_TYPE>
ITEM_TYPE& At(node<ITEM_TYPE>* head, const int pos);        //_item at this position

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* InsertSorted(node<ITEM_TYPE>*& head,           //insert
                              const ITEM_TYPE& item,
                              const bool ascending = true);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* InsertSorted_and_add(node<ITEM_TYPE>*& head,   //insert or add if a dup
                                      const ITEM_TYPE& item,
                                      const bool ascending = true);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* WhereThisGoes(node<ITEM_TYPE>* head,           //node after which this
                               const ITEM_TYPE& item,                                      //    item goes
                               const bool ascending = true);                               //order: 0 ascending

template <typename ITEM_TYPE>
node<ITEM_TYPE>* LastNode(node<ITEM_TYPE>* head);               //Last Node in the list

/*
    @summary: Prints the list forwards

    @param <const node<ITEM_TYPE> *head>: The head of the list.
*/
template<typename ITEM_TYPE>
inline void PrintList(const node<ITEM_TYPE>* head)
{
    using std::cout;
    using std::endl;

    if (head)
    {
        for (const node<ITEM_TYPE>* i = head; i != nullptr; i = i->next)
        {
            if (!i->next)
            {
                cout << "[" << *i << "]" << "->|||";
            }
            else
            {
                cout << "[" << *i << "]" << "->";
            }
        }
    }
    else
    {
        cout << "|||";
    }
}

/*
    @summary: Prints the list backwards

    @param <const node<ITEM_TYPE> *head>: The head of the list.
*/
template<typename ITEM_TYPE>
inline void PrintList_backwards(const node<ITEM_TYPE>* head, const int depth)
{
    using std::cout;
    using std::endl;

    if (head)
    {
        PrintList_backwards(head->next, depth + 1);

        if (!depth)
        {
            cout << *head;
        }
        else
        {
            cout << *head << "<-";
        }
    }
    else
    {
        cout << "|||<-";
    }
}

/*
    @summary: Searches for an item in the list with the given key.

    @param <node<ITEM_TYPE> *head>: The head of the list.
    @param <const ITEM_TYPE &key>: The item to search for.

    @return <node<ITEM_TYPE> *>: The node containing the item.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* SearchList(node<ITEM_TYPE>* head, const ITEM_TYPE& key)
{
    for (node<ITEM_TYPE>* i = head; i != nullptr; i = i->next)
    {
        if (i->_item == key)
        {
            return i;
        }
    }

    return nullptr;
}

/*
    @summary: Inserts a node at the head of the list.

    @param <node<ITEM_TYPE> *&head>: The head of the list.
    @param <const ITEM_TYPE &insertThis>: The item to insert.

    @return <node<ITEM_TYPE> *>: The node that was inserted.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* InsertHead(node<ITEM_TYPE>*& head,
                                   const ITEM_TYPE& insertThis)
{
    node<ITEM_TYPE>* newNode = new node<ITEM_TYPE>(insertThis);

    if (head)
    {
        newNode->next = head;
        head->prev = newNode;
    }

    head = newNode;

    return newNode;
}

/*
    @summary: Inserts a node after a given node.

    @param <node<ITEM_TYPE> *&head>: The head of the list.
    @param <node<ITEM_TYPE> *afterThis>: The node to insert after.
    @param <const ITEM_TYPE &insertThis>: The item to insert.

    @return <node<ITEM_TYPE> *>: The node that was inserted.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* InsertAfter(node<ITEM_TYPE>*& head,
                                    node<ITEM_TYPE>* afterThis, const ITEM_TYPE& insertThis)
{
    node<ITEM_TYPE>* newNode = nullptr;

    if (head)
    {
        if (afterThis)
        {
            newNode = new node<ITEM_TYPE>(insertThis);

            node<ITEM_TYPE>* temp = nullptr;

            if (afterThis->next)
            {
                temp = afterThis->next;
            }

            afterThis->next = newNode;
            newNode->prev = afterThis;

            if (temp)
            {
                newNode->next = temp;
                temp->prev = newNode;
            }
        }
    }
    else
    {
        newNode = InsertHead(head, insertThis);
    }

    return newNode;
}

/*
    @summary: Inserts a node before a given node.

    @param <node<ITEM_TYPE> *&head>: The head of the list.
    @param <node<ITEM_TYPE> *beforeThis>: The node to insert before.
    @param <const ITEM_TYPE &insertThis>: The item to insert.

    @return <node<ITEM_TYPE> *>: The node that was inserted.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* InsertBefore(node<ITEM_TYPE>*& head,
                                     const node<ITEM_TYPE>* beforeThis, const ITEM_TYPE& insertThis)
{
    node<ITEM_TYPE>* newNode = nullptr;

    if (head)
    {
        if (beforeThis)
        {
            if (beforeThis == head)
            {
                newNode = InsertHead(head, insertThis);
            }
            else
            {
                node<ITEM_TYPE>* prev = PreviousNode(head, beforeThis);

                newNode = InsertAfter(head, prev, insertThis);
            }
        }
    }
    else
    {
        newNode = InsertHead(head, insertThis);
    }

    return newNode;
}

/*
    @summary: Returns the previous node of a given node.

    @param <node<ITEM_TYPE> *head>: The head of the list.
    @param <node<ITEM_TYPE> *prevToThis>: The node to get the previous node of.

    @return <node<ITEM_TYPE> *>: The previous node of the given node.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* PreviousNode(node<ITEM_TYPE>* head,
                                     const node<ITEM_TYPE>* prevToThis)
{
    node<ITEM_TYPE>* prev = nullptr;

    if (prevToThis)
    {
        prev = prevToThis->prev;
    }

    return prev;
}

/*
    @summary: Deletes a given node.

    @param <node<ITEM_TYPE> *&head>: The head of the list.
    @param <node<ITEM_TYPE> *deleteThis>: The node to delete.

    @return <ITEM_TYPE>: The value of the deleted node.
*/
template<typename ITEM_TYPE>
inline ITEM_TYPE DeleteNode(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* deleteThis)
{
    if (!deleteThis)
    {
        throw std::invalid_argument("Delete this was nullptr");
    }

    ITEM_TYPE item;

    if (head == deleteThis && !deleteThis->next)
    {
        item = head->_item;
        delete head;
        head = nullptr;
    }
    else
    {
        node<ITEM_TYPE>* prev = PreviousNode(head, deleteThis);
        item = deleteThis->_item;

        if (prev)
        {
            prev->next = deleteThis->next;
            deleteThis->prev = prev;
            delete deleteThis;
        }
        else
        {
            head = deleteThis->next;
            head->prev = nullptr;
            delete deleteThis;
        }
    }

    return item;
}

/*
    @summary: Copies a given list.

    @param <node<ITEM_TYPE> *head>: The head of the list.

    @return <node<ITEM_TYPE> *>: The copy of the given list.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* CopyList(node<ITEM_TYPE>* head)
{
    if (head)
    {
        node<ITEM_TYPE>* newHead = new node<ITEM_TYPE>(head->_item);
        node<ITEM_TYPE>* temp = newHead;

        for (node<ITEM_TYPE>* i = head->next; i != nullptr; i = i->next)
        {
            InsertAfter(newHead, temp, i->_item);
            temp = temp->next;
        }

        return newHead;
    }

    return nullptr;
}

/*
    @summary: Clears a given list.

    @param <node<ITEM_TYPE> *&head>: The head of the list.
*/
template<typename ITEM_TYPE>
inline void ClearList(node<ITEM_TYPE>*& head)
{
    node<ITEM_TYPE>* curr = head;
    node<ITEM_TYPE>* next = curr;

    while (curr && next)
    {
        next = curr->next;

        delete curr;
        curr = nullptr;
        curr = next;
    }

    head = nullptr;
}

/*
    @summary: Gets the value of a given position in the list.

    @param <node<ITEM_TYPE> *head>: The head of the list.
    @param <int pos>: The index of the node.

    @return <ITEM_TYPE &>: Reference to the item in the node.
*/
template<typename ITEM_TYPE>
inline ITEM_TYPE& At(node<ITEM_TYPE>* head, const int pos)
{
    node<ITEM_TYPE>* i = head;
    int idx = 0;

    while (i && idx < pos)
    {
        i = i->next;
        ++idx;
    }

    if (!i)
    {
        throw std::out_of_range("Index was out of range.");
    }

    return i->_item;
}

/*
    @summary: Inserts a node in a sorted order.

    @param <node<ITEM_TYPE> *&head>: The head of the list.
    @param <const ITEM_TYPE &item>: The item to insert.
    @param <const bool ascending>: Whether or not the list is sorted ascending or descending.

    @return <node<ITEM_TYPE> *>: The node that was inserted.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* InsertSorted(node<ITEM_TYPE>*& head,
                                     const ITEM_TYPE& item, const bool ascending)
{
    node<ITEM_TYPE>* newNode = nullptr;
    node<ITEM_TYPE>* mNode = WhereThisGoes(head, item, ascending);

    if (ascending)
    {
        if (mNode)
        {
            if (mNode->_item <= item)
            {
                newNode = InsertAfter(head, mNode, item);
            }
            else
            {
                newNode = InsertBefore(head, mNode, item);
            }
        }
        else
        {
            newNode = InsertHead(head, item);
        }
    }
    else
    {
        if (mNode)
        {
            if (mNode->_item >= item)
            {
                newNode = InsertAfter(head, mNode, item);
            }
            else
            {
                newNode = InsertBefore(head, mNode, item);
            }
        }
        else
        {
            newNode = InsertHead(head, item);
        }
    }

    return newNode;
}

/*
    @summary: Inserts a node into the list in a given order.
        If the item in the node is a duplicate, then adds to the item already in the list.

    @param <node<ITEM_TYPE> *&head>: The head of the list.
    @param <const ITEM_TYPE &item>: The item to insert/add to the list.
    @param <const bool ascending>: Whether or not the list is sorted in ascending/descending order.

    @return <node<ITEM_TYPE> *>: The node that was inserted.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* InsertSorted_and_add(node<ITEM_TYPE>*& head,
                                             const ITEM_TYPE& item, const bool ascending)
{
    if (head)
    {
        node<ITEM_TYPE>* mNode = SearchList(head, item);

        if (mNode)
        {
            mNode->_item += item;
        }
        else
        {
            mNode = InsertSorted(head, item, ascending);
        }

        return mNode;
    }

    return nullptr;
}

/*
    @summary: Finds the spot to insert a given item in a sorted list.

    @param <node<ITEM_TYPE> *head>: The head of the list.
    @param <const ITEM_TYPE &item>: The item to insert.
    @param <const bool ascending>: Whether or not the list is sorted ascending or descending.

    @return <node<ITEM_TYPE> *>: The node that was inserted.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* WhereThisGoes(node<ITEM_TYPE>* head,
                                      const ITEM_TYPE& item, const bool ascending)
{
    if (head)
    {
        node<ITEM_TYPE>* curr = head;

        if (ascending)
        {
            while (curr->next != nullptr && curr->next->_item < item)
            {
                curr = curr->next;
            }
        }
        else
        {
            while (curr->next != nullptr && curr->next->_item > item)
            {
                curr = curr->next;
            }
        }

        return curr;
    }

    return nullptr;
}

/*
    @summary: Returns the last node in the list.

    @param <node<ITEM_TYPE> *head>: The head of the list.

    @return <node<ITEM_TYPE> *>: The last node in the list.
*/
template<typename ITEM_TYPE>
inline node<ITEM_TYPE>* LastNode(node<ITEM_TYPE>* head)
{
    node<ITEM_TYPE>* end = head;
    node<ITEM_TYPE>* tail = nullptr;

    while (end)
    {
        tail = end;
        end = end->next;
    }

    return tail;
}