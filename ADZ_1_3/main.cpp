// ID 19528537
// 1_3. Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
// Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
// n, m ≤ 100000.

#include <iostream>

size_t input_arr(int **array);

size_t sums_equals_to(const int *series1, const int *series2, \
                        size_t len1, size_t len2, size_t k);

int main() {
    // ввод двух строго возрастающих массивов
    int *series1;
    size_t len1 = input_arr(&series1);
    int *series2;
    size_t len2 = input_arr(&series2);

    size_t k = 0;  // чему равна сумма двух элементов
    std::cin >> k;
    // вывод колличества пар подходящих индексов
    std::cout << sums_equals_to(series1, series2, len1, len2, k) << std::endl;

    delete[] series1;
    delete[] series2;
    return 0;
}


size_t input_arr(int **array) {
    size_t len = 0;
    std::cin >> len;
    int *series = new int[len];
    for (size_t i = 0; i < len; i++) {
        std::cin >> series[i];
    }
    *array = series;
    return len;
}

size_t sums_equals_to(const int *series1, const int *series2, \
                        size_t len1, size_t len2, size_t k) {
    size_t count_equals = 0;
    ssize_t j_max = len2 - 1;  // инекс правой границы второго массива

    // проход второго массива по частям
    for (size_t i = 0; i < len1; ++i) {
        for (ssize_t j = j_max; j > -1; --j) {
            int res = series1[i] + series2[j];
            if (res == k) {
                count_equals++;
                j_max = j - 1;
                break;
            } else if (res < k) {
                break;
            }
        }
    }
    return count_equals;
}
