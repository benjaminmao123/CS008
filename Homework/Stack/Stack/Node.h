/*
 * Author: Benjamin Mao
 * Project: Linked List Functions
 * Purpose: Acts as a helper class to make up
 *      the nodes of the list.
 *
 * Notes: None.
 */

#pragma once

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
    node(const ITEM_TYPE &item)
        : _item(item), next(nullptr), prev(nullptr)
    {

    }

    /*
        @summary: Overloaded insertion operator to print contents of node.

        @param <std::ostream &outs>: The ostream object.
        @param <const node<T> &printMe>: The node to print.

        @return <std::ostream &>: ostream reference.
    */
    friend std::ostream &operator<<(std::ostream &outs, const node<ITEM_TYPE> &printMe)
    {
        outs << printMe._item;

        return outs;
    }

    ITEM_TYPE _item;
    node *next;
    node *prev;
};