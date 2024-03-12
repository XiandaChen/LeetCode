#include <iostream>

template <typename T>
class Node {
public:
    T data;         // Data stored in the node
    Node* next;     // Pointer to the next node

    Node(const T& item) : data(item), next(nullptr) {} // Constructor to initialize a node
};

template <typename T>
class LinkedQueue {
private:
    Node<T>* front; // Pointer to the front of the linked queue
    Node<T>* rear;  // Pointer to the rear of the linked queue

public:
    LinkedQueue() : front(nullptr), rear(nullptr) {} // Constructor initializes an empty linked queue

    ~LinkedQueue() {
        // Destructor to deallocate memory when the linked queue goes out of scope
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr; // Ensure rear is also set to null
    }

    bool isEmpty() const {
        return front == nullptr; // Linked queue is empty when the front is null
    }

    void enqueue(const T& item) {
        // Enqueue a new node at the rear of the linked queue
        Node<T>* newNode = new Node<T>(item);

        if (isEmpty()) {
            front = rear = newNode; // If the queue is empty, front and rear point to the new node
        } else {
            rear->next = newNode; // Link the current rear to the new node
            rear = newNode;       // Update rear to the new node
        }

        std::cout << "Enqueued: " << item << std::endl;
    }

    void dequeue() {
        if (!isEmpty()) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;

            std::cout << "Dequeued" << std::endl;

            if (front == nullptr) {
                rear = nullptr; // If the last element is dequeued, update rear to null
            }
        } else {
            std::cout << "Queue is empty. Cannot dequeue element." << std::endl;
        }
    }

    T getFront() const {
        if (!isEmpty()) {
            return front->data; // Return the data of the front node
        } else {
            throw std::runtime_error("Queue is empty. Cannot get front element.");
        }
    }
};

int main() {
    // Create a linked queue of integers
    LinkedQueue<int> myQueue;

    // Enqueue elements into the linked queue
    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);

    // Display the front element
    std::cout << "Front element: " << myQueue.getFront() << std::endl;

    // Dequeue elements from the linked queue
    myQueue.dequeue();
    myQueue.dequeue();
    myQueue.dequeue();

    // Attempt to dequeue from an empty linked queue
    myQueue.dequeue();

    return 0;
}
