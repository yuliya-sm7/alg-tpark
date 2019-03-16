
/*
 * 3_3. Реализовать очередь с помощью двух стеков.
 * Использовать стек, реализованный с помощью динамического буфера.
 */

#include <iostream>
#include <string.h>

template <class T>
class Stack {

private:
    size_t max_size;
    T *buff;
    ssize_t top;

public:
    explicit Stack(size_t length = 1) {
        top = -1;
        max_size = length;
        buff = new T[max_size];
    }

    Stack(const Stack &s){  // конструктор копирования
        max_size = s.max_size;
        top = s.top;
        memcpy(buff, s.buff, sizeof(T) * s.size());
    };

    Stack operator = (const Stack &s) = delete;

    ~Stack() {
        delete[] buff;
    }

    void push(T elem) {
        if (size() == max_size) {
            expand();
        }
        ++top;
        buff[top] = elem;
    }

    T pop() {
        if (is_empty()) {
            return -1;
        }
        return buff[top--];
    }

    void expand() {
        max_size *= 2;
        T *temp_buff = new T[max_size];
        memcpy(temp_buff, buff, sizeof(T) * size());
        delete[] buff;
        buff = temp_buff;
    }

    bool is_empty() {
        return (top < 0);
    }

    size_t size() {
        return size_t (top + 1);
    }
};

template <class T>
class Queue {

private:
    Stack<T> tail;
    Stack<T> head;
public:
    void insert(T data) {
        tail.push(data);
    }

    T remove() {
        if (head.is_empty()) {
            size_t n = tail.size();
            for (size_t i = 0; i < n; i++) {
                head.push(tail.pop());
            }
        }
        return head.pop();
    }

    bool is_empty() {
        return head.is_empty() && tail.is_empty();
    }
};

bool is_correct(size_t n) {
    Queue<int> queue;
    int command = 0;
    int value = -1;
    int real_value = -1;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> command >> value;
        switch (command) {
            case 3:
                queue.insert(value);
                break;
            case 2:
                if (!queue.is_empty()) {
                    real_value = queue.remove();
                } else {
                    real_value = -1;
                }
                if (real_value != value) {
                    return false;
                }
                break;
            default:
                return false;
        }
    }
    return true;
}

int main() {
    size_t num_command = 0;
    std::cin >> num_command;

    if (is_correct(num_command))
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}