/*
 * 7_1. MSD для строк.
Дан массив строк. Количество строк не больше 105.
 Отсортировать массив методом поразрядной сортировки MSD по символам.
 Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
*/
#include <iostream>
#include <string>

const int alphabet_size = 256;
const size_t LEN_BUFF = 2;
const int MUL_REBUFF = 2;

using std::string;

void CountSort(string *array, size_t size, size_t *temp, size_t radix) {
    for (int i = 0; i < alphabet_size + 1; i++)
        temp[i] = 0;  // зануляем массив счетчиков
    for (int i = 0; i < size; i++)
        temp[(int) array[i][radix]]++;  // считаем колличество каждого символа
    for (int i = 1; i < alphabet_size + 1; i++)
        temp[i] += temp[i - 1];  // преобразуем в индексы начала групп

    auto *result = new string[size];
    for (ssize_t i = size - 1; i >= 0; i--) {
        result[temp[(int) array[i][radix]] - 1] = array[i];
        temp[(int) array[i][radix]]--;
    }
    for (size_t j = 0; j < size; j++) {
        array[j] = result[j];
    }
    delete[] result;
}

void MSD(string *array, size_t size, size_t radix = 0) {
    size_t group[alphabet_size + 1];
    group[alphabet_size] = size;
    CountSort(array, size, group, radix);  // сортировка по первой букве

    for (int i = 0; i < alphabet_size; i++) {
        size_t group_size = group[i + 1] - group[i]; // кол-во строк с одиноковым началом
        // отбрасываем из группы "короткие" строки
        while (group_size > 1 && array[group[i]][radix] == '\0') {
            group[i]++;
            group_size--;
        }
        if (group_size > 1) {  // рекурсивно вызываем MSD сортировку для строк с одинаковым началом
            MSD(array + group[i], group_size, radix + 1);
        }
    }
}

string *input_strings(size_t &n_lines) {
    n_lines = 0;
    size_t n_buff = LEN_BUFF;
    auto *arr = new string[n_buff];

    while (std::cin >> arr[n_lines]) {
        ++n_lines;
        if (n_lines == n_buff) {  // то перевыделение памяти
            auto *tmp = new string[n_buff *= MUL_REBUFF];
            for (size_t i = 0; i < n_lines; i++)
                tmp[i] = arr[i];
            delete[] arr;
            arr = tmp;
        }
    }
    return arr;
}

int main(int argc, char const *argv[]) {
    size_t n_lines = 0;
    string *input_str = input_strings(n_lines);

    MSD(input_str, n_lines);
    for (size_t i = 0; i < n_lines; i++)
        std::cout << input_str[i] << std::endl;

    delete[] input_str;
    return 0;
}