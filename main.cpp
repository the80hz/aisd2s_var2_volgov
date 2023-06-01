#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "CustomSet.h"

/**
 * @brief Linear congruential generator
 * @return random number
 */
size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

/**
 * @brief Test container
 * @tparam Container container type
 * @param containerName container name
 * @param containerSize container size
 * @param fillAttempts number of attempts to fill container
 * @param searchAttempts number of attempts to search in container
 * @param addRemoveAttempts number of attempts to add/remove from container
 * @param insertOp insert operation
 * @param findOp find operation
 */
template<typename Container>
void testContainer(const std::string& containerName, int containerSize, int fillAttempts,
                   int searchAttempts, int addRemoveAttempts,
                   std::function<void(Container&, int)> insertOp, std::function<bool(Container&, int)> findOp) {
    using namespace std::chrono;


    Container container;
    int64_t totalTimeFill = 0;
    int64_t totalTimeSearch = 0;
    int64_t totalTimeAddRemove = 0;

    for (int i = 0; i < fillAttempts; ++i) {
        Container tmpContainer;
        auto startFill = steady_clock::now();
        for (int j = 0; j < containerSize; ++j) {
            int randomNum = lcg();
            if (!findOp(tmpContainer, randomNum)) {
                insertOp(tmpContainer, randomNum);
            }
        }
        auto endFill = steady_clock::now();
        totalTimeFill += duration_cast<microseconds>(endFill - startFill).count();
        container = tmpContainer;
    }

    for (int i = 0; i < searchAttempts; ++i) {
        auto startSearch = steady_clock::now();
        findOp(container, lcg());
        auto endSearch = steady_clock::now();
        totalTimeSearch += duration_cast<microseconds>(endSearch - startSearch).count();
    }

    for (int i = 0; i < addRemoveAttempts; ++i) {
        int randomNum = lcg();

        auto startAddRemove = steady_clock::now();
        bool found = findOp(container, randomNum);
        if (!found) {
            insertOp(container, randomNum);
        } else {
            // Remove operation not required for CustomSet, only for std::vector
            if constexpr (std::is_same_v<Container, std::vector<int>>) {
                container.erase(std::remove(container.begin(), container.end(), randomNum), container.end());
            }
        }
        auto endAddRemove = steady_clock::now();
        totalTimeAddRemove += duration_cast<microseconds>(endAddRemove - startAddRemove).count();
    }

    std::cout << containerName << " size: " << containerSize << std::endl;
    std::cout << "Average fill time: " << (totalTimeFill / static_cast<double>(fillAttempts)) << " microseconds" << std::endl;
    std::cout << "Average search time: " << (totalTimeSearch / static_cast<double>(searchAttempts)) << " microseconds" << std::endl;
    std::cout << "Average add/remove time: " << (totalTimeAddRemove / static_cast<double>(addRemoveAttempts)) << " microseconds" << std::endl;
    std::cout << std::endl;
}

/**
 * @brief Function for CustomSet and std::vector containers with different sizes
 * @param set1 first set
 * @param set2 second set
 * @return set containing elements from both sets
 */
CustomSet customSetUnion(const CustomSet& set1, const CustomSet& set2) { // Union of two sets
    CustomSet result = set1; // Copy the elements of set1 into result
    for (int key : set2.getSortedElements()) { // Iterate over the elements of set2
        result.insert(key); // Insert the elements of set2 into result, duplicates will be ignored
    }
    return result; // Return the result
}

/**
 * @brief Function for CustomSet and std::vector containers with different sizes
 * @param set1 first set
 * @param set2 second set
 * @return set containing elements that are in both sets
 */
CustomSet customSetSymmetricDifference(const CustomSet& set1, const CustomSet& set2) { // Symmetric difference of two sets
    CustomSet result; // Create an empty set
    for (int key : set1.getSortedElements()) { // Iterate over the elements of set1
        if (!set2.contains(key)) { // If the element is not in set2
            result.insert(key); // Insert elements from set1 that are not in set2
        }
    }
    for (int key : set2.getSortedElements()) { // Iterate over the elements of set2
        if (!set1.contains(key)) { // If the element is not in set1
            result.insert(key); // Insert elements from set2 that are not in set1
        }
    }
    return result; // Return the result
}

/**
 * @brief Test function for CustomSet and std::vector containers with different sizes
 */
void test1(){
    int fillAttempts = 100;
    int searchAttempts = 1000;
    int addRemoveAttempts = 1000;

    testContainer<CustomSet>("CustomSet", 1000, fillAttempts, searchAttempts, addRemoveAttempts,
                             [](CustomSet& container, int value) { container.insert(value); },
                             [](CustomSet& container, int value) { return container.contains(value); });

    testContainer<std::vector<int>>("std::vector<int>", 1000, fillAttempts, searchAttempts, addRemoveAttempts,
                                    [](std::vector<int>& container, int value) { container.insert(container.end(), value); },
                                    [](std::vector<int>& container, int value) { return std::find(container.begin(), container.end(), value) != container.end(); });
    testContainer<CustomSet>("CustomSet", 10000, fillAttempts, searchAttempts, addRemoveAttempts,
                             [](CustomSet& container, int value) { container.insert(value); },
                             [](CustomSet& container, int value) { return container.contains(value); });

    testContainer<std::vector<int>>("std::vector<int>", 10000, fillAttempts, searchAttempts, addRemoveAttempts,
                                    [](std::vector<int>& container, int value) { container.insert(container.end(), value); },
                                    [](std::vector<int>& container, int value) { return std::find(container.begin(), container.end(), value) != container.end(); });
    testContainer<CustomSet>("CustomSet", 100000, fillAttempts, searchAttempts, addRemoveAttempts,
                             [](CustomSet& container, int value) { container.insert(value); },
                             [](CustomSet& container, int value) { return container.contains(value); });

    testContainer<std::vector<int>>("std::vector<int>", 100000, fillAttempts, searchAttempts, addRemoveAttempts,
                                    [](std::vector<int>& container, int value) { container.insert(container.end(), value); },
                                    [](std::vector<int>& container, int value) { return std::find(container.begin(), container.end(), value) != container.end(); });
}

/**
 * @brief Main function
 * @return exit code
 */
int main() {

    return 0;
}
