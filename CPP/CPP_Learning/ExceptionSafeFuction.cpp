Guidelines for Writing Exception-Safe Functions:
// There are three levels of exception safety: basic, strong, and no-throw.
1. Use RAII (Resource Acquisition Is Initialization):
Acquire resources (e.g., memory, file handles) in constructors and release them in destructors. This ensures that resources are released even if an exception occurs.
2. Avoid Resource Leaks:
Use smart pointers, containers, and other RAII-based classes to manage resources automatically.
3. Minimize Code in Exception Handlers:
Exception handlers should be simple and avoid complex operations. Any complex operations should be performed before the main operation that might throw an exception.
4. Don't Throw Exceptions from Destructors:
Throwing exceptions from destructors can lead to undefined behavior. If an exception occurs during stack unwinding due to another exception, it can result in program termination.
5. Commit or Rollback Strategy:
If a function performs a series of operations, consider implementing a commit or rollback strategy. If an exception occurs, the state can be rolled back to the state before the operations began.
5. Use Copy and Swap Idiom:
When implementing assignment operators, use the copy-and-swap idiom to achieve strong exception safety.

/* Here's a simple example using the copy-and-swap idiom for strong exception safety: */
#include <algorithm>
#include <iostream>

class Example {
private:
    int* data;
    size_t size;

public:
    // Constructor
    Example(size_t initSize) : size(initSize), data(new int[initSize]) {}

    // Destructor
    ~Example() {
        delete[] data;
    }

    // Copy constructor (strong exception safety)
    Example(const Example& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
    }

    // Assignment operator (strong exception safety using copy-and-swap)
    Example& operator=(Example other) {
        swap(*this, other); // Use swap for strong exception safety
        return *this;
    }

    friend void swap(Example& first, Example& second) noexcept {
        using std::swap;
        swap(first.size, second.size);
        swap(first.data, second.data);
    }
};

int main() {
    try {
        Example obj1(5);
        Example obj2(10);

        // Copy assignment with strong exception safety
        obj1 = obj2;

        // ...
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
