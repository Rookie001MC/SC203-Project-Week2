#include "sorting_algo.hpp"
using namespace std;

// Selection Sort
std::vector<int> selectionSort(std::vector<int> a, int n) {
  for (int i = 0; i < n - 1; ++i) {
    int idMin = i;
    for (int j = i + 1; j < n; ++j) {
      if (a[j] <= a[idMin])
        idMin = j;
    }
    swap(a[i], a[idMin]);
  }
  return a;
}

// Insertion Sort
std::vector<int> insertionSort(std::vector<int> a, int n) {
  for (int i = 1; i < n; ++i) {
    int next = a[i];
    int j = i - 1;

    while (next < a[j] && j >= 0) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = next;
  }
  return a;
}

// Merge Sort
void merge(std::vector<int> &a, int l, int r, int m) {
  int i = l;
  int j = m + 1;
  int k = 0;

  int n = (r - l) + 1;
  std::vector<int> tmp(n);

  while (i <= m && j <= r) {
    if (a[i] <= a[j]) {
      tmp[k] = a[i];
      k++;
      i++;
    } else {
      tmp[k] = a[j];
      k++;
      j++;
    }
  }

  while (i <= m) {
    tmp[k] = a[i];
    k++;
    i++;
  }

  while (j <= r) {
    tmp[k] = a[j];
    k++;
    j++;
  }

  for (int i = 0; i < n; ++i) {
    a[l + i] = tmp[i];
  }
}

std::vector<int> mergeSort(std::vector<int> a, int l, int r) {
  if (l < r) {
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);

    merge(a, l, r, m);
  }
  return a;
}

// Bubble Sort
std::vector<int> bubbleSort(std::vector<int> a, int n) {
  int i, j;
  bool isSwap = false;
  for (i = 0; i < n - 1; i++) {
    isSwap = false;
    for (j = 0; j < n - i - 1; j++) {
      if (a[j] > a[j + 1]) {
        swap(a[j], a[j + 1]);
        isSwap = true;
      }
    }

    if (isSwap == false) {
      break;
    }
  }
  return a;
}
