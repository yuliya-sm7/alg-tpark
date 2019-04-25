// 4_2. Порядковые статистики.
// Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел,
// а также запрос на получение k-ой порядковой статистики.
// Команда добавления числа A задается положительным числом A,
// команда удаления числа A задается отрицательным числом “-A”.
// Запрос на получение k-ой порядковой статистики задается числом k.
// Требуемая скорость выполнения запроса - O(log n).

#include <iostream>

template<class T>
struct Node {
    T key;
    size_t height;
    size_t size;
    Node *left;
    Node *right;

    explicit Node(const T &key) :
            key(key),
            height(1),
            size(1),
            left(nullptr),
            right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

template<class T>
class ABLTree {
public:
    ABLTree() { root_ = nullptr; };

    ~ABLTree() { delete root_; };

    void Add(const T &key);

    void Remove(const T &key);

    int Kstat(int k);

private:
    Node<T> *root_;

    Node<T> *rotate_left(Node<T> *node);

    Node<T> *rotate_right(Node<T> *node);

    Node<T> *balance(Node<T> *node);

    size_t size(Node<T> *node) const;

    size_t height(Node<T> *node) const;

    int balance_factor(Node<T> *node) const;

    void fix(Node<T> *node);

    Node<T> *find_min(Node<T> *node);

    Node<T> *add_(Node<T> *node, const T &key);

    Node<T> *remove_(Node<T> *node, const T &key);

};

template<class T>
void ABLTree<T>::Add(const T &key) {
    root_ = add_(root_, key);
}

template<class T>
Node<T> *ABLTree<T>::add_(Node<T> *node, const T &key) {
    if (!node) {
        return new Node<T>(key);
    }
    if (key < node->key) {
        node->left = add_(node->left, key);
    } else {
        node->right = add_(node->right, key);
    }
    return balance(node);
}

template<class T>
void ABLTree<T>::Remove(const T &key) {
    root_ = remove_(root_, key);
}

template<class T>
Node<T> *ABLTree<T>::remove_(Node<T> *node, const T &key) {
    if (!node) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = remove_(node->left, key);
    } else if (key > node->key) {
        node->right = remove_(node->right, key);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Node<T> *temp = (node->left != nullptr) ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node<T> *min_node = find_min(node->right);
            node->key = min_node->key;
            node->right = remove_(node->right, min_node->key);
        }

    }
    if (node == nullptr) {
        return nullptr;
    }

    return balance(node);
}

template<class T>
Node<T> *ABLTree<T>::find_min(Node<T> *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<class T>
size_t ABLTree<T>::size(Node<T> *node) const {
    return node != nullptr ? node->size : 0;
}

template<class T>
size_t ABLTree<T>::height(Node<T> *node) const {
    return node != nullptr ? node->height : 0;
}

template<class T>
void ABLTree<T>::fix(Node<T> *node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
    node->size = size(node->left) + size(node->right) + 1;
}

template<class T>
Node<T> *ABLTree<T>::balance(Node<T> *node) {
    fix(node);
    int bf = balance_factor(node);
    if (bf == 2) {
        if (balance_factor(node->right) < 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }
    if (bf == -2) {
        if (balance_factor(node->left) > 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }
    return node;
}

template<class T>
int ABLTree<T>::balance_factor(Node<T> *node) const {
    return height(node->right) - height(node->left);
}

template<class T>
Node<T> *ABLTree<T>::rotate_left(Node<T> *node) {
    Node<T> *right = node->right;
    node->right = right->left;
    right->left = node;
    fix(node);
    fix(right);
    return right;
}

template<class T>
Node<T> *ABLTree<T>::rotate_right(Node<T> *node) {
    Node<T> *left = node->left;
    node->left = left->right;
    left->right = node;
    fix(node);
    fix(left);
    return left;
}

template<class T>
int ABLTree<T>::Kstat(int k) {
    int result = 0;
    if (k < size(root_)) {
        Node<T> *node = root_;
        int index = size(root_->left);

        while (k != index) {
            if (k > index) {
                node = node->right;
                index += size(node->left) + 1;
            } else {
                node = node->left;
                index -= size(node->right) + 1;
            }
        }
        result = node->key;
    } else {
        return 0;
    }
    return result;
}


int main() {
    size_t N;
    std::cin >> N;
    ABLTree<int> tree;

    for (size_t i = 0; i < N; i++) {
        int A, k;
        std::cin >> A >> k;
        if (A >= 0) {
            tree.Add(A);
        } else {
            tree.Remove(-A);
        }
        std::cout << tree.Kstat(k) << std::endl;
    }
    return 0;
}