/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми.
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции
 * добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

 1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */
#include <iostream>
#include <string>
#include <vector>

const double LEVEL = 0.75;
const int PARAMETER = 23;
const int MUL_REHASH = 2;

using std::string;

class HashTable {
public:
    explicit HashTable(size_t size);

    ~HashTable() = default;

    bool There(const string &key) const;

    bool Add(const string &key);

    bool Remove(const string &key);

private:
    int alpha_;
    size_t nodeCount_;
    double rehashLevel_;

    struct Node {
        Node() : key(""), deleted(false) {}

        string key;
        bool deleted;

        bool isEmpty() const {
            return key.empty();
        }
    };

    std::vector<Node> table;

    size_t Hash(const string &key, size_t probe) const;

    void Rehash();

    ssize_t find(const string &key) const;
};


HashTable::HashTable(size_t size) :
        table(size), alpha_(PARAMETER), nodeCount_(0), rehashLevel_(LEVEL) {}

size_t HashTable::Hash(const string &key, size_t probe) const {
    size_t hash = 0;
    size_t m = table.size();
    for (auto letter:key) {
        hash = (hash * alpha_ + letter) % m;
    }
    double c1 = 1.0/2, c2 = 1.0/2;
    return size_t (hash + c1 * probe + c2 * probe * probe) % m;
}

void HashTable::Rehash() {
    size_t new_size = MUL_REHASH * table.size();
    std::vector<Node> temp_table(std::move(table)); // переносим таблицу во временный вектор
    table.resize(new_size);

    nodeCount_ = 0;
    for (auto &nod:temp_table) {
        if (!nod.isEmpty() && !nod.deleted) {
            Add(nod.key);
        }
    }
}

bool HashTable::There(const string &key) const {
    return find(key) != -1;
}

bool HashTable::Add(const string &key) {
    if (nodeCount_ >= table.size() * rehashLevel_)
        Rehash();
    ssize_t insert_place = -1;
    size_t hash;
    for (size_t probe = 0; probe < table.size(); ++probe) {
        hash = Hash(key, probe);

        if (table[hash].isEmpty()) {
            if (insert_place == -1)
                insert_place = hash;
            break;
        }
        if (table[hash].deleted) {
            if (insert_place == -1)
                insert_place = hash;
        } else if (table[hash].key == key)
            return false;
    }
    if (insert_place == -1)
        return false;
    table[insert_place].key = key;
    table[insert_place].deleted = false;
    nodeCount_++;
    return true;
}

bool HashTable::Remove(const string &key) {
    ssize_t hash = find(key);
    if (hash == -1)
        return false;
    table[hash].deleted = true;
    --nodeCount_;
    return true;
}

ssize_t HashTable::find(const string &key) const {
    ssize_t hash;
    for (size_t probe = 0; probe < table.size(); ++probe) {
        hash = Hash(key, probe);
        if (table[hash].isEmpty())
            return -1;
        if (table[hash].key == key && !table[hash].deleted)
            return hash;
    }
    return -1;
}


void handling(char command, HashTable &table) {
    bool success;
    string key;
    std::cin >> key;
    switch (command) {
        case '?':
            success = table.There(key);
            break;
        case '+':
            success = table.Add(key);
            break;
        case '-':
            success = table.Remove(key);
            break;
        default:
            success = false;
    }
    std::cout << (success ? "OK" : "FAIL") << std::endl;
}

int main() {
    HashTable table(8);
    char command = 0;
    while (std::cin >> command) {
        handling(command, table);
    }
    return 0;
}