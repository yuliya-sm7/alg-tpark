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

const float level = 0.75;
const int alpha = 23;

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
    float rehashLevel_;

    struct Node {
        Node() : key(""), deleted(false) {}

        string key;
        bool deleted;

        bool isEmpty() const {
            return key.empty();
        }
    };

    std::vector<Node> table;

    size_t Hash(const string &key) const;

    void Rehash();
};


HashTable::HashTable(size_t size) :
        table(size), alpha_(alpha), nodeCount_(0), rehashLevel_(level) {}

size_t HashTable::Hash(const string &key) const {
    size_t hash = 0;
    for (auto letter:key) {
        hash = (hash * alpha_ + letter) % table.size();
    }
    return hash;
}

void HashTable::Rehash() {
    size_t new_size = 2 * table.size();
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
    size_t hash = Hash(key);
    for (int i = 0; i < table.size(); ++i) {
        hash = (hash + i) % table.size();
        if (table[hash].key == key && !table[hash].deleted) {
            return true;
        }
        if ((table[hash].isEmpty() && !table[hash].deleted) || (i >= table.size())) {
            return false;
        }
    }
    return false;
}

bool HashTable::Add(const string &key) {
    if (nodeCount_ >= table.size() * rehashLevel_) {
        Rehash();
    }
    size_t next_hash = Hash(key);
    size_t hash = next_hash;
    int i = 0;
    do {
        next_hash = (next_hash + i) % table.size();
        if (!table[hash].isEmpty() || !table[hash].deleted) {
            hash = next_hash;
        }
        if (table[next_hash].key == key) {
            return false;
        }
        i++;
    } while (!table[next_hash].isEmpty() || table[next_hash].deleted);
    table[hash].key = key;
    table[hash].deleted = false;
    nodeCount_++;
    return true;
}


bool HashTable::Remove(const string &key) {
    size_t hash = Hash(key);
    int i = 0;
    while (true) {
        hash = (hash + i) % table.size();
        if (table[hash].key == key && !table[hash].deleted) {
            table[hash].key = "";
            table[hash].deleted = true;
            return true;
        }
        if ((table[hash].isEmpty() && !table[hash].deleted) || (i >= table.size())) {
            return false;
        }
        i++;
    }
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