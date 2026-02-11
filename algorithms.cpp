// Aidan Carey, Feburary 2026, algorithms.cpp

#include "algorithms.hpp"

void selectionSort(std::array<int, SIZE> &array, int step) {
  int min = step;

  for (int i = step + 1; i < array.size(); i++) {
    if (array[i] < array[min]) {
      min = i;
    }
  }

  std::swap(array[min], array[step]);
}

void bogoSort(std::array<int, SIZE> &array, int step) {
  std::shuffle(array.begin(), array.end(),
               std::default_random_engine(std::time(0)));
}
