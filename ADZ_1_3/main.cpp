#include <iostream>

size_t input_arr(int **array);
size_t sums_equals_to(const int* series1, const int* series2, size_t len1, size_t len2, size_t k);


int main() {

    // заполнение первого массива
    int* series1;
    size_t len1 = input_arr(&series1);
    // заполнение второго массива
    int* series2;
    size_t len2 = input_arr(&series2);

    size_t k = 0;
    std::cin >> k;
    std::cout << sums_equals_to(series1, series2, len1, len2, k) << std::endl;

    delete[] series1;
    delete[] series2;
    return 0;
}


size_t input_arr(int **array) {
    size_t len = 0;
    std::cin >> len;
    int* series = new int[len];
    for (size_t i = 0; i < len; i++) {
        std::cin >> series[i];
    }
    *array = series;
    return len;
}

size_t sums_equals_to(const int* series1, const int* series2, size_t len1, size_t len2, size_t k) {
    size_t count_equals = 0;
    size_t j_max = len2 - 1;

    for (size_t i = 0; i < len1; ++i) {
        for (int j = j_max; j > -1; --j) {
            int res = series1[i] + series2[j];
            if (res == k) {
                count_equals++;
                j_max = j - 1;
                break; // конец итерации
            } else if (res < k) {
                break; // конец итерации
            }
        }
    }
    return count_equals;
}