1. std::endl vs "\n"
1.1 std::endl:
	It not only inserts a newline character ('\n') but also flushes the output buffer. Flushing the buffer means that it ensures that all the output is written to the destination (e.g., console or file) immediately.
	Flushing the buffer can be useful in certain situations, but it may have a performance impact, especially if there is a lot of output.
		std::cout << "Hello, World!" << std::endl;
1.2 "\n":
	It only inserts a newline character ('\n') without flushing the output buffer.
	If flushing the buffer is not necessary at that point and you have a large amount of output, using "\n" might be more efficient.
	std::cout << "Hello, World!" << "\n";
In many cases, the difference in performance between std::endl and "\n" is negligible. However, if you are writing a substantial amount of output and you don't need to flush the buffer explicitly, using "\n" is generally more efficient.

2.  constexpr specifier
The constexpr specifier is used to indicate that a function or variable can be evaluated at compile time. This allows for more efficient computations and can be used in contexts where constant expressions are required.
	#include <iostream>
	// Example of a constexpr function
	// It can be evaluated at compile time if its argument is a constant expression.
	constexpr int square(int x) {
		return x * x;
	}
	int main() {
		// Example of a constexpr variable
		// Its value is known at compile time.
		constexpr int num = 5;
		// Using the constexpr function and variable
		int result = square(num);
		std::cout << "Square of " << num << " is: " << result << std::endl;
		return 0;
	}

3. Variable Templates
Similar to function templates, C++14 introduces variable templates, allowing the creation of generic variables.
	#include <iostream>
	template <typename T>
	constexpr T pi = T(3.1415926535897932385);
	int main() {
		// Example uses of the pi variable template
		double doublePi = pi<double>;
		float floatPi = pi<float>;
		std::cout << "Double Pi: " << doublePi << std::endl;
		std::cout << "Float Pi: " << floatPi << std::endl;
		return 0;
	}

4. Sized deallocation
Sized deallocation is a feature introduced in C++14 that allows the deallocation of memory using operator delete with a specified size. This can be useful when custom allocators are managing memory and need to know the size of the allocated block during deallocation.