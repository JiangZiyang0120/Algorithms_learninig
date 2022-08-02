//
// Created by jiang-ziyang on 22-7-28.
//

#include "../../../Include/Sort_Example_Header.h"

int main() {
    std::cout << "---insertionSort---" << std::endl;
    std::vector<double> A = {1.2, 3.9, 2.4, 6.4, 2.1, 1.3, 2.1, 7.0, 5.2, -3, 0};
    std::cout << "The list is:" << std::endl;
    std::cout << A << std::endl;
    Sort<double,std::vector> S;
    std::cout << "The Sorted list is:" << std::endl;
    std::cout << S.insertionSort(A) << std::endl;
}