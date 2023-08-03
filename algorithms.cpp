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