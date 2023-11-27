#include "sorting_algo.hpp"

void enhancedSelectionSort(std::vector<int> arr, int size) {
  if (size <= 1)
    return;
  int index, tmp, max;
  index = size - 1;
  max = arr[index];
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] >= max) {
      max = arr[i];
      index = i;
    }
  }
  if (index != size - 1) {
    tmp = arr[size - 1];
    arr[size - 1] = max;
    arr[index] = tmp;
  }
  --size;
  enhancedSelectionSort(arr, size);
}

void enhancedBubbleSort(std::vector<int> arr, int size, int firstIndex,
                        int lastIndex) {
  if (size <= 1)
    return;
  int tmp = 0;
  int maxCounter = lastIndex;
  int minCounter = firstIndex;
  int max = arr[lastIndex];
  int min = arr[firstIndex];
  for (int i = firstIndex; i <= lastIndex; i++) {
    if (arr[i] >= max) {
      max = arr[i];
      maxCounter = i;
    }
    if (arr[i] < min) {
      min = arr[i];
      minCounter = i;
    }
  }
  if (firstIndex == maxCounter && lastIndex == minCounter) {
    arr[firstIndex] = min;
    arr[lastIndex] = max;
  } else if (firstIndex == maxCounter && lastIndex != minCounter) {
    tmp = arr[minCounter];
    arr[minCounter] = arr[lastIndex];
    arr[lastIndex] = max;
    arr[firstIndex] = min;
  } else if (firstIndex != maxCounter && lastIndex == minCounter) {
    tmp = arr[maxCounter];
    arr[maxCounter] = arr[firstIndex];
    arr[firstIndex] = min;
    arr[lastIndex] = max;
  } else {
    tmp = arr[maxCounter];
    arr[maxCounter] = arr[firstIndex];
    arr[firstIndex] = min;
    tmp = arr[minCounter];
    arr[minCounter] = arr[lastIndex];
    arr[lastIndex] = max;
  }
  ++firstIndex;
  --lastIndex;
  size -= 2;
  enhancedBubbleSort(arr, size, firstIndex, lastIndex);
}
