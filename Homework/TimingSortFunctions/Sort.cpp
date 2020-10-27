#include <algorithm>

#include "Heap.h"

using namespace std;

namespace Sort
{
    void SelectionSort(int a[], size_t n)
    {
        for (size_t i = 0; i < n; ++i)
        {
            size_t max = i;

            for (size_t j = i + 1; j < n; ++j)
            {
                if (a[j] > a[max])
                    max = j;
            }

            swap(a[i], a[max]);
        }
    }

    void BubbleSort(int a[], size_t n)
    {
        bool swapped;

        for (size_t i = 0; i < n - 1; i++)
        {
            swapped = false;

            for (size_t j = 0; j < n - i - 1; j++)
            {
                if (a[j] > a[j + 1])
                {
                    swap(a[j], a[j + 1]);
                    swapped = true;
                }
            }

            // IF no two elements were swapped by inner loop, then break
            if (!swapped)
                break;
        }
    }

    void MergeSort(int a[], size_t n)
    {
        auto merge = [](int data[], size_t n1, size_t n2) {
            int *temp;          // Points to dynamic array to hold the sorted elements
            size_t copied = 0;  // Number of elements copied from data to temp
            size_t copied1 = 0; // Number copied from the first half of data
            size_t copied2 = 0; // Number copied from the second half of data
            size_t i;           // Array index to copy from temp back into data

            // Allocate memory for the temporary dynamic array.
            temp = new int[n1 + n2];

            // Merge elements, copying from two halves of data to the temporary array.
            while ((copied1 < n1) && (copied2 < n2))
            {
                if (data[copied1] < (data + n1)[copied2])
                    temp[copied++] = data[copied1++]; // Copy from first half
                else
                    temp[copied++] = (data + n1)[copied2++]; // Copy from second half
            }

            // Copy any remaining entries in the left and right subarrays.
            while (copied1 < n1)
                temp[copied++] = data[copied1++];
            while (copied2 < n2)
                temp[copied++] = (data + n1)[copied2++];

            // Copy from temp back to the data array, and release temp's memory.
            for (i = 0; i < n1 + n2; i++)
                data[i] = temp[i];

            delete[] temp;
        };

        size_t n1; // Size of the first subarray
        size_t n2; // Size of the second subarray

        if (n > 1)
        {
            // Compute sizes of the subarrays.
            n1 = n / 2;
            n2 = n - n1;

            MergeSort(a, n1);        // Sort from data[0] through data[n1-1]
            MergeSort((a + n1), n2); // Sort from data[n1] to the end

            // Merge the two sorted halves.
            merge(a, n1, n2);
        }
    }

    void QuickSort(int a[], size_t n)
    {
        auto partition = [](int a[], size_t n, size_t &pivot_index) {
            pivot_index = 0;
            int pivot = a[pivot_index];
            size_t big_idx = 1;
            size_t small_idx = n - 1;

            while (big_idx <= small_idx)
            {
                while (big_idx < n && a[big_idx] <= pivot)
                    ++big_idx;

                while (a[small_idx] > pivot)
                    --small_idx;

                if (big_idx < small_idx)
                    swap(a[big_idx], a[small_idx]);
            }

            pivot_index = small_idx;
            a[0] = a[pivot_index];
            a[pivot_index] = pivot;
        };

        size_t pivot_index; // Array index for the pivot element
        size_t n1;          // Number of elements before the pivot element
        size_t n2;          // Number of elements after the pivot element

        if (n > 1)
        {
            // Partition the array, and set the pivot index.
            partition(a, n, pivot_index);

            // Compute the sizes of the subarrays.
            n1 = pivot_index;
            n2 = n - n1 - 1;

            // Recursive calls will now sort the subarrays.
            QuickSort(a, n1);
            QuickSort((a + pivot_index + 1), n2);
        }
    }

    void heapify(int a[], size_t n, size_t i)
    {
        size_t largest = i;   // Initialize largest as root
        size_t l = 2 * i + 1; // left = 2*i + 1
        size_t r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && a[l] > a[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < n && a[r] > a[largest])
            largest = r;

        // If largest is not root
        if (largest != i)
        {
            swap(a[i], a[largest]);

            // Recursively heapify the affected sub-tree
            heapify(a, n, largest);
        }
    }

    void HeapSort(int a[], size_t n)
    {
        for (size_t i = n / 2 - 1; (int)i >= 0; --i)
            heapify(a, n, i);

        // One by one extract an element from heap
        for (size_t i = n - 1; i > 0; --i)
        {
            // Move current root to end
            swap(a[0], a[i]);

            // call max heapify on the reduced heap
            heapify(a, i, 0);
        }
    }
} // namespace Sort