#include <iostream>

template <typename T>
class Node {
public:
    T data;         // Data stored in the node
    Node* next;     // Pointer to the next node

    Node(const T& item) : data(item), next(nullptr) {} // Constructor to initialize a node
};

template <typename T>
class CircularLinkedList {
private:
    Node<T>* head; // Pointer to the head of the circular linked list

public:
    CircularLinkedList() : head(nullptr) {} // Constructor initializes an empty circular linked list

    ~CircularLinkedList() {
        // Destructor to deallocate memory when the circular linked list goes out of scope
        if (head == nullptr) {
            return; // List is already empty
        }

        Node<T>* current = head->next;
        while (current != head) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }

        delete head; // Delete the head node
    }

    bool isEmpty() const {
        return head == nullptr; // Circular linked list is empty when the head is null
    }

    void insertFront(const T& item) {
        // Insert a new node at the front of the circular linked list
        Node<T>* newNode = new Node<T>(item);
        if (isEmpty()) {
            head = newNode;
            head->next = head; // Point the only node to itself
        } else {
            newNode->next = head->next;
            head->next = newNode;
        }

        std::cout << "Inserted: " << item << " at the front" << std::endl;
    }

    void insertBack(const T& item) {
        // Insert a new node at the back of the circular linked list
        Node<T>* newNode = new Node<T>(item);
        if (isEmpty()) {
            head = newNode;
            head->next = head; // Point the only node to itself
        } else {
            newNode->next = head->next;
            head->next = newNode;
            head = newNode; // Update the head to the new node
        }

        std::cout << "Inserted: " << item << " at the back" << std::endl;
    }

    void display() const {
        // Display the elements in the circular linked list
        if (isEmpty()) {
            std::cout << "Circular linked list is empty." << std::endl;
            return;
        }

        Node<T>* current = head->next;
        std::cout << "Circular linked list elements: " << current->data << " ";
        while (current != head) {
            current = current->next;
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }

    void remove(const T& item) {
        // Remove a node with the specified data from the circular linked list
        if (isEmpty()) {
            std::cout << "Circular linked list is empty. Cannot remove." << std::endl;
            return;
        }

        Node<T>* current = head->next;
        Node<T>* prev = head;

        do {
            if (current->data == item) {
                prev->next = current->next;
                delete current;

                std::cout << "Removed: " << item << std::endl;
                return;
            }

            prev = current;
            current = current->next;
        } while (current != head);

        std::cout << "Element not found. Cannot remove." << std::endl;
    }
};

int main() {
    // Create a circular linked list
    CircularLinkedList<int> myList;

    // Insert elements into the circular linked list
    myList.insertFront(10);
    myList.insertBack(20);
    myList.insertBack(30);

    // Display the elements in the circular linked list
    myList.display();

    // Remove an element from the circular linked list
    myList.remove(20);

    // Display the elements in the circular linked list after removal
    myList.display();

    return 0;
}
