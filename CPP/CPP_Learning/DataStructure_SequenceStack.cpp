#include <iostream>

const int MAX_SIZE = 100; // Maximum size of the stack

template <typename T>
class SqStack {
private:
    T data[MAX_SIZE]; // Array to store stack elements
    int top;          // Index of the top element

public:
    SqStack() : top(-1) {} // Constructor initializes an empty stack

    bool isEmpty() const {
        return top == -1; // Stack is empty when top is -1
    }

    bool isFull() const {
        return top == MAX_SIZE - 1; // Stack is full when top reaches the maximum size
    }

    void push(const T& item) {
        if (!isFull()) {
            data[++top] = item; // Increment top and add the item to the stack
            std::cout << "Pushed: " << item << std::endl;
        } else {
            std::cout << "Stack overflow. Cannot push element." << std::endl;
        }
    }

    void pop() {
        if (!isEmpty()) {
            std::cout << "Popped: " << data[top--] << std::endl; // Remove the top element
        } else {
            std::cout << "Stack underflow. Cannot pop element." << std::endl;
        }
    }

    T getTop() const {
        if (!isEmpty()) {
            return data[top]; // Return the top element
        } else {
            throw std::runtime_error("Stack is empty. Cannot get top element.");
        }
    }
};

int main() {
    // Create a stack of integers
    SqStack<int> myStack;

    // Push elements onto the stack
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    // Display the top element
    std::cout << "Top element: " << myStack.getTop() << std::endl;

    // Pop elements from the stack
    myStack.pop();
    myStack.pop();
    myStack.pop();

    // Attempt to pop from an empty stack
    myStack.pop();

    return 0;
}
