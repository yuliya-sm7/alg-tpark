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
#include <stdarg.h>


bool input_arr(int *&A, size_t &n) {
    if (n < 1)
        return false;
    A = new int[n];
    for (size_t i = 0; i < n; ++i)
        std::cin >> A[i];
    return true;
}

void delete_arr(int num, ...) {
    va_list ap;
    va_start(ap, num);
    while (num--) {
        delete[] va_arg(ap, int*);
    }
    va_end(ap);
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
int *greater_or_equal(const int A[], const int B[], size_t n, size_t m) {
    int *answer = (int *) calloc(m, sizeof(int));
    for (size_t i = 0; i < m; ++i) {
        ssize_t begin = -1;
        ssize_t end = 1;
        ssize_t k = -1;
        while (k < 0 && end < n) {
            end = (begin + 1) * 2;
            if (end < n && A[end] >= B[i])
                k = binary_check(B[i], A, begin, end);
            else
                k = binary_check(B[i], A, begin, n - 1);
            begin = end;
        }
        answer[i] = (k != -1) ? (int) k : (int) n;
    }
    return answer;
}


int main() {
    int *A, *B;
    size_t n, m;
    std::cin >> n >> m;
    input_arr(A, n);
    input_arr(B, m);
    int *answer = greater_or_equal(A, B, n, m);

    for (size_t i = 0; i < m; ++i)
        std::cout << answer[i] << " ";
    delete_arr(3, A, B, answer);
    return 0;
}