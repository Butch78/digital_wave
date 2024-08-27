# Development Environment Setup

1. Created a Dev Container to the C++ debian environment, the relevent files are in the .devcontainer folder
2. Installed g++ in the Debian container
3. Installed the C++ extension in VS Code and the C++ Intellisense extension
4. Created a task.json file to compile the code, the task.json file is in the .vscode folder and the command to compile the code is `g++ -g -o main main.cpp`. I can call the task by pressing `Ctrl+Shift+B` in VS Code and it will compile the code. I can then run the code by typing `./main` in the terminal.
5. I created the main.cpp file and the HashTable.cpp file. The main.cpp file contains the main function and the HashTable.cpp file contains the implementation of the HashTable class.

# Task 1: Data Structures and Algorithms

## Description

Create a data-set of words from the book https://www.gutenberg.org/files/98/98-0.txt. Implement a 
fixed sized hash table by using linear probing to resolve collisions. Assume that the keys are the 
words from the given data-set and the hash table’s values are integers. You need to implement the 
following functions with O(1)-complexity:
 ◦ insert(key, value): inserts a new key-value pair or replaces a key’s existing 
value,
 ◦ remove(key): removes the corresponding key-value pair,
 ◦ get(key): returns the value of the corresponding key,
 ◦ get_last(): returns the most recently inserted or changed key-value pair,
 ◦ get_first(): returns the least recently inserted or changed key-value pair

## Solution

1. I downloaded the book from https://www.gutenberg.org/files/98/98-0.txt. and saved it as `book.txt`

2. I created a main.cpp, HashTable.cpp, and HashTable.h file. The main.cpp file contains the main function and the HashTable.cpp file contains the implementation of the HashTable class. The HashTable.h file contains the HashTable class definition. I created a HashEntry Struct that would contain the revelant key and value. I then created a HashTable class that would contain the HashEntry struct and the methods that were required. The HashTable class has the following methods:
        - `insert(key, value)`: inserts a new key-value pair or replaces a key's existing value
        - `remove(key)`: removes the corresponding key-value pair
        - `get(key)`: returns the value of the corresponding key
        - `get_last()`: returns the most recently inserted or changed key-value pair
        - `get_first()`: returns the least recently inserted or changed key-value pair
        - `get_total_elements()`: returns the total number of elements in the hash table, this is used to check the number of elements in the hash table

3. To ensure O(1)-complexity for the insert, remove, get, get_last, and get_first methods, I used a hash table with linear probing to resolve collisions. I created a hash function that would hash the key and return the index of the key in the hash table. I then used the hash function to insert the key and value into the hash table. If there was a collision, I would use linear probing to find the next available index in the hash table. I used the same hash function to get the key and value from the hash table. I used the same hash function to remove the key and value from the hash table. I used the same hash function to get the last and first inserted key and value from the hash table. I also created a method to get the total number of elements in the hash table. 

3. Initially, I created a Table size with the value of 10007 and it caused there to be a "Hash table is full!" error. I then changed the size to 100003 and it worked fine and it was able to insert all the words from the book into the hash table and the output was the following:

```bash
Value for 'example': 1
Last inserted: newsletter with value 138925
First inserted: the with value 138905
Total elements: 12480
Value for 'example' after removal: Key not found!
-1
```


# Task 2: Trading Specific Algorithms

## Description
Review the API of Binance USD(S)-M Futures that can be found in 
https://binance-docs.github.io/apidocs/futures/en/#change-log. Then
 ◦ implement connectivity to the end-point GET /fapi/v1/aggTrades,
 ◦ receive a stream of trades. Write a parsing algorithm to parse the incoming stream of trades and 
print each trade in the form:
```json
 [
 {
 "a": 26129, // Aggregate tradeId
 "p": "0.01633102", // Price
 "q": "4.70443515", // Quantity
 "f": 27781, // First tradeId
 "l": 27781, // Last tradeId
 "T": 1498793709153, // Timestamp
 "m": true, // Was the buyer the maker?
 }
 ]
 ```
 ◦ measure the speed at which singular trades are parsed and comment on the algorithmic 
complexity of your parsing algorithm.

1. I begun by installing the following packages:
        - sudo apt-get install libcurl4-openssl-dev
        - sudo apt-get install nlohmann-json3-dev
2. I modified my tasks.json to add the "binance_trades.cpp" file and "-lcurl" to the compile command
3. I created a binance_trades.cpp file that would connect to the Binance API and get the trades from the /fapi/v1/aggTrades endpoint. I used the libcurl library to connect to the Binance API and get the trades. I then used the nlohmann json library to parse the incoming stream of trades and print each trade in the form:
```bash
[
    {
        "T": 1724747667662,
        "a": 2305171792,
        "f": 5323850839,
        "l": 5323850839,
        "m": true,
        "p": "62690.60",
        "q": "0.002"
    },
    {
        "T": 1724747667662,
        "a": 2305171793,
        "f": 5323850840,
        "l": 5323850843,
        "m": true,
        "p": "62690.00",
        "q": "0.083"
    },
    {
        "T": 1724747667771,
        "a": 2305171794,
        "f": 5323850844,
        "l": 5323850844,
        "m": true,
        "p": "62690.00",
        "q": "0.116"
    },
    {
        "T": 1724747668177,
        "a": 2305171795,
        "f": 5323850845,
        "l": 5323850845,
        "m": true,
        "p": "62690.00",
        "q": "0.001"
    },
    {
        "T": 1724747668216,
        "a": 2305171796,
        "f": 5323850846,
        "l": 5323850846,
        "m": false,
        "p": "62690.10",
        "q": "0.433"
    }
]
Time taken to parse trades: 0.000353793 seconds
 ```

## Algorithmic Complexity

**JSON Parsing**: $(O(n))$, where $(n)$ is the size of the JSON string.

**Formatting Trades**: $(O(m))$, where $(m)$ is the number of trades in the JSON array.

Since the JSON parsing and formatting trades are sequential operations, the overall complexity is the sum of their complexities:

$ O(n) + O(m) $

In most cases, $(n)$ (the size of the JSON string) is proportional to $(m)$ (the number of trades), so the complexity can be simplified to:

$ O(n) $

The algorithmic complexity of the fetchAggTrades function is (O(n)), where $(n)$ is the size of the JSON string being parsed. This is a linear time complexity, indicating that the time taken to parse and format the trades grows linearly with the size of the input JSON data.

If the size of the JSON data increases, the time taken to parse and format the trades will also increase linearly. This linear relationship between the input size and the time taken to process the data is a characteristic of algorithms with linear time complexity. If we were to parse from multiple streams, the time complexity would be $O(n*m)$, where $n$ is the number of streams and $m$ is the size of the JSON string and a possible optimization would be to use a multi-threaded approach to parse the streams concurrently or a distributed system to parse the streams in parallel.