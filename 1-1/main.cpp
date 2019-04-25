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

template<class T>
class HashTable {
public:
    explicit HashTable(size_t size);

    ~HashTable() = default;

    bool There(const T &key) const;

    bool Add(const T &key);

    bool Remove(const T &key);

private:
    int alpha_;
    size_t nodeCount_;
    double rehashLevel_;

    std::vector<T> table;
    std::vector<char> status;  // f - free, d - deleted, b - busy

    size_t Hash(const T &key, size_t probe, ssize_t old_hash) const;

    void Rehash();

    ssize_t find(const T &key) const;
};

template<class T>
HashTable<T>::HashTable(size_t size) :
        table(size), status(size, 'f'), alpha_(PARAMETER), nodeCount_(0), rehashLevel_(LEVEL) {}

template<class T>
size_t HashTable<T>::Hash(const T &key, size_t probe, ssize_t old_hash) const {
    size_t m = table.size();
    if (old_hash < 0) {
        old_hash = 0;
        for (auto letter:key) {
            old_hash = (old_hash * alpha_ + letter) % m;
        }
    }
    double c1 = 1.0 / 2, c2 = 1.0 / 2;
    return size_t(old_hash + c1 * probe + c2 * probe * probe) % m;
}

template<class T>
void HashTable<T>::Rehash() {
    size_t new_size = MUL_REHASH * table.size();
    std::vector<T> temp_table(std::move(table)); // переносим таблицу во временный вектор
    std::vector<char> temp_status(std::move(status));
    table.resize(new_size);
    status.resize(new_size, 'f');

    nodeCount_ = 0;
    for (int i = 0; i < temp_table.size(); ++i) {
        if (temp_status[i] == 'b') {
            Add(temp_table[i]);
        }
    }
}

template<class T>
bool HashTable<T>::There(const T &key) const {
    return find(key) != -1;
}

template<class T>
bool HashTable<T>::Add(const T &key) {
    if (nodeCount_ >= table.size() * rehashLevel_)
        Rehash();
    ssize_t insert_place = -1;
    ssize_t hash = -1;
    for (size_t probe = 0; probe < table.size(); ++probe) {
        hash = Hash(key, probe, hash);

        if (status[hash] == 'f') {
            if (insert_place == -1)
                insert_place = hash;
            break;
        }
        if (status[hash] == 'd') {
            if (insert_place == -1)
                insert_place = hash;
        } else if (table[hash] == key)
            return false;
    }
    table[insert_place] = key;
    status[insert_place] = 'b';
    nodeCount_++;
    return true;
}

template<class T>
bool HashTable<T>::Remove(const T &key) {
    ssize_t hash = find(key);
    if (hash == -1)
        return false;
    status[hash] = 'd';
    --nodeCount_;
    return true;
}

template<class T>
ssize_t HashTable<T>::find(const T &key) const {
    ssize_t hash = -1;
    for (size_t probe = 0; probe < table.size(); ++probe) {
        hash = Hash(key, probe, hash);
        if (status[hash] == 'f')
            return -1;
        if (table[hash] == key && status[hash] != 'd')
            return hash;
    }
    return -1;
}

template<class T>
void handling(char command, HashTable<T> &table) {
    bool success;
    T key;
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
    HashTable<string> table(2);
    char command = 0;
    while (std::cin >> command) {
        handling(command, table);
    }
    return 0;
}