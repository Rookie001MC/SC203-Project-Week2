#include "sorting_algo.hpp"

std::vector<int> quickSort(std::vector<int> a, int l, int r)
{
    if (l < r)
    {
        int pi = partition(a, l, r);
        quickSort(a, l, pi - 1);
        quickSort(a, pi + 1, r);
    }
    return a;
}

int partition(std::vector<int> &a, int l, int r)
{
    int pivot = a[r];
    int i     = l - 1;
    for (int j = l; j < r; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i + 1], a[r]);
    return i + 1;
}