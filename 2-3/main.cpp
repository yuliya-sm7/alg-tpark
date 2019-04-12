/* Задача 2. Порядок обхода (4 балла)
Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
2_3. Выведите элементы в порядке post-order (снизу вверх).
 */

#include <iostream>
#include <vector>
#include <stack>

class BinTree {
public:
    BinTree() = default;

    ~BinTree() { delete node_; };

    void Add(int K);

    std::vector<int> Post_order();

private:
    struct Node {
        int key;
        Node *left;
        Node *right;

        explicit Node(const int &key) : key(key), left(nullptr), right(nullptr) {}

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node *node_ = nullptr;
};

void BinTree::Add(int K) {
    Node *new_node = new Node(K);
    Node **ptr_insert = &node_;

    while ((*ptr_insert) != nullptr) {
        if ((*ptr_insert)->key >= K) {
            ptr_insert = &(*ptr_insert)->left;
        } else {
            ptr_insert = &(*ptr_insert)->right;
        }
    }
    *ptr_insert = new_node;
}

std::vector<int> BinTree::Post_order() {
    std::vector<int> result;
    std::stack<Node *> st;
    Node *prev_node = nullptr;
    st.push(node_);
    while (!st.empty() && node_ != nullptr) {
        Node *curr_node = st.top();

        if (!prev_node || prev_node->left == curr_node || prev_node->right == curr_node ||
            curr_node->left == prev_node) {
            if (curr_node->left && curr_node->left != prev_node) {
                st.push(curr_node->left);
            } else if (curr_node->right) {
                st.push(curr_node->right);
            } else {
                result.push_back(curr_node->key);
                st.pop();
            }
        } else if (curr_node->right == prev_node) {
            result.push_back(curr_node->key);
            st.pop();
        }

        prev_node = curr_node;
    }
    return result;
}

int main() {
    size_t N = 0;
    std::cin >> N;
    BinTree tree;
    int element;
    for (size_t i = 0; i < N; i++) {
        std::cin >> element;
        tree.Add(element);
    }
    auto result = tree.Post_order();
    for (const int &key : result) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    return 0;
}