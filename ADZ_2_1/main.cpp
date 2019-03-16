/*
 * 2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A,
 * равного или превосходящего B[i]: A[k] >= B[i].
 * Если такого элемента нет, выведите n.
 * Время работы поиска k для каждого элемента B[i]: O(log(k)).
 * n, m ≤ 10000.
 * Формат входных данных.
 * В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.
 */

#include <iostream>

bool input_arr(int *&A, int *&B, size_t &n, size_t &m) {
    std::cin >> n >> m;
    if (n == 0 || m == 0)
        return false;
    A = new int[n];
    for (size_t i = 0; i < n; ++i)
        std::cin >> A[i];
    B = new int[m];
    for (size_t i = 0; i < m; ++i)
        std::cin >> B[i];
    return true;
}

void delete_input_arr(int A[], int B[]) {
    delete[] A;
    delete[] B;
}


// Бинарный поиск в диапазоне элемента, большего или равного element
ssize_t binary_check(int element, const int *array, ssize_t begin, ssize_t end) {
    ssize_t length = end - begin;
    while (length > 1) {
        if (element > array[begin + length / 2]) {
            begin += length / 2;
        } else {
            end -= length / 2;
        }
        length = end - begin;
    }
    // Если элемент не найден, возвращаем -1
    return array[end] >= element ? end : -1;
}


// Поиск первого элемента массива array, который больше или равен element
size_t greater_or_equal(int elem[], int *array, size_t size) {
    for (size_t i = 0; i < m; ++i) {
        ssize_t begin = -1;
        ssize_t end = 0;
        ssize_t k = -1;
        while (k < 0 && end < size) {
            end = (begin + 1) * 2;
            if (end < size && array[end] >= elem)
                k = binary_check(elem, array, begin, end);
            else if (array[end] >= elem)
                k = binary_check(elem, array, begin, size - 1);
            begin = end;
        }
        return k != -1 ? k : size;
    }
}


int main() {
    int *A, *B;
    size_t n, m;
    if (input_arr(A, B, n, m)) {
        size_t *answer = greater_or_equal(B, A, n);

        for (size_t i = 0; i < m; ++i)
            std::cout << greater_or_equal(B[i], A, n) << " ";
        delete_input_arr(A, B);
    }
    return 0;
}