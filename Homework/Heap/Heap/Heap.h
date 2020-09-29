#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

template<typename T>
class Heap
{
public:
    Heap();

    void insert(const T& insert_me);
    T pop();

    bool is_empty() const;
    unsigned int size() const;
    unsigned int capacity() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& outs, const Heap<U>& print_me);

private:
    void print_tree(std::ostream& outs = std::cout) const;
    void print_tree(unsigned int root, int level = 0, std::ostream& outs = std::cout) const;
    bool is_leaf(unsigned int i) const;
    unsigned int parent_index(unsigned int i) const;
    unsigned int left_child_index(unsigned int i)const;
    unsigned int right_child_index(unsigned int i) const;
    unsigned int big_child_index(unsigned int i) const;
    void swap_with_parent(unsigned int i);
    void heapify_up(unsigned int i);
    void heapify_down(unsigned int i);

    std::vector<T> tree;
};

template<typename T>
inline Heap<T>::Heap()
{

}

template<typename T>
inline void Heap<T>::insert(const T& insert_me)
{
    tree.emplace_back(insert_me);

    if (!is_empty())
        heapify_up(size() - 1);
}

template<typename T>
inline T Heap<T>::pop()
{
    if (is_empty())
        throw std::out_of_range("Heap is empty.");

    T item = tree.back();
    tree[0] = item;
    tree.pop_back();
    heapify_down(0);

    return item;
}

template<typename T>
inline bool Heap<T>::is_empty() const
{
    return tree.empty();
}

template<typename T>
inline unsigned int Heap<T>::size() const
{
    return tree.size();
}

template<typename T>
inline unsigned int Heap<T>::capacity() const
{
    return tree.capacity();
}

template<typename T>
inline void Heap<T>::print_tree(std::ostream& outs) const
{
    for (const auto& i : tree)
        outs << i << " ";
}

template<typename T>
inline void Heap<T>::print_tree(unsigned int root, int level, std::ostream& outs) const
{
    if (root < 0 || root >= size())
        return;

    print_tree(right_child_index(root), level + 5, outs);

    outs << std::endl;
    for (int i = 0; i < level; ++i)
        outs << " ";
    outs << "{" << tree[root] << "}" << std::endl;

    print_tree(left_child_index(root), level + 5, outs);
}

template<typename T>
inline bool Heap<T>::is_leaf(unsigned int i) const
{
    return (i >= size() / 2) && (i < size());
}

template<typename T>
inline unsigned int Heap<T>::parent_index(unsigned int i) const
{
    return (i - 1) / 2;
}

template<typename T>
inline unsigned int Heap<T>::left_child_index(unsigned int i) const
{
    return (2 * i) + 1;
}

template<typename T>
inline unsigned int Heap<T>::right_child_index(unsigned int i) const
{
    return (2 * i) + 2;
}

template<typename T>
inline unsigned int Heap<T>::big_child_index(unsigned int i) const
{
    unsigned int largest = i;

    if (left_child_index(i) < size() && 
        tree[left_child_index(i)] > tree[largest])
        largest = left_child_index(i);
    if (right_child_index(i) < size() && 
        tree[right_child_index(i)] > tree[largest])
        largest = right_child_index(i);

    return largest;
}

template<typename T>
inline void Heap<T>::swap_with_parent(unsigned int i)
{
    std::swap(tree[i], tree[parent_index(i)]);
}

template<typename T>
inline void Heap<T>::heapify_up(unsigned int i)
{
    if (parent_index(i) >= 0 && parent_index(i) < size())
    {
        if (tree[i] > tree[parent_index(i)])
        {
            swap_with_parent(i);
            heapify_up(parent_index(i));
        }
    }
}

template<typename T>
inline void Heap<T>::heapify_down(unsigned int i)
{
    if (is_leaf(i))
        return;

    if (big_child_index(i) != i)
    {
        swap_with_parent(big_child_index(i));
        heapify_down(big_child_index(i));
    }
}

template<typename U>
inline std::ostream& operator<<(std::ostream& outs, const Heap<U>& print_me)
{
    print_me.print_tree(0, 0, outs);

    return outs;
}
