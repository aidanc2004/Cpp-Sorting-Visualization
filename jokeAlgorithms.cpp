#include "algorithms.hpp" // for SIZE
#include "jokeAlgorithms.hpp"

bool bogoSort(std::array<int, SIZE> &array, int step) {
    if (std::is_sorted(array.begin(), array.end())) {
        return true;
    }

    std::shuffle(array.begin(), array.end(),
                  std::default_random_engine(std::time(0)));

    return false;
}
