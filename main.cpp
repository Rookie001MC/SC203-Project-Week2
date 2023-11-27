#include "sort_algos/sorting_algo.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

void read_from_file(std::string filename, std::vector<int> &arr);
void write_to_csv(std::string filename,
                  const std::vector<std::vector<unsigned long long>> &timeTable,
                  std::vector<std::string> headers);
void output_table(const std::vector<std::vector<unsigned long long>> &timeTable,
                  std::vector<std::string> headers);

int main() {

  system("python3 generate_data.py");

  std::vector<int> randomArr;
  std::vector<int> descendingArr;
  std::vector<int> almostSortedArr;
  std::vector<int> sortedArr;

  bool runCountingSort = true;
  bool runCocktailSort = true;
  bool runEnhancedSelectionSort = false;
  bool runEnhancedBubbleSort = true;
  bool runSelectionSort = true;
  bool runInsertionSort = true;
  bool runMergeSort = true;
  bool runBubbleSort = true;

  for (int i = 0; i < 7; i++) {
    int n = pow(10, i + 1);

    std::string random_filename = "random_" + std::to_string(n) + ".txt";
    std::string descending_filename = "desc_" + std::to_string(n) + ".txt";
    std::string almostSorted_filename =
        "almost_sorted_" + std::to_string(n) + ".txt";
    std::string sorted_filename = "result_" + std::to_string(n) + ".txt";

    read_from_file(random_filename, randomArr);
    read_from_file(descending_filename, descendingArr);
    read_from_file(almostSorted_filename, almostSortedArr);
    read_from_file(sorted_filename, sortedArr);

    // 2d vector to store the time of each algorithm
    // each column is the algorithm
    // each row is the array type
    std::vector<std::vector<unsigned long long>> timeTable(
        4, std::vector<unsigned long long>(8, 0));
    std::cout << "----------------------------" << std::endl;
    std::cout << "n = " << n << std::endl;

    if (runCountingSort) {
      std::cout << "Running Counting Sort for ";
      // Run Counting Sort for 4 cases
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std ::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std ::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std ::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        counting_sort(arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;

        // Append the time to the time table
        timeTable[j][0] = (duration.count());
      }
    }

    if (runCocktailSort) {
      // Run Cocktail Sort for 4 cases
      std::cout << "Running Cocktail Sort for ";
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std ::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std ::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std ::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        cocktail_sort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;
        // Append the time to the time table
        timeTable[j][1] = (duration.count());
      }
    }

    if (runEnhancedSelectionSort) {
      // Run Enhanced Selection Sort for 4 cases
      std::cout << "Running Enhanced Selection Sort for ";
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std ::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std ::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std ::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        enhancedSelectionSort(arr, arr.size());
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;

        // Append the time to the time table
        timeTable[j][2] = (duration.count());
      }
    }

    if (runEnhancedBubbleSort) {
      // Run Enhanced Bubble Sort for 4 cases
      std::cout << "Running Enhanced Bubble Sort for ";
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std ::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std ::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std ::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        enhancedBubbleSort(arr, arr.size(), 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;

        // Append the time to the time table
        timeTable[j][3] = (duration.count());
      }
    }

    if (runSelectionSort) {
      // Run Selection Sort for 4 cases
      std::cout << "Running Selection Sort for ";
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std ::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std ::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std ::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        selectionSort(arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;

        // Append the time to the time table
        timeTable[j][4] = (duration.count());
      }
    }

    if (runInsertionSort) {
      // Run Insertion Sort for 4 cases
      std::cout << "Running Insertion Sort for ";
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std ::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std ::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std ::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;

        // Append the time to the time table
        timeTable[j][5] = (duration.count());
      }
    }

    if (runMergeSort) {
      // Run Merge Sort for 4 cases
      std::cout << "Running Merge Sort for ";
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std ::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std ::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std ::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;

        // Append the time to the time table
        timeTable[j][6] = (duration.count());
      }
    }

    if (runBubbleSort) {
      // Run Bubble Sort for 4 cases
      std::cout << "Running Bubble Sort for ";
      for (int j = 0; j < 4; j++) {
        std::vector<int> arr;
        if (j == 0) {
          arr = randomArr;
          std ::cout << "random array" << std::endl;
        } else if (j == 1) {
          arr = descendingArr;
          std::cout << "descending array" << std::endl;
        } else if (j == 2) {
          arr = almostSortedArr;
          std::cout << "almost sorted array" << std::endl;
        } else if (j == 3) {
          arr = sortedArr;
          std::cout << "sorted array" << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        bubbleSort(arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " microseconds"
                  << std::endl;

        // Append the time to the time table
        timeTable[j][7] = (duration.count());
      }
    }

    // Write the time table to a csv file
    std::string filename = "timeTable_" + std::to_string(n) + ".csv";
    std::vector<std::string> headers = {"Random", "Descending", "Almost Sorted",
                                        "Sorted"};

    write_to_csv(filename, timeTable, headers);
    output_table(timeTable, headers);
  }
}

void read_from_file(std::string filename, std::vector<int> &arr) {
  std::ifstream file(filename);
  if (file.is_open()) {
    int num;
    while (file >> num) {
      arr.push_back(num);
    }
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
  file.close();
}

void write_to_csv(std::string filename,
                  const std::vector<std::vector<unsigned long long>> &timeTable,
                  std::vector<std::string> headers) {
  std::fstream(file);
  file.open(filename, std::ios::out | std::ios::app);
  if (file.is_open()) {
    // Write the headers
    for (int i = 0; i < headers.size(); i++) {
      file << headers[i] << ",";
    }
    file << "\n";

    // Write the time table
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 4; j++) {
        file << timeTable[j][i] << ",";
      }
      file << "\n";
    }
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  file.close();
}

void output_table(const std::vector<std::vector<unsigned long long>> &timeTable,
                  std::vector<std::string> headers) {
  // Write the headers
  for (int i = 0; i < headers.size(); i++) {
    std::cout << headers[i] << ",";
  }
  std::cout << "\n";

  // Write the time table
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << timeTable[j][i] << ",";
    }
    std::cout << "\n";
  }
}
