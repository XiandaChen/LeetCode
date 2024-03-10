#include <iostream>
#include <utility>
/*
lvalue (locator value): represents an object that has a specific memory location.
	Lvalues often correspond to named variables or objects.
	You can take the address of an lvalue.
rvalue (right-hand value): represents a temporary or a value that doesn't have a persistent memory beyond its expression.
	Rvalues often correspond to temporary results of expressions.
	You cannot take the address of an rvalue.
*/
/*
X&: lvalue reference
X&&: rvalue reference
X&& &: an lvalue reference to an rvalue reference
X& &&: an rvalue reference to an lvalue reference
*/
/*
T&&: Universal references are used in template functions to capture both lvalues and rvalues.
std::forward is used to forward the received argument with its original value category.
*/
template <typename T>
void forwarder(T&& arg) {
    // Forward the argument with its original value category
    process(std::forward<T>(arg)); // without void modifier
}
// process with lvalue
void process(int& value) {
    std::cout << "process with lvalue: " << value + 10 << std::endl;
}
// process with rvalue
void process(int&& value) {
    std::cout << "process with rvalue: " << value + 100 << std::endl;
}

int main() {
    int x = 1;
    process(x);
    process(123);
    return 0;
}


/*** 
Relationship of Move semantics and Perfect forwarding:
Overlap: Move semantics often use rvalue references, and perfect forwarding can involve universal references, which are a form of rvalue references.

Complementary: Move semantics is primarily concerned with efficient resource transfer and optimization of move operations, while perfect forwarding focuses on preserving the original value category and types of function arguments.

Use Together: They are often used together, especially when designing generic functions (e.g., in template code) to ensure both efficiency and flexibility.
***/
