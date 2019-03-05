#include <iostream>
#include <string.h>

class Stack {

private:
    size_t max_size;
    int *buff;
    ssize_t top;

public:
    explicit Stack(size_t length = 1) {
        top = -1;
        max_size = length;
        buff = new int[max_size];
    }

    ~Stack() {
        delete[] buff;
    }

    void push(int elem) {
        ++top;
        if (top > max_size)
            expand();
        buff[top] = elem;
    }

    int pop() {
        if (is_empty())
            return -1;
        return buff[top--];
    }

    void expand() {
        max_size *= 2;
        int *temp_buff = new int[max_size];
        memcpy(temp_buff, buff, size());
        delete[] buff;
        buff = temp_buff;
    }

    bool is_empty() {
        return (top < 0);
    }

    size_t size() {
        return size_t(top + 1);
    }
};


class Queue {
private:
    Stack initial;
    Stack final;
public:
    void insert(int data) {
        initial.push(data);
    }

    int remove() {
        if (final.is_empty()) {
            while (!initial.is_empty())
                final.push(initial.pop());
        }
        return final.pop();
    }

    bool is_empty() {
        return initial.is_empty();
    }
};

bool is_correct(size_t n) {
    Queue queue;
    int command = 0;
    int value = -1;
    int real_value = -1;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> command >> value;

        if (command == 3) {

            queue.insert(value);

        } else if (command == 2) {

            if (queue.is_empty()) {
                    real_value = -1;
            } else  real_value = queue.remove();
            if (real_value != value)
                return false;

        } else return false;
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