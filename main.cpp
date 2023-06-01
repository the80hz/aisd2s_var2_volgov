#include <iostream>
#include <chrono>
#include "CustomSet.h"

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

void testContainer(int containerSize, int fillAttempts, int searchAttempts, int addRemoveAttempts) {
    using namespace std::chrono;

    CustomSet container;
    int64_t totalTimeFill = 0;
    int64_t totalTimeSearch = 0;
    int64_t totalTimeAddRemove = 0;

    for (int i = 0; i < fillAttempts; ++i) {
        CustomSet tmpContainer;
        auto startFill = steady_clock::now();
        for (int j = 0; j < containerSize; ++j) {
            tmpContainer.insert(lcg());
        }
        auto endFill = steady_clock::now();
        totalTimeFill += duration_cast<microseconds>(endFill - startFill).count();
        container = tmpContainer;
    }

    for (int i = 0; i < searchAttempts; ++i) {
        auto startSearch = steady_clock::now();
        container.contains(lcg());
        auto endSearch = steady_clock::now();
        totalTimeSearch += duration_cast<microseconds>(endSearch - startSearch).count();
    }

    for (int i = 0; i < addRemoveAttempts; ++i) {
        int randomNum = lcg();

        auto startAddRemove = steady_clock::now();
        container.insert(randomNum);
        container.erase(randomNum);
        auto endAddRemove = steady_clock::now();
        totalTimeAddRemove += duration_cast<microseconds>(endAddRemove - startAddRemove).count();
    }

    std::cout << "Container size: " << containerSize << std::endl;
    std::cout << "Average fill time: " << (totalTimeFill / static_cast<double>(fillAttempts)) << " microseconds" << std::endl;
    std::cout << "Average search time: " << (totalTimeSearch / static_cast<double>(searchAttempts)) << " microseconds" << std::endl;
    std::cout << "Average add/remove time: " << (totalTimeAddRemove / static_cast<double>(addRemoveAttempts)) << " microseconds" << std::endl;
    std::cout << std::endl;
}

int main() {
    int fillAttempts = 100;
    int searchAttempts = 1000;
    int addRemoveAttempts = 1000;

    testContainer(1000, fillAttempts, searchAttempts, addRemoveAttempts);
    testContainer(10000, fillAttempts, searchAttempts, addRemoveAttempts);
    testContainer(100000, fillAttempts, searchAttempts, addRemoveAttempts);

    return 0;
}
