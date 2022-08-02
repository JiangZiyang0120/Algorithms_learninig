//
// Created by jiang-ziyang on 22-7-22.
//
#include "../../../Include/Sort_Example_Header.h"

int main() {
    std::cout << "Heap Sort:" << std::endl;
    std::vector<double> a = {1.2, 3.9, 2.4, 6.4, 2.1, 1.3, 2.1, 7.0, 5.2, -3, 0};
    std::cout << "The list is:" << std::endl;
    std::cout << a << std::endl;
    // heap sort function
    // This function is built by the max-heap principle but also return the default order
    a = Sort::reverseHeapSort(a);
    std::cout << "The Sorted list (in reverse order) is:" << std::endl;
    std::cout << a << std::endl;
}