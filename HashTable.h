#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>

const int TABLE_SIZE = 100003; // A larger prime number for better distribution

struct HashEntry {
    std::string key;
    int value;
    bool isActive;
    HashEntry* prev;
    HashEntry* next;

    HashEntry();
};

class HashTable {
private:
    std::vector<HashEntry> table;
    HashEntry* first;
    HashEntry* last;

    int hashFunction(const std::string &key);

public:
    HashTable();
    void insert(const std::string &key, int value);
    void remove(const std::string &key);
    int get(const std::string &key);
    std::pair<std::string, int> get_last();
    std::pair<std::string, int> get_first();
    int get_total_elements();
};

#endif // HASHTABLE_H