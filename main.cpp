#include <iostream>
#include <fstream>
#include <algorithm>
#include "HashTable.h"

// Declare the function to fetch trades from binance_trades.cpp
void fetchAggTrades();

void createDataSet(const std::string &filename, HashTable &hashTable) {
    std::ifstream file(filename);
    std::string word;
    int value = 1;

    while (file >> word) {
        // Remove punctuation and convert to lowercase
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!word.empty()) {
            hashTable.insert(word, value++);
        }
    }
}

int main() {

    // Task 1: Data Structures and Algorithms (Hash Table)
    HashTable hashTable;
    createDataSet("book.txt", hashTable);

    // Example usage
    hashTable.insert("example", 1);
    std::cout << "Value for 'example': " << hashTable.get("example") << std::endl;

    auto last = hashTable.get_last();
    std::cout << "Last inserted: " << last.first << " with value " << last.second << std::endl;

    auto first = hashTable.get_first();
    std::cout << "First inserted: " << first.first << " with value " << first.second << std::endl;

    auto count = hashTable.get_total_elements();
    std::cout << "Total elements: " << count << std::endl;

    hashTable.remove("example");
    std::cout << "Value for 'example' after removal: " << hashTable.get("example") << std::endl;   

    // Task 2: Trading Specific Algorithms
    fetchAggTrades();

    return 0;
}