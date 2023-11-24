from enum import Enum
import numpy as np

def main() -> None:
    max_value = 99999999
    min_value = -99999999
    num_elements = 1000000
    dataset_100k_asc = DatasetGenerator(num_elements, min_value, max_value, DatasetGeneratorMode.ASCENDING)

    dataset_100k_asc.generate()
    dataset_100k_asc.write_to_text("data_asc_100k.txt")

    dataset_100k_desc = DatasetGenerator(num_elements, min_value, max_value, DatasetGeneratorMode.DESCENDING)
    dataset_100k_desc.generate()
    dataset_100k_desc.write_to_text("data_desc_100k.txt")

    dataset_100k_almost_sorted = DatasetGenerator(num_elements, min_value, max_value, DatasetGeneratorMode.ALMOST_SORTED)
    dataset_100k_almost_sorted.generate()
    dataset_100k_almost_sorted.write_to_text("data_almost_sorted_100k.txt")

    dataset_100k_random = DatasetGenerator(num_elements, min_value, max_value, DatasetGeneratorMode.RANDOM)
    dataset_100k_random.generate()
    dataset_100k_random.write_to_text("data_random_100k.txt")



class DatasetGeneratorMode(Enum):
    RANDOM = 0
    ASCENDING = 1
    DESCENDING = 2
    ALMOST_SORTED = 3

class DatasetGenerator:
    def __init__(self, num_elements: int, min_value: int, max_value: int, mode: DatasetGeneratorMode):
        if (mode not in DatasetGeneratorMode):
            raise ValueError("Invalid mode for DatasetGenerator")
        self._num_elements = num_elements
        self._min_value = min_value
        self._max_value = max_value
        self._mode = mode
        self._rng_engine = np.random.Generator(np.random.PCG64DXSM())
        self.data = np.empty(num_elements, dtype=np.int64)

    def generate(self) -> np.ndarray:
        
        # First generate a random array for us to work with
        self.data = self._rng_engine.integers(low=self._min_value, high=self._max_value, size=self._num_elements)

        # Now sort the array based on the mode
        if (self._mode == DatasetGeneratorMode.RANDOM):
            self.data = self._rng_engine.permutation(self.data)
        elif (self._mode == DatasetGeneratorMode.ASCENDING):
            self.data = np.sort(self.data)
        elif (self._mode == DatasetGeneratorMode.DESCENDING):
            self.data = np.sort(self.data)[::-1]
        elif (self._mode == DatasetGeneratorMode.ALMOST_SORTED):
            # For this, we should the array in ascending order.
            # Then, we swap a couple of elements in the array, by randomize the index
            # of the elements to swap.
            # We will swap 20% of the elements in the array.
            self.data = np.sort(self.data)
            num_elements_to_swap = int(self._num_elements * 0.2)
            indices_to_swap = self._rng_engine.choice(self._num_elements, size=num_elements_to_swap, replace=False)
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
            DatasetGeneratorMode.ALMOST_SORTED: "Almost Sorted"
                }
        return mode_str[self._mode]





if __name__ == '__main__':
    main()
