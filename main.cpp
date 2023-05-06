/* 1) Реализовать алгоритмы сортировки для массивов целых чисел сортировкой выбором и быстрой сортировкой.
 * 2) Посчитать число сравнений и число копирований объектов для массивов длины 1000, 2000, 3000, …, 10000,
 *  25000, 50000, 100000:
 *  а) в среднем (сгенерировать 100 случайных массивов и посчитать средние значения);
 *  б) для полностью отсортированного массива;
 *  в) для обратно отсортированного массива.
 *
 * Минимальные требования:
 * Запрещено использование функций из заголовочных файлов <alogprithm> и <numeric>.
 * Функции сортировки должны возвращать структуру stats:
 * struct stats {
 *  size_t comparison_count = 0;
 *  size_t copy_count = 0;
 * };
 * Функции сортировки должны принимать std::vector<int> - сортируемый набор элементов.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

// Сортировка выбором
stats selection_sort(std::vector<int> &array) {
    stats result;
    for (size_t i = 0; i < array.size() - 1; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < array.size(); ++j) {
            ++result.comparison_count;
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        ++result.copy_count;
        std::swap(array[i], array[min_index]);
    }
    return result;
}

// Быстрая сортировка
stats quick_sort(std::vector<int> &array) {
    stats result;
    if (array.size() < 2) {
        return result;
    }
    int pivot = array[array.size() / 2];
    std::vector<int> less;
    std::vector<int> greater;
    for (size_t i = 0; i < array.size(); ++i) {
        ++result.comparison_count;
        if (array[i] < pivot) {
            ++result.copy_count;
            less.push_back(array[i]);
        } else if (array[i] > pivot) {
            ++result.copy_count;
            greater.push_back(array[i]);
        }
    }
    stats less_stats = quick_sort(less);
    stats greater_stats = quick_sort(greater);
    result.comparison_count += less_stats.comparison_count + greater_stats.comparison_count;
    result.copy_count += less_stats.copy_count + greater_stats.copy_count;
    std::copy(less.begin(), less.end(), array.begin());
    array[less.size()] = pivot;
    std::copy(greater.begin(), greater.end(), array.begin() + less.size() + 1);
    return result;
}

// Генератор случайных чисел
std::vector<int> generate_random_array(size_t size) {
    std::vector<int> result(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000000);
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

// Среднее значение
double average(std::vector<double> &array) {
    double result = 0;
    for (size_t i = 0; i < array.size(); ++i) {
        result += array[i];
    }
    return result / array.size();
}

// Статистика
struct statistics {
    double average_comparison_count = 0;
    double average_copy_count = 0;
};

// Статистика для массива
statistics get_statistics(std::vector<int> &array, size_t count) {
    std::vector<double> comparison_count(count);
    std::vector<double> copy_count(count);
    for (size_t i = 0; i < count; ++i) {
        std::vector<int> copy = array;
        stats result = selection_sort(copy);
        comparison_count[i] = result.comparison_count;
        copy_count[i] = result.copy_count;
    }
    statistics result;
    result.average_comparison_count = average(comparison_count);
    result.average_copy_count = average(copy_count);
    return result;
}

int main() {
    std::vector<size_t> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000,
                                 8000, 9000, 10000, 25000, 50000, 100000};
    std::vector<statistics> selection_sort_statistics(sizes.size());
    std::vector<statistics> quick_sort_statistics(sizes.size());
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::vector<int> random_array = generate_random_array(sizes[i]);
        std::vector<int> sorted_array = generate_sorted_array(sizes[i]);
        std::vector<int> reverse_sorted_array = generate_reverse_sorted_array(sizes[i]);
        selection_sort_statistics[i] = get_statistics(random_array, 100);
        quick_sort_statistics[i] = get_statistics(random_array, 100);
    }
    std::cout << "Размер массива\tСравнений\tКопирований\tСравнений\tКопирований\n";
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout << sizes[i] << "\t\t\t" << selection_sort_statistics[i].average_comparison_count << "\t\t\t"
                  << selection_sort_statistics[i].average_copy_count << "\t\t\t"
                  << quick_sort_statistics[i].average_comparison_count << "\t\t\t"
                  << quick_sort_statistics[i].average_copy_count << "\n";
    }

    return 0;
}