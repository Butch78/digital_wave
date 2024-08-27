#include "HashTable.h"
#include <iostream>
#include <algorithm>
#include <functional>

HashEntry::HashEntry() : key(""), value(0), isActive(false), prev(nullptr), next(nullptr) {}

HashTable::HashTable() : table(TABLE_SIZE), first(nullptr), last(nullptr) {}

int HashTable::hashFunction(const std::string &key) {
    std::hash<std::string> hashFn;
    return hashFn(key) % TABLE_SIZE;
}

void HashTable::insert(const std::string &key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index].isActive && table[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            std::cerr << "Hash table is full!" << std::endl;
            return;
        }
    }

    if (!table[index].isActive) {
        table[index].key = key;
        table[index].isActive = true;
        table[index].value = value;

        if (last) {
            last->next = &table[index];
            table[index].prev = last;
        }
        last = &table[index];

        if (!first) {
            first = &table[index];
        }
    } else {
        table[index].value = value;
    }
}

void HashTable::remove(const std::string &key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index].isActive && table[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            std::cerr << "Key not found!" << std::endl;
            return;
        }
    }

    if (table[index].isActive) {
        table[index].isActive = false;

        if (table[index].prev) {
            table[index].prev->next = table[index].next;
        } else {
            first = table[index].next;
        }

        if (table[index].next) {
            table[index].next->prev = table[index].prev;
        } else {
            last = table[index].prev;
        }
    }
}

int HashTable::get(const std::string &key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index].isActive && table[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            std::cerr << "Key not found!" << std::endl;
            return -1;
        }
    }

    if (table[index].isActive) {
        return table[index].value;
    } else {
        std::cerr << "Key not found!" << std::endl;
        return -1;
    }
}

std::pair<std::string, int> HashTable::get_last() {
    if (last && last->isActive) {
        return {last->key, last->value};
    } else {
        return {"", -1};
    }
}

std::pair<std::string, int> HashTable::get_first() {
    if (first && first->isActive) {
        return {first->key, first->value};
    } else {
        return {"", -1};
    }
}

int HashTable::get_total_elements() {
    int count = 0;
    for (const auto& entry : table) {
        if (entry.isActive) {
            count++;
        }
    }
    return count;
}