#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : data(value) {
        std::cout << "Constructing MyClass with value: " << data << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructing MyClass with value: " << data << std::endl;
    }

    void display() const {
        std::cout << "Data: " << data << std::endl;
    }

private:
    int data;
};

int main() {
    // Creating a unique_ptr and initializing it with a dynamically allocated object
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(42);

    // Using the unique_ptr
    uniquePtr->display();

    // unique_ptr automatically releases the memory when it goes out of scope
    // or when explicitly reset
    uniquePtr.reset();

    // Attempting to access the object after reset would result in an error

    return 0;
}
