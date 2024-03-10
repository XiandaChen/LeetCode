#include <iostream>
#include <vector>
#include <utility>

/*
std::move is a utility function used to indicate that an object should be treated as an rvalue, 
allowing for efficient moves instead of expensive copies, 
i.e., move semantics to improve performance when transferring ownership of resources.
*/
// Function that takes rvalue reference parameters (&&)
void processVector(std::vector<int>&& rvalueVec) {
    std::cout << "Original vector: ";
    for (int val : rvalueVec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Move the vector content to a new vector
    std::vector<int> newVector = std::move(rvalueVec);
    
    // After std::move, rvalueVec is in a valid but unspecified state

    // Display the contents of the new vector
    std::cout << "New vector: ";
    for (int val : newVector) std::cout << val << " ";
    std::cout << std::endl;
    
    newVector[0] = newVector[0] + 100;
    
    // Transfer ownership back to the original vector
    rvalueVec = std::move(newVector);
}
/*
Original vector: 1 2 3 4 5
New vector: 1 2 3 4 5
vector transferred back: 101 2 3 4 5
*/
int main()
{
    std::vector<int> originalVector = {1, 2, 3, 4, 5};
    processVector(std::move(originalVector));
    
    // After std::move, originalVector is in a valid but unspecified state

    // Transfer ownership back to originalVector
    originalVector.shrink_to_fit();  // Optional: reduce capacity to fit the size
    std::cout << "Vector transferred back: ";
    for (int val : originalVector) std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}




/*** transfer ownership of class object ***/
#include <iostream>
#include <utility>

class MyClass {
public:
    // Constructor
    MyClass(int value) : data(new int(value)) {}

    // Move constructor
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr;  // Prevent other from deleting the data
    }

    // Destructor
    ~MyClass() {
        delete data;
    }

private:
    int* data;
};

int main() {
    MyClass obj1(42);

    MyClass obj2 = std::move(obj1);  // Use std::move to invoke the move constructor

    // At this point, obj1 is in a valid but unspecified state, and obj2 owns the data.
    
    return 0;
}
