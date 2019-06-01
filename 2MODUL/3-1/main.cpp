//Задача 3. Декартово дерево (4 балла)
//Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
//Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
//Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
//Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
//При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
// Затем разбейте найденное поддерево по ключу x так,
// чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x.
// Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
//
//Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
//
//3_1. Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.


#include <iostream>
#include <vector>
#include <stack>


template<class T>
struct Node {
    T key;
    T priority;
    Node *left;
    Node *right;

    explicit Node(const T &key, const T &priority = 0) : key(key), priority(priority), left(nullptr), right(nullptr) {}

    ~Node() = default;
};

template<class T>
size_t  depth(Node<T> *root) {
    ssize_t depth = 0;
    ssize_t max_depth = 0;
    std::stack<Node<T> *> st;
    Node<T> *prev_node = nullptr;
    st.push(root);
    while (!st.empty() && root != nullptr) {
        Node<T> *curr_node = st.top();
        depth++;
        if (!prev_node || prev_node->left == curr_node || prev_node->right == curr_node ||
            curr_node->left == prev_node) {
            if (curr_node->left && curr_node->left != prev_node) {
                st.push(curr_node->left);
            } else if (curr_node->right) {
                st.push(curr_node->right);
            } else {
                st.pop();
                max_depth = std::max(max_depth, depth);
                depth -= 2;
            }
        } else {
            st.pop();
            max_depth = std::max(max_depth, depth);
            depth -= 2;
        }
        prev_node = curr_node;
    }
    return (size_t)max_depth;
}

template<class T>
void Delete(Node<T> *node_) {
    std::stack<Node<T> *> st;
    st.push(node_);
    while (!st.empty() && node_ != nullptr) {
        Node<T> *curr_node = st.top();
        if (curr_node->left) {
            st.push(curr_node->left);
        } else if (curr_node->right) {
            st.push(curr_node->right);
        } else {
            st.pop();
            if (!st.empty()) {
                Node<T> *prev_node = st.top();
                if (prev_node->right == curr_node) {
                    prev_node->right = nullptr;
                } else {
                    prev_node->left = nullptr;
                }
            }
            delete curr_node;
        }
    }
}

//////////////////////////////////////////////////////////////////////

template<class T>
class BinTree {
public:
    BinTree() = default;

    ~BinTree() { Delete(node_); };

    void Add(T K);

    size_t getDepth();

private:
    Node<T> *node_ = nullptr;
};

template<class T>
void BinTree<T>::Add(T K) {
    Node<T> *new_node = new Node<T>(K);
    Node<T> **ptr_insert = &node_;

    while ((*ptr_insert) != nullptr) {
        if ((*ptr_insert)->key >= K) {
            ptr_insert = &(*ptr_insert)->left;
        } else {
            ptr_insert = &(*ptr_insert)->right;
        }
    }
    *ptr_insert = new_node;
}

template<class T>
size_t BinTree<T>::getDepth() {
    return depth(node_);
}

//////////////////////////////////////////////////////////////////////

template<class T>
class Treap {
public:
    Treap() : root_(nullptr) {};

    ~Treap() { Delete(root_); };

    void Add(T key, T priority);

    size_t getDepth();

private:
    Node<T> *root_;

    void split(Node<T> *node, int key, Node<T> *&left, Node<T> *&right);
};

template<class T>
void Treap<T>::split(Node<T> *node, int key, Node<T> *&left, Node<T> *&right) {
    if (node == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (key > node->key) {
        split(node->right, key, node->right, right);
        left = node;
    } else {
        split(node->left, key, left, node->left);
        right = node;
    }
}

template<class T>
void Treap<T>::Add(T key, T priority) {

    auto *new_node = new Node<T>(key, priority);
    if (root_ == nullptr) {
        root_ = new_node;
        return;
    }
    Node<T> *node = root_;
    Node<T> *prev = root_;
    while (node != nullptr && priority < node->priority) {
        prev = node;
        if (key > node->key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    split(node, key, new_node->left, new_node->right);

    if (node == root_) {
        root_ = new_node;
    } else {
        if (key > prev->key) {
            prev->right = new_node;
        } else {
            prev->left = new_node;
        }
    }
}

template<class T>
size_t Treap<T>::getDepth() {
    return depth(root_);
}


int main() {
    Treap<int> treap;
    BinTree<int> tree;

    size_t n;
    std::cin >> n;
    int key;
    int priority;
    for (int i = 0; i < n; i++) {
        std::cin >> key >> priority;
        treap.Add(key, priority);
        tree.Add(key);
    }

    int difference = tree.getDepth() - treap.getDepth();
    std::cout << difference << std::endl;
    return 0;
}