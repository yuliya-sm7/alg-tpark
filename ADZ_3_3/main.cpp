#include <iostream>
#include <string.h>

class Stack {

private:
    size_t max_size;
    int* buff;
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
        if (top == max_size){
            expand();
        }
        buff[top] = elem;

    }
    int pop() {
        if (is_empty()) {
            return -1;
        }
        return buff[top--];
    }

    void expand() {
        size_t new_max_size = max_size*2;
        int* temp_buff = new int[new_max_size];
        memcpy(temp_buff, buff, sizeof(int)*max_size);
        //for (int i = 0; i < max_size; i++) temp_buff[i] = buff[i];
        delete[] buff;
        max_size = new_max_size;
        buff = temp_buff;
    }

    bool is_empty() {
        return (top < 0);
    }

    ssize_t size() {
        return top;
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
        ssize_t n = initial.size();
        for (ssize_t i = 0; i <= n; i++) {
            final.push(initial.pop());
        }
        int elem = final.pop();
        for (int i = 0; i <n; i++) {
            initial.push(final.pop());
        }
        return elem;
    }
    bool is_empty() {
        return initial.is_empty();
    }
};

bool is_correct(size_t n) {
    Queue queue;
    int command = 0;
    int value = -1;
    int realValue = -1;

    for (int i = 0; i < n; ++i) {
        std::cin >> command >> value;
        switch (command) {
            case 3:
                queue.insert(value);
                break;
            case 2:
                if (!queue.is_empty()) {
                    realValue = queue.remove();
                } else {
                    realValue = -1;
                }
                if (realValue != value) {
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