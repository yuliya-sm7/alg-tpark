/*5_1. Реклама.
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
 Каждому покупателю необходимо показать минимум 2 рекламы.
 Рекламу можно транслировать только в целочисленные моменты времени.
 Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама.
 Считается, что реклама показывается мгновенно.
 Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
 Требуется определить минимальное число показов рекламы.
*/
#include <iostream>
#include <string.h>


struct Customer {
public:
    int enter;
    int exit;
    int ads_count;

    Customer() : enter(0), exit(0), ads_count(0) {};

    bool operator>(const Customer &R) {
        if (this->exit > R.exit)
            return true;
        if (this->exit == R.exit)
            return this->enter < R.enter;
        return false;
    }
};

void show(Customer *arr, size_t n, int start, int adTime) {
    for (int i = start; i < n; i++)
        if (arr[i].enter <= adTime)
            arr[i].ads_count++;
}

template<class T>
void Merge(T a[], size_t a_len, T b[], size_t b_len, T c[]) {
    size_t i = 0;
    size_t j = 0;
    for (size_t k = 0; k < (a_len + b_len); k++) {
        if ((j >= b_len) || (i < a_len && b[j] > a[i])) {
            c[k] = a[i];
            i++;
        } else {
            c[k] = b[j];
            j++;
        }
    }
}

template<class T>
void MergeSort(T a[], size_t aLen) {
    if (aLen <= 1) {
        return;
    }
    size_t firstLen = aLen / 2;
    size_t secondLen = aLen - firstLen;
    MergeSort(a, firstLen);
    MergeSort(a + firstLen, secondLen);
    T *c = new T[aLen];
    Merge(a, firstLen, a + firstLen, secondLen, c);
    memcpy(a, c, sizeof(T) * aLen);
    delete[] c;
}


int main() {
    size_t n = 0;
    std::cin >> n;
    Customer A[n];
    for (int i = 0; i < n; i++) {
        std::cin >> A[i].enter >> A[i].exit;
    }
    MergeSort(A, n);

    int ads_count = 0;
    for (int i = 0; i < n; i++) {
        if (A[i].ads_count == 0) {
            show(A, n, i, A[i].exit - 1);
            ads_count++;
        }
        if (A[i].ads_count == 1) {
            show(A, n, i, A[i].exit);
            ads_count++;
        }
    }
    std::cout << ads_count;
    return 0;
}