#include "vector.h"
#include <iostream>

int main() {
    // Default Constructor & Empty Vector Check
    Vector<int> testV;
    std::cout << "Empty Vector: " << testV << std::endl;

    // Push_back Check
    testV.push_back(1);
    testV.push_back(2);
    testV.push_back(3);
    testV.push_back(4);
    testV.push_back(5);
    std::cout << "Vector after push_back: " << testV << std::endl;

    // Copy Constructor Check + Iterator
    Vector<int> v{testV};
    std::cout << "Copied Vector: " << v << std::endl;

    // Iterator Check
    std::cout << "Vector using Iterator: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Clear Check
    v.clear();
    std::cout << "Cleared Vector: " << v << std::endl;

    // Resize Check
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    std::cout << "Vector after push_back: " << v << std::endl;
    v.reserve(10);
    std::cout << "Vector after reserve(10): " << v << std::endl;

    // Shrink_to_fit Check
    v.shrink_to_fit();
    std::cout << "Vector after shrink_to_fit: " << v << std::endl;

    return 0;
}
