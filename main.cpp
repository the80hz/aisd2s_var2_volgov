/* 1) Реализовать алгоритмы сортировки для массивов целых чисел сортировкой выбором и быстрой сортировкой.
 * 2) Посчитать число сравнений и число копирований объектов для массивов длины 1000, 2000, 3000, …, 10000,
 *  25000, 50000, 100000:
 *  а) в среднем (сгенерировать 100 случайных массивов и посчитать средние значения);
 *  б) для полностью отсортированного массива;
 *  в) для обратно отсортированного массива.
 *
 * Минимальные требования:
 * Запрещено использование функций из заголовочных файлов <algorithm> и <numeric>.
 * Функции сортировки должны возвращать структуру stats:
 * struct stats {
 *  size_t comparison_count = 0;
 *  size_t copy_count = 0;
 * };
 * Функции сортировки должны принимать std::vector<int> - сортируемый набор элементов.
 */

#include <random>
#include <iostream>
#include <fstream>
#include <vector>


struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

// Сортировка выбором
stats selection_sort(std::vector<int>& array) {
    stats sort_stats;

    for (size_t i = 0; i < array.size() - 1; ++i) {
        size_t min_index = i;

        for (size_t j = i + 1; j < array.size(); ++j) {
            ++sort_stats.comparison_count;
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            std::swap(array[i], array[min_index]);
            ++sort_stats.copy_count;
        }
    }

    return sort_stats;
}

size_t partition(std::vector<int>& arr, size_t low, size_t high, stats& sort_stats) {
    int pivot = arr[high];
    size_t i = low - 1;

    for (size_t j = low; j <= high - 1; ++j) {
        ++sort_stats.comparison_count;
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
            ++sort_stats.copy_count;
        }
    }

    std::swap(arr[i + 1], arr[high]);
    ++sort_stats.copy_count;

    return i + 1;
}

void quickSort(std::vector<int>& arr, size_t low, size_t high, stats& sort_stats) {
    if (low < high) {
        size_t pivot_index = partition(arr, low, high, sort_stats);

        quickSort(arr, low, pivot_index - 1, sort_stats);
        quickSort(arr, pivot_index + 1, high, sort_stats);
    }
}

stats quick_sort(std::vector<int>& arr) {
    stats sort_stats;
    quickSort(arr, 0, arr.size() - 1, sort_stats);
    return sort_stats;
}


// Генератор случайных чисел
std::vector<int> generate_random_array(size_t size) {
    std::vector<int> result(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size-1);
    for (size_t i = 0; i < size; ++i) {
        result[i] = dis(gen);
    }
    return result;
}


// Генератор отсортированных чисел
std::vector<int> generate_sorted_array(size_t size) {
    std::vector<int> result(size);
    for (size_t i = 0; i < size; ++i) {
        result[i] = i;
    }
    return result;
}

// Генератор обратно отсортированных чисел
std::vector<int> generate_reverse_sorted_array(size_t size) {
    std::vector<int> result(size);
    for (size_t i = 0; i < size; ++i) {
        result[i] = size - i;
    }
    return result;
}


// Function to calculate the average of a vector
double calculate_average(const std::vector<double>& array) {
    double sum = 0;
    for (double value : array) {
        sum += value;
    }
    return sum / array.size();
}

// Function to perform the testing and write results to a CSV file
void perform_testing(const std::string& filename) {
    std::vector<size_t> sizes = { 50 };

    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    outfile << "Array Size,Comparison Count (Selection Sort - Random),Copy Count (Selection Sort - Random),Comparison Count (Selection Sort - Sorted),Copy Count (Selection Sort - Sorted),Comparison Count (Selection Sort - Reverse Sorted),Copy Count (Selection Sort - Reverse Sorted),Comparison Count (Quick Sort - Random),Copy Count (Quick Sort - Random),Comparison Count (Quick Sort - Sorted),Copy Count (Quick Sort - Sorted),Comparison Count (Quick Sort - Reverse Sorted),Copy Count (Quick Sort - Reverse Sorted)\n";

    for (size_t size : sizes) {
        std::cout << std::endl << size << std::endl;
        std::vector<double> selection_random_comparison_counts;
        std::vector<double> selection_random_copy_counts;
        std::vector<double> selection_sorted_comparison_counts;
        std::vector<double> selection_sorted_copy_counts;
        std::vector<double> selection_reverse_sorted_comparison_counts;
        std::vector<double> selection_reverse_sorted_copy_counts;

        std::vector<double> quick_random_comparison_counts;
        std::vector<double> quick_random_copy_counts;
        std::vector<double> quick_sorted_comparison_counts;
        std::vector<double> quick_sorted_copy_counts;
        std::vector<double> quick_reverse_sorted_comparison_counts;
        std::vector<double> quick_reverse_sorted_copy_counts;

        for (size_t i = 0; i < 100; ++i) {
            std::cout << i << " ";
            std::vector<int> random_array = generate_random_array(size);

            stats selection_random_stats = selection_sort(random_array);
            selection_random_comparison_counts.push_back(selection_random_stats.comparison_count);
            selection_random_copy_counts.push_back(selection_random_stats.copy_count);

            stats quick_random_stats = quick_sort(random_array);
            quick_random_comparison_counts.push_back(quick_random_stats.comparison_count);
            quick_random_copy_counts.push_back(quick_random_stats.copy_count);


        }
        std::vector<int> sorted_array = generate_sorted_array(size);
        std::vector<int> reverse_sorted_array = generate_reverse_sorted_array(size);

        stats selection_sorted_stats = selection_sort(sorted_array);
        selection_sorted_comparison_counts.push_back(selection_sorted_stats.comparison_count);
        selection_sorted_copy_counts.push_back(selection_sorted_stats.copy_count);

        stats selection_reverse_sorted_stats = selection_sort(reverse_sorted_array);
        selection_reverse_sorted_comparison_counts.push_back(selection_reverse_sorted_stats.comparison_count);
        selection_reverse_sorted_copy_counts.push_back(selection_reverse_sorted_stats.copy_count);

        stats quick_sorted_stats = quick_sort(sorted_array);
        quick_sorted_comparison_counts.push_back(selection_sorted_stats.comparison_count);
        quick_sorted_copy_counts.push_back(quick_sorted_stats.copy_count);

        stats quick_reverse_sorted_stats = quick_sort(reverse_sorted_array);
        quick_reverse_sorted_comparison_counts.push_back(quick_reverse_sorted_stats.comparison_count);
        quick_reverse_sorted_copy_counts.push_back(quick_reverse_sorted_stats.copy_count);

        outfile << size << ","
                << calculate_average(selection_random_comparison_counts) << ","
                << calculate_average(selection_random_copy_counts) << ","
                << calculate_average(selection_sorted_comparison_counts) << ","
                << calculate_average(selection_sorted_copy_counts) << ","
                << calculate_average(selection_reverse_sorted_comparison_counts) << ","
                << calculate_average(selection_reverse_sorted_copy_counts) << ","
                << calculate_average(quick_random_comparison_counts) << ","
                << calculate_average(quick_random_copy_counts) << ","
                << calculate_average(quick_sorted_comparison_counts) << ","
                << calculate_average(quick_sorted_copy_counts) << ","
                << calculate_average(quick_reverse_sorted_comparison_counts) << ","
                << calculate_average(quick_reverse_sorted_copy_counts) << "\n";
    }

    outfile.close();

    std::cout << "Testing completed. Results are saved in " << filename << std::endl;
}


// Function to display the menu
void show_menu() {
    std::cout << "Menu:\n";
    std::cout << "1. Compare sorting algorithms for a random array\n";
    std::cout << "2. Compare sorting algorithms for a sorted array\n";
    std::cout << "3. Compare sorting algorithms for a reverse sorted array\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::string filename = "sorting_results.csv";
    perform_testing(filename);

    /*
    while (true) {
        show_menu();

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice >= 1 && choice <= 3) {
            size_t array_size;
            std::cout << "Enter the array size: ";
            std::cin >> array_size;

            std::vector<int> array;
            std::string array_type;

            if (choice == 1) {
                array = generate_random_array(array_size);
                array_type = "random";
            } else if (choice == 2) {
                array = generate_sorted_array(array_size);
                array_type = "sorted";
            } else if (choice == 3) {
                array = generate_reverse_sorted_array(array_size);
                array_type = "reverse sorted";
            }

            stats selection_sort_stats = selection_sort(array);
            stats quick_sort_stats = quick_sort(array);

            std::cout << "Comparisons and copies for a " << array_type << " array of size " << array_size << ":\n";
            std::cout << "Selection Sort:\n";
            std::cout << "Comparison count: " << selection_sort_stats.comparison_count << std::endl;
            std::cout << "Copy count: " << selection_sort_stats.copy_count << std::endl;

            std::cout << "Quick Sort:\n";
            std::cout << "Comparison count: " << quick_sort_stats.comparison_count << std::endl;
            std::cout << "Copy count: " << quick_sort_stats.copy_count << std::endl;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << std::endl;
    }*/

    return 0;
}