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

class maxHeap {
public:
    explicit maxHeap(size_t bufferSize);

    ~maxHeap() { delete[] buff_; };

    maxHeap(const maxHeap &) = delete;

    maxHeap(maxHeap &) = delete;

    maxHeap &operator=(const maxHeap &) = delete;

    maxHeap &operator=(maxHeap &) = delete;

    //void Add(const int& element);
    void Add(int element);

    int ExtractMax();

    // const int& GetMax() const;
    void BuildmaxHeap();


private:
    void SiftDown(size_t index);

    void SiftUp(size_t index);

    void AllocateNewMem();

    int *buff_;
    size_t max_size_;
    size_t size_;

};

maxHeap::maxHeap(size_t bufferSize) {
    size_ = 0;
    max_size_ = bufferSize;
    buff_ = new int[bufferSize];
}

void maxHeap::AllocateNewMem() {
    max_size_ *= 2;
    int *temp_buff = new int[max_size_ * 2];
    memcpy(temp_buff, buff_, sizeof(int) * size_);
    delete[] buff_;
    buff_ = temp_buff;
}

void maxHeap::BuildmaxHeap() {
    for (size_t i = (size_ / 2) - 1; i >= 0; i--) {
        SiftDown(i);
    }
}

// проталкивание элемента вниз
void maxHeap::SiftDown(size_t index) {
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

void maxHeap::SiftUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (buff_[index] <= buff_[parent]) {
            return;
        }
        std::swap(buff_[index], buff_[parent]);
        index = parent;
    }
}

void maxHeap::Add(int element) {
    if (size_ >= max_size_) {
        AllocateNewMem();
        std::cout << "Alloc" << std::endl;
    }
    buff_[size_] = element;
    // std::cout << "Element = " << element << "  size = " << size_ << std::endl;
    size_++;
    SiftUp(size_ - 1);
}

int maxHeap::ExtractMax() {
    // if is not empty
    int result = buff_[0];
    buff_[0] = buff_[size_ - 1];
    size_--; // delete last element
    if (size_ > 0) {
        SiftDown(0);
    }
    return result;
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

    maxHeap heap(n);
    for (size_t i = 0; i < k; ++i) {
        heap.Add(A[i]);
    }
    std::cout << heap.ExtractMax() << " ";
    for(size_t end = k; end < n; ++end) {
        heap.Add(A[end]);
        std::cout << heap.ExtractMax() << " ";
        //heap.BuildmaxHeap();
    }

    return 0;
}