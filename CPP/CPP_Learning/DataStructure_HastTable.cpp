#include <iostream>
#include <vector>
#include <list>

// HashNode represents a key-value pair in the hash table
template <typename K, typename V>
class HashNode {
public:
    K key;
    V value;

    HashNode(const K& k, const V& v) : key(k), value(v) {}
};

// HashTable class
template <typename K, typename V, typename Hash = std::hash<K>>
class HashTable {
private:
    std::vector<std::list<HashNode<K, V>>> table; // Vector of linked lists for separate chaining
    size_t size; // Number of elements in the hash table

public:
    // Constructor initializes the hash table with a given size
    explicit HashTable(size_t tableSize) : table(tableSize), size(0) {}

    // Hash function to determine the index in the vector
    size_t hashFunction(const K& key) const {
        Hash hash;
        return hash(key) % table.size();
    }

    // Insert a key-value pair into the hash table
    void insert(const K& key, const V& value) {
        size_t index = hashFunction(key);
        HashNode<K, V> newNode(key, value);

        // Check for duplicates and update the value if the key already exists
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }

        // Insert the new node at the front of the linked list
        table[index].emplace_front(newNode);
        ++size;
    }

    // Retrieve the value associated with a given key
    bool get(const K& key, V& value) const {
        size_t index = hashFunction(key);

        // Search for the key in the linked list at the specified index
        for (const auto& node : table[index]) {
            if (node.key == key) {
                value = node.value;
                return true; // Key found
            }
        }

        return false; // Key not found
    }

    // Remove a key-value pair from the hash table
    void remove(const K& key) {
        size_t index = hashFunction(key);

        // Iterate through the linked list to find and remove the key
        table[index].remove_if([key](const HashNode<K, V>& node) {
            return node.key == key;
        });

        --size;
    }

    // Display the contents of the hash table
    void display() const {
        for (size_t i = 0; i < table.size(); ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& node : table[i]) {
                std::cout << "[" << node.key << ": " << node.value << "] ";
            }
            std::cout << std::endl;
        }
    }

    // Get the current size of the hash table
    size_t getSize() const {
        return size;
    }
};

int main() {
    // Create a hash table with a size of 5
    HashTable<std::string, int> myHashTable(5);

    // Insert key-value pairs into the hash table
    myHashTable.insert("one", 1);
    myHashTable.insert("two", 2);
    myHashTable.insert("three", 3);
    myHashTable.insert("four", 4);
    myHashTable.insert("five", 5);

    // Display the contents of the hash table
    std::cout << "Hash Table after insertion:" << std::endl;
    myHashTable.display();

    // Retrieve and display values associated with keys
    int value;
    if (myHashTable.get("three", value)) {
        std::cout << "Value associated with key 'three': " << value << std::endl;
    } else {
        std::cout << "Key 'three' not found in the hash table." << std::endl;
    }

    // Remove a key-value pair from the hash table
    myHashTable.remove("two");

    // Display the contents of the hash table after removal
    std::cout << "\nHash Table after removal:" << std::endl;
    myHashTable.display();

    // Get the current size of the hash table
    std::cout << "\nCurrent size of the hash table: " << myHashTable.getSize() << std::endl;

    return 0;
}
