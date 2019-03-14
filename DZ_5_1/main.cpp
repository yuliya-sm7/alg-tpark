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

void Merge(int *a, int a_len, int *b, int b_len, int *c) {
    int i = 0;
    int j = 0;
    for (int k = 0; k < (a_len + b_len); k++) {
        if (i < a_len && j < b_len) {
            if (a[i] < b[j]) {
                c[k] = a[i];
                i++;
            } else {
                c[k] = b[j];
                j++;
            }
        } else if (i >= a_len) {
            c[k] = b[j];
            j++;
        } else {
            c[k] = a[i];
            i++;
        }
    }
}

void MergeSort(int *a, int aLen) {
    if (aLen <= 1) {
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort(a, firstLen);
    MergeSort(a + firstLen, secondLen);
    int *c = new int[aLen];
    Merge(a, firstLen, a + firstLen, secondLen, c);
    memcpy(a, c, sizeof(int) * aLen);
    delete[] c;
}


int main() {
    int n = 0;
    std::cin >> n;
    int *A = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    MergeSort(A, n);
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    delete[] A;
    return 0;
}