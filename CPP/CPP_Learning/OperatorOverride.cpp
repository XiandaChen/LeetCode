 // Operator overloading allows you to define custom behaviors for operators when applied to user-defined types (classes or structs). 
 
 #include <iostream>

class MyClass {
public:
    MyClass() {}
    MyClass(int value) : data(value) {}
    ~MyClass() {}
    
    // Overloading binary operator+
    MyClass operator+(const MyClass& other) const {
        MyClass result;
        // Define custom behavior for operator+
        result.data = this->data + other.data;
        return result;
    }
    
    // Overloading binary operator+=
    MyClass& operator+=(const MyClass& other) {
        this->data += other.data;
        return *this;  // Return a reference to the modified object
    }

    // Overloading unary operator-
    MyClass operator-() const {
        MyClass result;
        // Define custom behavior for operator-
        result.data = -this->data;
        return result;
    }

    // Overloading comparison operator==
    bool operator==(const MyClass& other) const {
        // Define custom behavior for operator==
        return this->data == other.data;
    }
    
    int getData() const {
        return this->data;
    }
private:
    int data;
};

// Non-member function for operator<<
std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
    os << "Data: " << obj.getData();
    return os;
}

int main() {
    MyClass a(5);
    MyClass b(10);
    
    // Using overloaded operators
    MyClass c = a + b;      // Calls operator+
    MyClass d = -a;         // Calls operator-
    c += a;  // Calls operator+=
    
    std::cout << c << std::endl;  // 20
    std::cout << d << std::endl;  // -5

    if (a == b) { // Calls operator==
        std::cout << "a == b" << std::endl;
    }
    else {
        std::cout << "a != b" << std::endl;
    }

    return 0;
}