C++ 11
1. Auto keyword: Introduces automatic type deduction for variable declarations, allowing the compiler to determine the type based on the initializer.
	auto variable = some_function_returning_int();
2. Range-based for loop: Simplifies iteration over a range of elements in a container.
	for (auto& element : container) {
		// Do something with the element
	}
3. nullptr: Introduces a new keyword nullptr to represent a null pointer, providing a safer alternative to using NULL or 0.
	int* ptr = nullptr;
4. Strongly-typed enumerations (enum class): Allows the creation of scoped enumerations, providing better type safety.
	enum class Color { Red, Green, Blue };
5. Lambda expressions: Enables the creation of anonymous functions, improving code conciseness.
	auto add = [](int a, int b) { return a + b; };
6. Smart pointers: Introduces std::unique_ptr and std::shared_ptr to manage dynamic memory more safely and efficiently.
	std::unique_ptr<int> uniquePtr(new int);
7. Move semantics: Introduces move constructors and move assignment operators, allowing more efficient transfer of resources, such as dynamic memory.
	std::vector<int> source = get_data();
	std::vector<int> destination = std::move(source);
8. Concurrency support: Adds support for multithreading with features like std::thread, std::mutex, std::condition_variable, and others in the <thread> and <mutex> headers.
	td::thread myThread([]() { /* Thread function */ });
9. Final and override specifiers: Provides explicit indication of a virtual function's intention to be overridden or not.
	class Base {
	public:
		virtual void foo() final;
	};

	class Derived : public Base {
	public:
		// Error: Cannot override final function
		// void foo() override;
	};
10. New standard library features: Introduces several additions and improvements to the C++ Standard Library, including enhancements to existing containers, algorithms, and new utilities.


C++ 14
1. Binary Literals:
Binary literals can be expressed using the 0b or 0B prefix.
	int binaryLiteral = 0b101010;
2. Generic Lambdas:
Lambdas can now use the auto specifier for their parameters, allowing them to accept a wider range of arguments.
	auto add = [](auto a, auto b) { return a + b; };
3. Return Type Deduction for Functions:
Functions can use auto as the return type, and the compiler will deduce the return type based on the function's implementation.
	auto add(int a, int b) {
		return a + b;
	}
4. Variable Templates:
Similar to function templates, C++14 introduces variable templates, allowing the creation of generic variables.
	template <typename T>
	constexpr T pi = T(3.1415926535897932385);
5. Aggregate Member Initialization:
Members of an aggregate can now be initialized using the brace syntax, similar to how arrays can be initialized.
	struct Point {
		int x;
		int y;
	};
	Point p{1, 2};
6. Relaxed constexpr Restrictions:
The restrictions on constexpr functions were relaxed, allowing more flexibility in using them.
	constexpr int add(int a, int b) {
		return a + b;
	}
7. Variable-sized Arrays:
The sizeof operator can now be used with a runtime variable, enabling the creation of variable-sized arrays.
	int n = 5;
	int array[n];
8. Sized Deallocation:
New global operator delete overloads were introduced to support sized deallocation, allowing custom allocators to deallocate memory more efficiently.
	void operator delete(void* ptr, std::size_t size);
	
	
C++ 17
1. Structured Bindings:
Allows decomposition of structures and arrays into their individual members.
	auto [x, y] = std::make_pair(1, 2);
2. if with Initialization:
Allows variable initialization within the condition of an if statement.
	if (int x = someFunction(); x > 0) {
		// Code when x is greater than 0
	}
3. std::optional:
Represents an optional (nullable) value and provides a safer alternative to using pointers or sentinel values.
	// Function that may or may not return a value
	std::optional<int> findValue(int key) {
		if (key % 2 == 0) {
			return key * 2;
		} else {
			return std::nullopt; // Indicates no value is returned
		}
	}
	std::optional<int> maybeValue = getOptionalValue();
	if (maybeValue) {
		// Value is present
	}
4. std::variant:
Represents a type-safe union, providing a type-safe way to work with different alternative types.
	#include <iostream>
	#include <variant>
	#include <string>
	// Function that returns std::variant<int, double, std::string>
	std::variant<int, double, std::string> getVariant(int choice) {
		if (choice == 1) {
			return 42;
		} else if (choice == 2) {
			return 3.14;
		} else {
			return "Hello, Variant!";
		}
	}
	int main() {
		// Using std::variant to store different types
		std::variant<int, double, std::string> myVariant = getVariant(2);
		// Visiting the variant based on its type
		std::visit([](auto&& value) {
			std::cout << "Variant Value: " << value << std::endl;
		}, myVariant);
		return 0;
	}
5. std::any:
std::any is a C++17 feature that provides a type-safe container for single values of any type. It allows you to store and retrieve values of different types in a type-safe manner without sacrificing type information. 
The std::any_cast function is used to retrieve the stored value with the specified type. It throws a std::bad_any_cast exception if the stored type does not match the specified type.
	std::any myAny = 42;
6. constexpr if:
Introduces if statements that can be evaluated at compile time based on a constant expression.
	template <typename T>
	auto square(T value) {
		if constexpr (std::is_integral_v<T>) {
			return value * value;
		} else {
			return value;
		}
	}
7. Parallel Algorithms:
Introduces parallelized versions of some standard algorithms, improving performance on multi-core processors.
	#include <algorithm>
	#include <execution>
	std::sort(std::execution::par, myVector.begin(), myVector.end());
8. Filesystem Library:
Adds the <filesystem> library, providing facilities to manipulate file systems.
	#include <filesystem>
	std::filesystem::path currentPath = std::filesystem::current_path();
9. std::invoke:
A utility function template that simplifies the invocation of callable objects.
	std::invoke([] { std::cout << "Hello, World!" << std::endl; });
10. std::byte:
Introduces a new type std::byte for representing raw byte data.
	std::byte myByte = std::byte(0xFF);
	
	
C++ 20
1 .Concepts:
Concepts allow you to specify constraints on template parameters, providing a more readable and expressive way to define template interfaces and improve error messages.
	template <typename T>
	concept Integral = std::is_integral_v<T>;

	template <Integral T>
	T square(T x) {
		return x * x;
	}
2. Ranges:
The Ranges library introduces a set of utilities for working with ranges of values, making it easier to write concise and expressive code for operations like filtering, transformation, and iteration.
	#include <ranges>
	#include <iostream>
	#include <vector>
	int main() {
		std::vector<int> numbers = {1, 2, 3, 4, 5};
		auto squared = numbers | std::views::transform([](int x) { return x * x; });
		for (int value : squared) {
			std::cout << value << ' ';
		}
		return 0;
	}
3. Coroutines:
Coroutines provide a way to write asynchronous code more naturally. The co_await keyword allows functions to be suspended, and co_yield enables the generation of sequences.
4. Three-Way Comparison Operator (<=>):
The spaceship operator (<=>) simplifies the process of defining comparison operators for user-defined types.
 the operator<=> returns a value of type std::strong_ordering, std::weak_ordering, or std::partial_ordering.
	struct Point {
		int x, y;
		auto operator<=>(const Point&) const = default;
	};
	#include <iostream>
	#include <compare>
	class MyClass {
	public:
		int value;
		// Three-Way Comparison Operator
		auto operator<=>(const MyClass& other) const {
			return value <=> other.value;
		}
	};
	int main() {
		MyClass a{15};
		MyClass b{5};
		// Using the spaceship operator for comparison
		auto result = a <=> b;
		if (result > 0) {
			std::cout << "a is greater than b." << std::endl;
		} else if (result < 0) {
			std::cout << "a is less than b." << std::endl;
		} else {
			std::cout << "a is equal to b." << std::endl;
		}
		return 0;
	}
5. Calendar and Timezone Library:
C++20 introduces a <chrono> update with calendar and timezone support, making it easier to work with dates and times.
6. Improvements in std::span:
C++20 brings enhancements to std::span, providing a non-owning reference to a contiguous sequence of objects.