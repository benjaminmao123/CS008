#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>

#include "Timer.h"
#include "Sort.h"
#include "Heap.h"

using namespace std;

#define SIZE 50000

enum class SortType
{
    SELECTION,
    BUBBLE,
    MERGE,
    QUICK,
    HEAP,
    COUNT
};

float time_sort_routine(int a[],
                        void (*f)(int *, size_t));

double sort_test(int a[], void (*f)(int *, size_t));
void print_results(double times[], size_t start, size_t end);

int main()
{
    int *a = new int[SIZE];

    for (int i = 0; i < SIZE; ++i)
        a[i] = i;

    shuffle(a, a + SIZE, default_random_engine(0));
    cout << time_sort_routine(a, Sort::BubbleSort);
    double times[5];

    int i = (int)SortType::MERGE;

    for (i; i < (int)SortType::COUNT; ++i)
    {
        switch ((SortType)i)
        {
        case SortType::SELECTION:
            times[i] = sort_test(a, Sort::SelectionSort);
            break;
        case SortType::BUBBLE:
            times[i] = sort_test(a, Sort::SelectionSort);
            break;
        case SortType::MERGE:
            times[i] = sort_test(a, Sort::MergeSort);
            break;
        case SortType::QUICK:
            times[i] = sort_test(a, Sort::QuickSort);
            break;
        case SortType::HEAP:
            times[i] = sort_test(a, Sort::HeapSort);
            break;
        default:
            break;
        }
    }

    print_results(times, 2, (int)SortType::COUNT);

    return 0;
}

float time_sort_routine(int a[],
                        void (*f)(int *, size_t))
{
    timer t;

    t.start();
    f(a, SIZE);
    t.stop();

    return t.duration();
}

double sort_test(int a[], void (*f)(int *, size_t))
{
    int *a_cpy = new int[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
        a_cpy[i] = a[i];

    auto getAverage = [](double times[]) {
        double total = 0.0;

        for (int i = 0; i < 500; ++i)
            total += times[i];

        return total / 500.0;
    };

    double sortTimes[500];

    for (size_t i = 0; i < 500; ++i)
    {
        cout << "iteration: " << i << endl;
        sortTimes[i] = time_sort_routine(a_cpy, f) * 1000.0;
        shuffle(a_cpy, a_cpy + SIZE, default_random_engine(0));
    }

    delete[] a_cpy;

    return getAverage(sortTimes);
}

void print_results(double times[], size_t start, size_t end)
{
    while (start < end)
    {
        cout << "average duration - ";

        switch ((SortType)start)
        {
        case SortType::SELECTION:
            cout << "selectionSort(50000): " << times[start];
            break;
        case SortType::BUBBLE:
            cout << "bubbleSort(50000): " << times[start];
            break;
        case SortType::MERGE:
            cout << "mergeSort(50000): " << times[start];
            break;
        case SortType::QUICK:
            cout << "quickSort(50000): " << times[start];
            break;
        case SortType::HEAP:
            cout << "heapSort(50000): " << times[start];
            break;
        default:
            break;
        }

        cout << endl;

        ++start;
    }
}