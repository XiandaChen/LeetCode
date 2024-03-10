Cast

1. Compile-Time vs. Run-Time:
	static_cast is resolved at compile time and is used for known, static type conversions.
	dynamic_cast is resolved at runtime and is used for dynamic type checking and safe downcasting.
2. Safety:
	static_cast provides less safety as it performs minimal checks during compilation.
	dynamic_cast provides more safety by performing runtime type checks, but it requires polymorphism.
3 .Usage:
	Use static_cast for simple, well-defined conversions.
	Use dynamic_cast when dealing with polymorphic types and when the actual type is determined at runtime.
4. Polymorphism:
	dynamic_cast requires at least one virtual function in the base class to enable runtime type identification.
	
5. const_cast:
	const_cast is used to add or remove const or volatile qualifiers from a variable.
		const int constantValue = 42;
		int* nonConstPtr = const_cast<int*>(&constantValue);
		
6. reinterpret_cast:
	reinterpret_cast is used for low-level type conversions between unrelated types, such as converting between pointers and integers.
		int intValue = 42;
		double* doublePtr = reinterpret_cast<double*>(&intValue);
	
/* C-style cast */
int intValue = 10;
double doubleValue = (double)intValue;  // C-style cast

/* static_cast */
class Base {};
class Derived : public Base {};
int main() {
    Base* basePtr = new Derived();
    
    // Using static_cast to convert base pointer to derived pointer
    Derived* derivedPtr = static_cast<Derived*>(basePtr);

    delete basePtr;
    return 0;
}

/* dynamic_cast */
class Base {
public:
    virtual ~Base() {}  // Ensure a polymorphic base class
};
class Derived : public Base {};
int main() {
    Base* basePtr = new Derived();
    // Using dynamic_cast to check and convert base pointer to derived pointer
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if (derivedPtr != nullptr) {
        // Successfully casted, safe to use derivedPtr
    } else {
        // Failed to cast (basePtr does not point to a Derived object)
    }
    delete basePtr;
    return 0;
}
