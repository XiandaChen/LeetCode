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

// Function taking a std::unique_ptr by value (ownership transfer)
void processUniquePtr(std::unique_ptr<MyClass> ptr) {
    std::cout << "Inside processUniquePtr function." << std::endl;
    ptr->display();
    // The unique_ptr will automatically delete the object when it goes out of scope
}

int main() {
    // Creating a unique_ptr and initializing it with a dynamically allocated object
    std::unique_ptr<MyClass> uniquePtr1 = std::make_unique<MyClass>(42);

    // Using std::move to transfer ownership to another std::unique_ptr
    std::unique_ptr<MyClass> uniquePtr2 = std::move(uniquePtr1);

    // Attempting to access uniquePtr1 here would result in a compilation error,
    // as ownership has been transferred to uniquePtr2.

    // Using the unique_ptr
    if (uniquePtr2) {
        uniquePtr2->display();
    } else {
        std::cout << "uniquePtr2 is null." << std::endl;
    }

    // Passing a unique_ptr to a function (ownership transfer)
    processUniquePtr(std::move(uniquePtr2));

    // Attempting to access uniquePtr2 here would result in a compilation error,
    // as ownership has been transferred to the processUniquePtr function.

    return 0;
}
