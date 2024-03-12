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
/*
Output:
Constructing MyClass with value: 42
sharedPtr1 has object.
Data: 42
sharedPtr2 has object.
Data: 42
sharedPtr3 has object.
Data: 42

sharedPtr1 has object.
Data: 42
sharedPtr2 is null.
sharedPtr3 has object.
Data: 42

Destructing MyClass with value: 42
*/
int main() {
    // Creating a shared_ptr and initializing it with a dynamically allocated object
    std::shared_ptr<MyClass> sharedPtr1 = std::make_shared<MyClass>(42);

    // Creating two more shared_ptrs sharing ownership of the same object
    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1;
    std::shared_ptr<MyClass> sharedPtr3 = sharedPtr1;

    // All three shared_ptrs now share ownership of the same object

    // Using the shared_ptrs
    if (sharedPtr1) {
        sharedPtr1->display();
    } else {
        std::cout << "sharedPtr1 is null." << std::endl;
    }

    if (sharedPtr2) {
        sharedPtr2->display();
    } else {
        std::cout << "sharedPtr2 is null." << std::endl;
    }

    if (sharedPtr3) {
        sharedPtr3->display();
    } else {
        std::cout << "sharedPtr3 is null." << std::endl;
    }

    // Resetting one shared_ptr, reducing reference count
    sharedPtr2.reset();

    // Using the remaining shared_ptrs
    if (sharedPtr1) {
        sharedPtr1->display();
    } else {
        std::cout << "sharedPtr1 is null." << std::endl;
    }

    if (sharedPtr2) {
        sharedPtr2->display();
    } else {
        std::cout << "sharedPtr2 is null." << std::endl;
    }

    if (sharedPtr3) {
        sharedPtr3->display();
    } else {
        std::cout << "sharedPtr3 is null." << std::endl;
    }

    // The object will be deleted when the last shared_ptr owning it goes out of scope

    return 0;
}
