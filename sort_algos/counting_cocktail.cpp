#include "sorting_algo.hpp"

std::vector<int> counting_sort(std::vector<int> input, int n) {
  int output[n]; // The output will have sorted input array
  int max = input[0];
  int min = input[0];

  for (int i = 1; i < n; i++) {
    if (input[i] > max)
      max = input[i]; // Maximum value in array
    else if (input[i] < min)
      min = input[i]; // Minimum value in array
  }

  int k = max - min + 1; // Size of count array

  int count_array[k]; // Create a count_array to store count of each individual
                      // input value
  std::fill_n(count_array, k, 0); // Initialize count_array elements as zero

  for (int i = 0; i < n; i++)
    count_array[input[i] - min]++; // Store count of each individual input value

  /* Change count_array so that count_array now contains actual
   position of input values in output array */
  for (int i = 1; i < k; i++)
    count_array[i] += count_array[i - 1];

  // Populate output array using count_array and input array
  for (int i = 0; i < n; i++) {
    output[count_array[input[i] - min] - 1] = input[i];
    count_array[input[i] - min]--;
  }

  for (int i = 0; i < n; i++)
    input[i] = output[i]; // Copy the output array to input, so that input now
                          // contains sorted values

  return input;
}

std::vector<int> cocktail_sort(std::vector<int> arr) {
  bool swapped = true;
  int start = -1;
  int end = arr.size() - 1;

  while (swapped) {
    swapped = false; // Reset the flag for forward pass
    for (int i = ++start; i < end; i++) {
      if (arr[i] >
          arr[i + 1]) { // Compare and shift the larger element to the right
        std::swap(arr[i], arr[i + 1]);
        swapped = true;
      }
    }

    if (!swapped)
      break; // Break the loop if no swapping happens

    swapped = false; // Reset the flag for backward pass
    for (int i = --end; i > start; i--) {
      if (arr[i] <
          arr[i - 1]) { // Compare and shift the smaller element to the left
        std::swap(arr[i], arr[i - 1]);
        swapped = true;
      }
    }
  }
  return arr;
}
