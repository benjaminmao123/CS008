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
        //balance factor = height of the right subtree 
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        int factor = 0;

        if (_left && _right)
            factor = _right->height() - _left->height();
        else if (_left)
            factor = -1 - _left->height();
        else if (_right)
            factor = _right->height() + 1;
        
        return factor;
    }

    int height()
    {
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)
        if (_left && _right)
            _height = std::max(_left->height(), _right->height()) + 1;
        else if (_left)
            _height = _left->height() + 1;
        else if (_right)
            _height = _right->height() + 1;
        else
            _height = 0;

        return _height;
    }

    int update_height() 
    {
        //set the _height member variable (call height();)
        return height();
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
template <typename T>
tree_node<T>* tree_from_sorted_list(const T* a, int l, int r);

// ---------------- ROTATIONS --------------------------
template <typename T>
tree_node<T>* rotate_right(tree_node<T>*& root);
template <typename T>
tree_node<T>* rotate_left(tree_node<T>*& root);
template <typename T>
tree_node<T>* rotate(tree_node<T>*& root); //decide which rotate is needed based on balance factor

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
        std::cout << "Item exists." << std::endl;
}

template<typename T>
inline tree_node<T>* tree_search(tree_node<T>* root, const T& target)
{
    tree_node<T>* res = nullptr;
    tree_search(root, target, res);

    return res;
}

template<typename T>
inline bool tree_search(tree_node<T>* root, const T& target, tree_node<T>*& found_ptr)
{
    if (!root)
        return nullptr;

    if (target == root->_item)
    {
        found_ptr = root;
        return true;
    }
    else if (target < root->_item)
        return tree_search(root->_left, target, found_ptr);

    return tree_search(root->_right, target, found_ptr);
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
        tree_print(root->_right, level + 10, outs);

    outs << std::endl;
    for (int i = 0; i < level; ++i)
        outs << " ";
    outs << "{" << root->_item << "}" << std::endl;

    if (root->_left)
        tree_print(root->_left, level + 10, outs);
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
        tree_print_debug(root->_right, level + 10, outs);

    outs << std::endl;
    for (int i = 0; i < level; ++i)
        outs << " ";
    outs << "{" << root->_item << "}" << "H: " << root->_height << std::endl;

    if (root->_left)
        tree_print_debug(root->_left, level + 10, outs);
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
        if (!root->_left && !root->_right)
        {
            delete root;
            root = nullptr;
            return true;
        }
        else if (!root->_left)
        {
            tree_node<T>* temp = root->_right;
            delete root;
            root = temp;
        }
        else if (!root->_right)
        {
            tree_node<T>* temp = root->_left;
            delete root;
            root = temp;
        }
        else
        {
            tree_node<T>* successor = root->_right;

            while (successor && successor->_left)
                successor = successor->_left;

            root->_item = successor->_item;

            tree_erase(root->_right, successor->_item);
        }
    }

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
        delete root;
        root = nullptr;

        return;
    }
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
    if (!dest)
        return src;
    if (!src)
        return dest;

    dest->_item += src->_item;

    dest->_left = MergeTrees(dest->_left, src->_left);
    dest->_right = MergeTrees(dest->_right, src->_right);

    return dest;
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

template<typename T>
inline tree_node<T>* rotate_right(tree_node<T>*& root)
{
    tree_node<T>* middleNode = root->_left;
    root->_left = middleNode->_right;
    middleNode->_right = root;

    root->update_height();
    middleNode->update_height();

    return middleNode;
}

template<typename T>
inline tree_node<T>* rotate_left(tree_node<T>*& root)
{
    tree_node<T>* middleNode = root->_right;
    root->_right = middleNode->_left;
    middleNode->_left = root;

    root->update_height();
    middleNode->update_height();

    return middleNode;
}

template<typename T>
inline tree_node<T>* rotate(tree_node<T>*& root)
{
    

    return NULL;
}
