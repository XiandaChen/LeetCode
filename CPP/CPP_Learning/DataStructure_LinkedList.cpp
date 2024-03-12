#include <iostream>

template <typename T>
class Node {
public:
    T data;         // Data stored in the node
    Node* next;     // Pointer to the next node

    Node(const T& item) : data(item), next(nullptr) {} // Constructor to initialize a node
};

template <typename T>
class LinkedList {
private:
    Node<T>* head; // Pointer to the head of the linked list

public:
    LinkedList() : head(nullptr) {} // Constructor initializes an empty linked list

    ~LinkedList() {
        // Destructor to deallocate memory when the linked list goes out of scope
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return head == nullptr; // Linked list is empty when the head is null
    }

    void insert(const T& item) {
        // Insert a new node at the beginning of the linked list
        Node<T>* newNode = new Node<T>(item);
        newNode->next = head;
        head = newNode;

        std::cout << "Inserted: " << item << " at the beginning" << std::endl;
    }

    void display() const {
        // Display the elements in the linked list
        Node<T>* current = head;
        std::cout << "Linked list elements: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void remove(const T& item) {
        // Remove a node with the specified data from the linked list
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current != nullptr && current->data != item) {
            prev = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            std::cout << "Removed: " << item << std::endl;
            delete current;
        } else {
            std::cout << "Element not found. Cannot remove." << std::endl;
        }
    }
};

int main() {
    // Create a linked list of integers
    LinkedList<int> myList;

    // Insert elements into the linked list
    myList.insert(10);
    myList.insert(20);
    myList.insert(30);

    // Display the elements in the linked list
    myList.display();

    // Remove an element from the linked list
    myList.remove(20);

    // Display the elements in the linked list after removal
    myList.display();

    return 0;
}
