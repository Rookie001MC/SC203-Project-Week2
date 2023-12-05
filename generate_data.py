import random
from enum import Enum

import numpy as np


def read_config(filename: str):
    with open(filename, "r") as f:
        try:
            count = int(f.readline())
        except ValueError:
            print("Invalid value for MAX_TEST_CASES")
            exit(1)
        return count


class DatasetGeneratorMode(Enum):
    RANDOM = 0
    ASCENDING = 1
    DESCENDING = 2
    ALMOST_SORTED = 3


MAX_TEST_CASES = read_config("config/maxTestCaseCount.cfg")
TESTCASE_DIR = "testcases"


def main() -> None:
    mode_filename = [
        "random",
        "ascending",
        "descending",
        "almost_sorted",
    ]

    FACTOR_EVERY_ITERATION = 1
    arr_size = 0

    for i in range(MAX_TEST_CASES):
        if i % int((MAX_TEST_CASES / 80)) == 0:
            FACTOR_EVERY_ITERATION += 2
        print(100 * FACTOR_EVERY_ITERATION)
        arr_size = random.randint(10, 100 * FACTOR_EVERY_ITERATION)

        min_value = int(
            round(random.randint(-10, 6)) * (((i + 1)) + FACTOR_EVERY_ITERATION / 2)
        )
        max_value = int(
            round(random.randint(7, 10)) * (((i + 1)) + FACTOR_EVERY_ITERATION / 2)
        )

        print(
            f"Generating test case {i} with size {arr_size}, min value {min_value}, max value {max_value}"
        )
        for mode in DatasetGeneratorMode:
            filename = f"{TESTCASE_DIR}/{mode_filename[mode.value]}_{i}.txt"

            generator = DatasetGenerator(arr_size, min_value, max_value, mode)
            generator.generate()
            generator.write_to_text(filename)


class DatasetGenerator:
    def __init__(
        self,
        num_elements: int,
        min_value: int,
        max_value: int,
        mode: DatasetGeneratorMode,
    ):
        if mode not in DatasetGeneratorMode:
            raise ValueError("Invalid mode for DatasetGenerator")
        self._num_elements = num_elements
        self._min_value = min_value
        self._max_value = max_value
        self._mode = mode
        self._rng_engine = np.random.Generator(np.random.PCG64DXSM())
        self.data = np.empty(num_elements, dtype=np.int64)

    def generate(self) -> np.ndarray:
        # First generate a random array for us to work with
        self.data = self._rng_engine.integers(
            low=self._min_value, high=self._max_value, size=self._num_elements
        )

        # Now sort the array based on the mode
        if self._mode == DatasetGeneratorMode.RANDOM:
            self.data = self._rng_engine.permutation(self.data)
        elif self._mode == DatasetGeneratorMode.ASCENDING:
            self.data = np.sort(self.data)
        elif self._mode == DatasetGeneratorMode.DESCENDING:
            self.data = np.sort(self.data)[::-1]
        elif self._mode == DatasetGeneratorMode.ALMOST_SORTED:
            # For this, we should the array in ascending order.
            # Then, we swap a couple of elements in the array, by randomize the index
            # of the elements to swap.
            # We will swap 10% of the elements in the array.
            self.data = np.sort(self.data)
            num_elements_to_swap = int(self._num_elements * 0.1)
            indices_to_swap = self._rng_engine.choice(
                self._num_elements, size=num_elements_to_swap, replace=False
            )
            for i in range(num_elements_to_swap):
                # Swap the elements
                temp = self.data[i]
                self.data[i] = self.data[indices_to_swap[i]]
                self.data[indices_to_swap[i]] = temp

        return self.data

    def write_to_text(self, filename: str) -> None:
        np.savetxt(filename, self.data, fmt="%d")

    def get_num_elements(self) -> int:
        return self._num_elements

    def get_min_value(self) -> int:
        return self._min_value

    def get_max_value(self) -> int:
        return self._max_value

    def get_mode(self) -> str:
        mode_str = {
            DatasetGeneratorMode.RANDOM: "Random",
            DatasetGeneratorMode.ASCENDING: "Ascending",
            DatasetGeneratorMode.DESCENDING: "Descending",
            DatasetGeneratorMode.ALMOST_SORTED: "Almost Sorted",
        }
        return mode_str[self._mode]


if __name__ == "__main__":
    main()
