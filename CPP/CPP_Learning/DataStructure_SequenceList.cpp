#include <iostream>

const int MAX_SIZE = 100; // Maximum size of the list

template <typename T>
class SeqList {
private:
    T data[MAX_SIZE]; // Array to store list elements
    int size;          // Current size of the list

public:
    SeqList() : size(0) {} // Constructor initializes an empty list

    int getSize() const {
        return size; // Return the current size of the list
    }

    bool isEmpty() const {
        return size == 0; // List is empty when size is zero
    }

    bool isFull() const {
        return size == MAX_SIZE; // List is full when size reaches the maximum size
    }

    void insert(const T& item, int position) {
        if (!isFull() && position >= 0 && position <= size) {
            // Shift elements to make space for the new item
            for (int i = size; i > position; --i) {
                data[i] = data[i - 1];
            }

            // Insert the item at the specified position
            data[position] = item;
            ++size;

            std::cout << "Inserted: " << item << " at position " << position << std::endl;
        } else {
            std::cout << "List is full or invalid position. Cannot insert element." << std::endl;
        }
    }

    void remove(int position) {
        if (!isEmpty() && position >= 0 && position < size) {
            // Shift elements to remove the item at the specified position
            for (int i = position; i < size - 1; ++i) {
                data[i] = data[i + 1];
            }

            --size;

            std::cout << "Removed element at position " << position << std::endl;
        } else {
            std::cout << "List is empty or invalid position. Cannot remove element." << std::endl;
        }
    }

    T get(int position) const {
        if (!isEmpty() && position >= 0 && position < size) {
            return data[position]; // Return the element at the specified position
        } else {
            throw std::runtime_error("List is empty or invalid position. Cannot get element.");
        }
    }
};

int main() {
    // Create a list of integers
    SeqList<int> myList;

    // Insert elements into the list
    myList.insert(10, 0);
    myList.insert(20, 1);
    myList.insert(30, 2);

    // Display the size of the list
    std::cout << "Size of the list: " << myList.getSize() << std::endl;

    // Get and display elements from the list
    for (int i = 0; i < myList.getSize(); ++i) {
        std::cout << "Element at position " << i << ": " << myList.get(i) << std::endl;
    }

    // Remove an element from the list
    myList.remove(1);

    // Display the size of the list after removal
    std::cout << "Size of the list after removal: " << myList.getSize() << std::endl;

    return 0;
}
