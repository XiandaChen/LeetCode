#include <iostream>

template <typename T>
class Node {
public:
    T data;          // Data stored in the node
    Node* next;      // Pointer to the next node
    Node* previous;  // Pointer to the previous node

    Node(const T& item) : data(item), next(nullptr), previous(nullptr) {} // Constructor to initialize a node
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head; // Pointer to the head of the doubly linked list
    Node<T>* tail; // Pointer to the tail of the doubly linked list

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {} // Constructor initializes an empty doubly linked list

    ~DoublyLinkedList() {
        // Destructor to deallocate memory when the doubly linked list goes out of scope
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return head == nullptr; // Doubly linked list is empty when the head is null
    }

    void insertFront(const T& item) {
        // Insert a new node at the front of the doubly linked list
        Node<T>* newNode = new Node<T>(item);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }

        std::cout << "Inserted: " << item << " at the front" << std::endl;
    }

    void insertBack(const T& item) {
        // Insert a new node at the back of the doubly linked list
        Node<T>* newNode = new Node<T>(item);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        }

        std::cout << "Inserted: " << item << " at the back" << std::endl;
    }

    void display() const {
        // Display the elements in the doubly linked list
        Node<T>* current = head;
        std::cout << "Doubly linked list elements: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void remove(const T& item) {
        // Remove a node with the specified data from the doubly linked list
        Node<T>* current = head;

        while (current != nullptr && current->data != item) {
            current = current->next;
        }

        if (current != nullptr) {
            if (current->previous != nullptr) {
                current->previous->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->previous = current->previous;
            } else {
                tail = current->previous;
            }

            std::cout << "Removed: " << item << std::endl;
            delete current;
        } else {
            std::cout << "Element not found. Cannot remove." << std::endl;
        }
    }
};

template <typename T>
class LinkedQueue {
private:
    DoublyLinkedList<T> list; // Use a doubly linked list as the underlying structure for the queue

public:
    LinkedQueue() {} // Constructor initializes an empty linked queue

    bool isEmpty() const {
        return list.isEmpty(); // Linked queue is empty when the underlying list is empty
    }

    void enqueue(const T& item) {
        // Enqueue an item into the linked queue
        list.insertBack(item);
    }

    void dequeue() {
        // Dequeue an item from the linked queue
        if (!isEmpty()) {
            T frontItem = list.getFront();
            list.remove(frontItem);
        } else {
            std::cout << "Queue is empty. Cannot dequeue." << std::endl;
        }
    }

    T getFront() const {
        // Get the front item of the linked queue
        return list.getFront();
    }

    void display() const {
        // Display the elements in the linked queue
        list.display();
    }
};

int main() {
    // Create a doubly linked list
    DoublyLinkedList<int> myList;

    // Insert elements into the doubly linked list
    myList.insertFront(10);
    myList.insertBack(20);
    myList.insertBack(30);

    // Display the elements in the doubly linked list
    myList.display();

    // Remove an element from the doubly linked list
    myList.remove(20);

    // Display the elements in the doubly linked list after removal
    myList.display();

    // Create a linked queue
    LinkedQueue<int> myQueue;

    // Enqueue elements into the linked queue
    myQueue.enqueue(40);
    myQueue.enqueue(50);

    // Display the front element of the linked queue
    std::cout << "Front element of the queue: " << myQueue.getFront() << std::endl;

    // Dequeue elements from the linked queue
    myQueue.dequeue();
    myQueue.dequeue();

    // Attempt to dequeue from an empty linked queue
    myQueue.dequeue();

    return 0;
}
