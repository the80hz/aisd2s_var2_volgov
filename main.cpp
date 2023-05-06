#include <iostream>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

void selection_sort(std::vector<int>& arr, stats& st) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; j++) {
            st.comparison_count++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
            st.copy_count += 3;
        }
    }
}

size_t partition(std::vector<int>& arr, size_t low, size_t high, stats& st) {
    int pivot = arr[high];
    size_t i = low - 1;
    for (size_t j = low; j < high; j++) {
        st.comparison_count++;
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            st.copy_count += 3;
        }
    }
    std::swap(arr[i+1], arr[high]);
    st.copy_count += 3;
    return i+1;
}

void quicksort(std::vector<int>& arr, size_t low, size_t high, stats& st) {
    if (low < high) {
        size_t p = partition(arr, low, high, st);
        quicksort(arr, low, p - 1, st);
        quicksort(arr, p + 1, high, st);
    }
}

void quick_sort(std::vector<int>& arr, stats& st) {
    quicksort(arr, 0, arr.size() - 1, st);
}

int main() {
    std::vector<int> arr = {5, 3, 8, 2, 9, 1, 7, 4, 6};
    stats st;

    // Сортировка выбором
    selection_sort(arr, st);
    for (auto x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    std::cout << "Comparison count: " << st.comparison_count << "\n";
    std::cout << "Copy count: " << st.copy_count << "\n";

    // Быстрая сортировка
    quick_sort(arr, st);
    for (auto x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    std::cout << "Comparison count: " << st.comparison_count << "\n";
    std::cout << "Copy count: " << st.copy_count << "\n";

    return 0;
}
