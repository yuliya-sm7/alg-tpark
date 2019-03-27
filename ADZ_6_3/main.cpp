/* Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 * Требуется найти k-ю порядковую статистику.
 * т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 * Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).

 * 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */

#include <iostream>


size_t Partition(int *array, size_t left, size_t right) {
    if (left == right)
        return left;

    // srand(2);
    size_t rand_pivot_index = left + (rand() % (right - left));
    int pivot = array[rand_pivot_index];  // выбор случайного разделителя
    std::swap(array[rand_pivot_index], array[right]); // перемещаем пивот в крайнее левое положение

    //проход двумя итераторами от начала массива к концу
    size_t i = left;  // указывает на начало группы элементов, строго бОльших опорного
    size_t j = left;  // указывает на первый нерассмотренный элемент
    for (; j < right; j++) {
        if (array[j] <= pivot) {
            std::swap(array[i], array[j]);
            i++;
        }
    }
    std::swap(array[i], array[j]);
    return i;
}

// Поиск k-ой порядковой статистики, возвращаем её значение
int K_statistic(int *array, size_t size, size_t k) {
    size_t left = 0;
    size_t right = size - 1;
    size_t pivot_index;

    do {
        pivot_index = Partition(array, left, right);
        if (pivot_index < k) {
            left = pivot_index + 1;
        } else {
            right = pivot_index;
        }
    } while (pivot_index != k);
    return array[k];
}


int main() {
    size_t n, k;
    std::cin >> n >> k;

    int *array = new int[n];
    for (size_t i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    int result = K_statistic(array, n, k);
    std::cout << result << std::endl;

    delete[] array;
    return 0;
}