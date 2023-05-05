#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
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
    using namespace std::chrono; // for std::chrono functions

    Container container;            // Container to test
    duration<double, std::milli> totalTimeFill{};       // Total time for filling container
    duration<double, std::milli> totalTimeSearch{};     // Total time for searching in container
    duration<double, std::milli> totalTimeAddRemove{};  // Total time for adding/removing from container

    // Fill container
    for (int i = 0; i < fillAttempts; ++i) {
        Container tmpContainer;                             // Temporary container for filling
        auto startFill = steady_clock::now();  // Start time
        for (int j = 0; j < containerSize; ++j) {
            int randomNum = lcg();                          // Random number
            insertOp(tmpContainer, randomNum);          // Insert number
        }
        auto endFill = steady_clock::now();    // End time
        totalTimeFill += duration_cast<duration<double, std::milli>>(endFill - startFill); // Add time to total time
        container = tmpContainer;                          // Copy temporary container to container
    }

    // Search in container
    for (int i = 0; i < searchAttempts; ++i) {
        auto startSearch = steady_clock::now(); // Start time
        findOp(container, lcg());                            // Search for random number
        auto endSearch = steady_clock::now();   // End time
        totalTimeSearch += duration_cast<duration<double, std::milli>>(endSearch - startSearch); // Add time to total time
    }

    // Add/remove from container
    for (int i = 0; i < addRemoveAttempts; ++i) {
        int randomNum = lcg(); // Random number

        auto startAddRemove = steady_clock::now(); // Start time
        bool found = findOp(container, randomNum);              // Search for random number
        if (!found) {                                           // If number is not in container
            insertOp(container, randomNum);                     // Insert number
        } else {
            // Remove operation not required for CustomSet, only for std::vector
            if constexpr (std::is_same_v<Container, std::vector<int>>) {
                container.erase(std::remove(container.begin(),
                                            container.end(), randomNum), container.end());    // Remove number
            }
        }
        auto endAddRemove = steady_clock::now();    // End time
        totalTimeAddRemove += duration_cast<duration<double, std::milli>>(endAddRemove - startAddRemove); // Add time to total time
    }

    std::cout << containerName << " size: " << containerSize << std::endl;
    std::cout << "Average fill time: " << totalTimeFill.count() / fillAttempts << " ms" << std::endl;
    std::cout << "Average search time: " << totalTimeSearch.count() / searchAttempts << " ms" << std::endl;
    std::cout << "Average add/remove time: " << totalTimeAddRemove.count() / addRemoveAttempts << " ms" << std::endl;
    std::cout << std::endl;
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

void printMenu() {
    std::cout << "Please choose an option from the menu:\n";
    std::cout << "1. Create a new tree\n";
    std::cout << "2. Copy a tree\n";
    std::cout << "3. Print a tree\n";
    std::cout << "4. Insert an element into a tree\n";
    std::cout << "5. Check if an element is in a tree\n";
    std::cout << "6. Delete an element from a tree\n";
    std::cout << "7. Union of two trees\n";
    std::cout << "8. Symmetric difference of two trees\n";
    std::cout << "9. Exit\n";
}

int main() {
    test1();
    std::map<int, CustomSet> trees;
    int idCounter = 1;

    while (true) {
        printMenu();

        int choice;
        std::cin >> choice;

        int id, id2;
        int element;

        switch (choice) {
            case 1:
                trees[idCounter] = CustomSet();
                std::cout << "Created tree with ID: " << idCounter << std::endl;
                idCounter++;
                break;
            case 2:
                std::cout << "Enter the ID of the tree to copy: ";
                std::cin >> id;
                if (trees.find(id) == trees.end()) {
                    std::cout << "Tree not found.\n";
                } else {
                    trees[idCounter] = CustomSet(trees[id]);
                    std::cout << "Copied tree with ID: " << id << " to tree with ID: " << idCounter << std::endl;
                    idCounter++;
                }
                break;
            case 3:
                std::cout << "Enter the ID of the tree to print: ";
                std::cin >> id;
                if (trees.find(id) == trees.end()) {
                    std::cout << "Tree not found.\n";
                } else {
                    trees[id].print();
                }
                break;
            case 4:
                std::cout << "Enter the ID of the tree to insert the element into: ";
                std::cin >> id;
                std::cout << "Enter the element to insert: ";
                std::cin >> element;
                if (trees.find(id) == trees.end()) {
                    std::cout << "Tree not found.\n";
                } else {
                    trees[id].insert(element);
                    std::cout << "Inserted element " << element << " into tree with ID: " << id << std::endl;
                }
                break;
            case 5:
                std::cout << "Enter the ID of the tree to check for the presence of an element: ";
                std::cin >> id;
                std::cout << "Enter the element to check: ";
                std::cin >> element;
                if (trees.find(id) == trees.end()) {
                    std::cout << "Tree not found.\n";
                } else {
                    bool found = trees[id].contains(element);
                    if (found) {
                        std::cout << "Element " << element << " is present in tree with ID: " << id << std::endl;
                    } else {
                        std::cout << "Element " << element << " is not present in tree with ID: " << id << std::endl;
                    }
                }
                break;
            case 6:
                std::cout << "Enter the ID of the tree to delete an element from: ";
                std::cin >> id;
                std::cout << "Enter the element to delete: ";
                std::cin >> element;
                if (trees.find(id) == trees.end()) {
                    std::cout << "Tree not found.\n";
                } else {
                    bool deleted = trees[id].erase(element);
                    if (deleted) {
                        std::cout << "Deleted element " << element << " from tree with ID: " << id << std::endl;
                    } else {
                        std::cout << "Element " << element << " not found in tree with ID: " << id << std::endl;
                    }
                }
                break;
            case 7:
                std::cout << "Enter the IDs of the trees to perform the union operation: ";
                std::cin >> id >> id2;
                if (trees.find(id) == trees.end() || trees.find(id2) == trees.end()) {
                    std::cout << "One or both tree IDs not found.\n";
                } else {
                    trees[idCounter] = customSetUnion(trees[id], trees[id2]);
                    std::cout << "Created new tree with ID: " << idCounter << " as the union of trees with IDs: " << id << " and " << id2 << std::endl;
                    idCounter++;
                }
                break;
            case 8:
                std::cout << "Enter the IDs of the trees to perform the symmetric difference operation: ";
                std::cin >> id >> id2;
                if (trees.find(id) == trees.end() || trees.find(id2) == trees.end()) {
                    std::cout << "One or both tree IDs not found.\n";
                } else {
                    trees[idCounter] = customSetSymmetricDifference(trees[id], trees[id2]);
                    std::cout << "Created new tree with ID: " << idCounter << " as the symmetric difference of trees with IDs: " << id << " and " << id2 << std::endl;
                    idCounter++;
                }
                break;
            case 9:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
