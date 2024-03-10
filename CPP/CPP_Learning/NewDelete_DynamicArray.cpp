#include <iostream>
class DynamicArray {
private:
    int* data;
    size_t size;
public:
    DynamicArray(size_t sz) : size(sz) {
        data = new int[size];
    }
    ~DynamicArray() {
        delete[] data;
    }
    void printArray() const {
        std::cout << "Array elements: " << std::endl;
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};
int main() {
    DynamicArray* arr = new DynamicArray(5);
    arr->printArray();
    return 0;
}