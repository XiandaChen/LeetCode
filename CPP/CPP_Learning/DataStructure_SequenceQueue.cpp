#include <iostream>

const int MAX_SIZE = 100; // Maximum size of the queue

template <typename T>
class SeqQueue {
private:
    T data[MAX_SIZE]; // Array to store queue elements
    int front;         // Index of the front element
    int rear;          // Index of the rear element

public:
    SeqQueue() : front(0), rear(0) {} // Constructor initializes an empty queue

    bool isEmpty() const {
        return front == rear; // Queue is empty when front equals rear
    }

    bool isFull() const {
        return (rear + 1) % MAX_SIZE == front; // Queue is full when the next rear index is equal to front
    }

    void enqueue(const T& item) {
        if (!isFull()) {
            data[rear] = item;         // Add the item to the rear
            rear = (rear + 1) % MAX_SIZE; // Update the rear index, considering circular wrapping
            std::cout << "Enqueued: " << item << std::endl;
        } else {
            std::cout << "Queue is full. Cannot enqueue element." << std::endl;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            std::cout << "Dequeued: " << data[front] << std::endl; // Remove the front element
            front = (front + 1) % MAX_SIZE;                         // Update the front index, considering circular wrapping
        } else {
            std::cout << "Queue is empty. Cannot dequeue element." << std::endl;
        }
    }

    T getFront() const {
        if (!isEmpty()) {
            return data[front]; // Return the front element
        } else {
            throw std::runtime_error("Queue is empty. Cannot get front element.");
        }
    }
};

int main() {
    // Create a queue of integers
    SeqQueue<int> myQueue;

    // Enqueue elements into the queue
    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);

    // Display the front element
    std::cout << "Front element: " << myQueue.getFront() << std::endl;

    // Dequeue elements from the queue
    myQueue.dequeue();
    myQueue.dequeue();
    myQueue.dequeue();

    // Attempt to dequeue from an empty queue
    myQueue.dequeue();

    return 0;
}
