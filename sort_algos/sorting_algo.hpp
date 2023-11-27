#pragma once

#include <algorithm>
#include <vector>

std::vector<int> counting_sort(std::vector<int> input, int n);
std::vector<int> cocktail_sort(std::vector<int> arr);
void enhancedSelectionSort(std::vector<int> arr, int size);
void enhancedBubbleSort(std::vector<int> arr, int size, int firstIndex,
                        int lastIndex);

std::vector<int> selectionSort(std::vector<int> a, int n);
std::vector<int> insertionSort(std::vector<int> a, int n);
void merge(std::vector<int> &a, int l, int r, int m);
std::vector<int> mergeSort(std::vector<int> a, int l, int r);
std::vector<int> bubbleSort(std::vector<int> a, int n);