#pragma once

#include <cstdlib>

namespace Sort
{
    void SelectionSort(int a[], size_t n);
    void BubbleSort(int a[], size_t n);
    void MergeSort(int a[], size_t n);
    void QuickSort(int a[], size_t n);
    void heapify(int a[], size_t n, size_t i);
    void HeapSort(int a[], size_t n);
}