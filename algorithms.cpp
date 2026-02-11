#include "algorithms.hpp"

bool selectionSort(std::array<int, SIZE> &array, int step) {
    int min = step;

    for (int i = step + 1; i < array.size(); i++) {
        if (array[i] < array[min]) {
            min = i;
        }
    }

    std::swap(array[min], array[step]);

    return false;
}

bool bogoSort(std::array<int, SIZE> &array, int step) {
    if (std::is_sorted(array.begin(), array.end())) {
        return true;
    }

    std::shuffle(array.begin(), array.end(),
                  std::default_random_engine(std::time(0)));

    return false;
}
