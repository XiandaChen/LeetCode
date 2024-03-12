New/delete in C++
1. Memory Leaks:
Forgetting to call delete for memory allocated with new can lead to memory leaks.
2. Dangling Pointers:
Accessing memory through a pointer after it has been deleted can result in undefined behavior.
3. Double Deletion:
Deleting the same pointer more than once can lead to undefined behavior (double deletion).
4. Not Using delete[] with new[]:
Forgetting to use delete[] when deallocating memory allocated with new[] for arrays can lead to issues.
5. Memory Allocation Failure:
new can throw a std::bad_alloc exception if memory allocation fails. It's essential to handle this exception appropriately.
6. Manual Memory Management Complexity:
Manual memory management using new and delete can be error-prone and complex, especially in large codebases.
Smart pointers (std::unique_ptr, std::shared_ptr) offer safer and more convenient alternatives.


Smart pointers in C++ are objects designed to manage the memory of dynamically allocated objects
1. std::unique_ptr:
	Represents ownership of a dynamically allocated object.
	Ensures that the object it owns is deleted when the std::unique_ptr goes out of scope.
	Cannot be copied but can be moved.
2. std::shared_ptr:
	Represents shared ownership of a dynamically allocated object.
	Keeps track of the number of std::shared_ptr instances pointing to the same object.
	Deletes the object when the last std::shared_ptr pointing to it is destroyed.
3. std::weak_ptr:
	Represents non-owning, weak references to an object owned by std::shared_ptr.
	Does not contribute to the reference count, preventing circular references.
	Useful for breaking reference cycles.
	
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : data(value) {
        std::cout << "Constructor called. Value: " << data << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called. Value: " << data << std::endl;
    }

    void printData() const {
        std::cout << "Data: " << data << std::endl;
    }

private:
    int data;
};

int main() {
    // Using std::unique_ptr
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(42);

    // Using std::shared_ptr
    std::shared_ptr<MyClass> sharedPtr1 = std::make_shared<MyClass>(10);
    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1;

    // Using std::weak_ptr
    std::shared_ptr<MyClass> sharedPtr3 = std::make_shared<MyClass>(99);
    std::weak_ptr<MyClass> weakPtr = sharedPtr3;

    // Accessing the object through smart pointers
    uniquePtr->printData();
    sharedPtr1->printData();
    sharedPtr2->printData();

    // Check if the object is still valid using std::weak_ptr
    if (auto sharedPtr = weakPtr.lock()) {
        std::cout << "Weak pointer is still valid." << std::endl;
        sharedPtr->printData();
    } else {
        std::cout << "Weak pointer is no longer valid." << std::endl;
    }

    return 0;
}

/*
RAII stands for "Resource Acquisition Is Initialization," and it is a programming idiom in C++ where resource management is tied to the lifespan of an object. RAII is often implemented using classes, and such classes are referred to as RAII classes.

The key idea behind RAII is to use a class to manage resources in such a way that the resource is acquired during the object's construction and released during its destruction. This ensures that resources are properly managed and that the cleanup logic is automatically invoked when the object goes out of scope, regardless of how the scope is exited (e.g., due to normal flow, an exception, or an early return).
*/
