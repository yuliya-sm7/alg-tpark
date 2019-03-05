#include <iostream>


bool input_arr(int*& A, int*& B, size_t &n, size_t &m) {
    std::cin >> n >> m;
    if (n <= 0 || m <= 0)
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


// Поиск в массиве array в диапазоне (a,b] элемента, большего или равного element
ssize_t binary_check(int element, const int *array, size_t a, size_t b) {
    ssize_t length = b - a;
    while (length > 1) {
        if (element > array[a + length / 2]) {
            a += length / 2;
        } else {
            b -= length / 2;
        }
        length = b - a;
    }
    // Если элемент не найден, возвращаем -1
    return array[b] >= element ? b : -1;
}


// Поиск первого элемента массива array, который больше или равен element
size_t greater_or_equal(int elem, int *array, size_t size) {
    ssize_t begin = -1;
    ssize_t end;

    ssize_t k;

    do {
        end = (begin + 1) * 2;
        if (end < size) {
            k = binary_check(elem, array, begin, end);
            begin = end;
        } else {
            k = binary_check(elem, array, begin, size - 1);
            break;
        }
    } while (k == -1);

    return k != -1 ? k : size;
}


int main() {
    int *A, *B;
    size_t n, m;
    input_arr(A, B, n, m);

    for (size_t i = 0; i < m; ++i)
        std::cout << greater_or_equal(B[i], A, n) << " ";

    delete_input_arr(A, B);
    return 0;
}