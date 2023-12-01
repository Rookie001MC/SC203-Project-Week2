import pprint

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def main():
    df_10 = load_from_file("timeTable_10.csv")
    df_100 = load_from_file("timeTable_100.csv")
    df_1000 = load_from_file("timeTable_1000.csv")
    df_10000 = load_from_file("timeTable_10000.csv")
    df_100000 = load_from_file("timeTable_100000.csv")

    df_list = [df_10, df_100, df_1000, df_10000, df_100000]

    sorting_algorithms = [
        "Counting Sort",
        "Cocktail Sort",
        "Enhanced Selection Sort",
        "Enhanced Bubble Sort",
        "Selection Sort",
        "Merge Sort",
        "Bubble Sort",
    ]

    arrays_size = [10, 100, 1000, 10000, 100000]

    array_type = ["Random", "Descending", "Almost Sorted", "Sorted"]

    data = {}

    # Create the dictionary structure to populate the data later

    for sorting_algorithm in sorting_algorithms:
        data[sorting_algorithm] = {}
        for array_size in arrays_size:
            data[sorting_algorithm][array_size] = {}
            for array in array_type:
                data[sorting_algorithm][array_size][array] = 0
   
    pp = pprint.PrettyPrinter(indent=4)
    # Populate the data dictionary with the data from the dataframes
    # CSV File format:
    # Random, Descending, Almost Sorted, Sorted
    # 0.001, 0.001, 0.001, 0.001

    # Just assume that each row is a sorting algorithm, correspoting to the sorting_algorithms list

    for i in range(len(sorting_algorithms)):
        for j in range(len(arrays_size)):
            for k in range(len(array_type)):
                # Convert the time from milliseconds to seconds
                df_list[j].iloc[i, k] = df_list[j].iloc[i, k] / 1000
                data[sorting_algorithms[i]][arrays_size[j]][array_type[k]] = df_list[j].iloc[i, k]

                    
    pp.pprint(data)
    
    # Draw the bar graphs

    x = np.arange(len(sorting_algorithms))
    width = 0.3
    multiplier = 0
    scaling = 3

    fig, ax = plt.subplots()

    # Each group is a different array size, and each bar is a different sorting algorithm
    # We have 4 groups, and 7 bars per group
    # The bars are sorted by array size, and the groups are sorted by sorting algorithm
    # we also need to scale down the bar heights by a factor of 3 in order to make the graph 
    # readable.

    plt.show()

def load_from_file(filename: str) -> pd.DataFrame:
    """Load data from a csv file"""
    return pd.read_csv(filename)


if __name__ == "__main__":
    main()
