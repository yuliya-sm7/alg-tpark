/*
 * 4_4. Скользящий максимум.
Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некоторого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне.
Скорость работы O(n log n), память O(n).
Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n строк со значением каждого элемента. Затем вводится k  - размер окна.
Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения окна.
 */

#include <iostream>
#include <cassert>
#include <string.h>

class Elem {
public:
    int value;
    size_t index;

    bool operator>(const Elem &x) {
        return this->value > x.value;
    };

    bool operator<=(const Elem &x) {
        return this->value <= x.value;
    };
};

template<class T>
class maxHeap {
public:
    explicit maxHeap(size_t bufferSize);

    ~maxHeap() { delete[] buff_; };

    maxHeap(const maxHeap &) = delete;

    maxHeap(maxHeap &) = delete;

    maxHeap &operator=(const maxHeap &) = delete;

    maxHeap &operator=(maxHeap &) = delete;

    void Add(T element);

    T ExtractMax();

    const T &GetMax() const;

private:
    void SiftDown(size_t index);

    void SiftUp(size_t index);

    void AllocateNewMem();

    T *buff_;
    size_t max_size_;
    size_t size_;

};

template<class T>
maxHeap<T>::maxHeap(size_t bufferSize) {
    size_ = 0;
    max_size_ = bufferSize;
    buff_ = new T[bufferSize];
}

template<class T>
void maxHeap<T>::AllocateNewMem() {
    max_size_ *= 2;
    T *temp_buff = new T[max_size_ * 2];
    memcpy(temp_buff, buff_, sizeof(T) * size_);
    delete[] buff_;
    buff_ = temp_buff;
}


template<class T>
// проталкивание элемента вниз
void maxHeap<T>::SiftDown(size_t index) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t largest = index;

    if (left < size_ && buff_[left] > buff_[index]) {
        largest = left;
    }
    if (right < size_ && buff_[right] > buff_[largest]) {
        largest = right;
    }
    if (largest != index) {
        std::swap(buff_[index], buff_[largest]);
        SiftDown(largest);
    }
}

template<class T>
void maxHeap<T>::SiftUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (buff_[index] <= buff_[parent]) {
            return;
        }
        std::swap(buff_[index], buff_[parent]);
        index = parent;
    }
}

template<class T>
void maxHeap<T>::Add(T element) {
    if (size_ >= max_size_) {
        AllocateNewMem();
    }
    buff_[size_] = element;
    size_++;
    SiftUp(size_ - 1);
}

template<class T>
T maxHeap<T>::ExtractMax() {
    // if is not empty
    T result = buff_[0];
    buff_[0] = buff_[size_ - 1];
    size_--; // delete last element
    if (size_ > 0) {
        SiftDown(0);
    }
    return result;
}

template<class T>
const T &maxHeap<T>::GetMax() const {
    return buff_[0];
}


int main() {
    size_t n = 0;
    std::cin >> n;
    int *A = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    size_t k = 0;
    std::cin >> k;

    maxHeap<Elem> *heap = new maxHeap<Elem>(k + 1);
    Elem temp;
    for (size_t i = 0; i < k; ++i) {
        temp.index = i;
        temp.value = A[i];
        heap->Add(temp);
    }
    std::cout << heap->GetMax().value << " ";

    for (size_t end = k; end < n; ++end) {
        temp.index = end;
        temp.value = A[end];
        heap->Add(temp);
        Elem maxElem = heap->GetMax();

        while (maxElem.index < (end - k + 1)) {
            maxElem = heap->ExtractMax();
        }
        std::cout << maxElem.value << " ";
    }
    delete[] A;
    delete heap;
    return 0;
}