import os

import matplotlib.pyplot as plt
import pandas as pd

RESULT_DIRECTORY = "results/"


def main():
    file_name = [file for file in os.listdir(RESULT_DIRECTORY) if file.endswith(".csv")]

    list_of_algos = [
        "Counting Sort",
        "Cocktail Sort",
        "Enhanced Selection Sort",
        "Enhanced Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Bubble Sort",
        "Merge Sort",
        "Quick Sort",
    ]

    list_arr_type = [
        "Random",
        "Descending",
        "Almost Sorted",
        "Sorted",
    ]

    df_list_of_arr_type: list[pd.DataFrame] = [
        pd.DataFrame(
            columns=["element_count"]
            + [
                list_of_algos[i].lower().replace(" ", "_")
                for i in range(len(list_of_algos))
            ]
        )
        for _ in range(len(list_arr_type))
    ]

    for file in file_name:
        print("Processing file:", file, end="\r", flush=True)
        element_count = file.split("_")[2].split(".")[0]

        df_cur_file = pd.read_csv(RESULT_DIRECTORY + file)

        for i, arr_type in enumerate(list_arr_type):
            df_cur_arr_type = df_cur_file[arr_type]
            for j, algo in enumerate(list_of_algos):
                df_list_of_arr_type[i].loc[int(element_count), "element_count"] = int(
                    element_count
                )
                df_list_of_arr_type[i].loc[
                    int(element_count), algo.lower().replace(" ", "_")
                ] = float(df_cur_arr_type[j] / 1000)

    for arr_type in list_arr_type:
        plot_graph(df_list_of_arr_type[list_arr_type.index(arr_type)], arr_type)


def plot_graph(df: pd.DataFrame, arr_type: str):
    plt.figure(figsize=(6, 6))
    plt.title(f"Time Complexity of Sorting Algorithms on {arr_type} Array")
    plt.xlabel("Number of Elements")
    plt.ylabel("Time Taken (in seconds)")

    for col in df.columns[1:]:
        plt.scatter(
            df["element_count"], df[col], label=col.replace("_", " ").title(), s=5
        )

    plt.legend()
    plt.savefig(f"graphs/{arr_type}.png")


if __name__ == "__main__":
    main()
