//
// Created by DYF on 2022/6/23.
//

#include <vector>
#include <iostream>
#include "../algorithms.h"
# include "./Test/test.h"

/* This function shows each sort algorithms' API
 * The input and output vectors are all l-value
 * The default order is beginning with the min value and gradually increasing to the max value
 * The functions is named in hump nomenclature.
 * If you want the revers order different from the default order,
 * you need to add "reverse" in the front of the function name and take care of its naming notations
 */
void theShowFunction() {
    std::vector<double> a = {1.2, 3.9, 2.4, 6.4, 2.1, 1.3, 2.1, 7.0, 5.2, -3, 0};

    // Intersect sort function
    a = insertionSort(a);
    // you can sort a vector without returning it
    reverseInsertionSort(a);

    // Merge sort function
    a = mergeSort(a);
    a = reverseMergeSort(a);

    // heap sort function
    // This function is built by the max-heap principle but also return the default order
    a = heapSort(a);
    a = reverseHeapSort(a);
}

class testtype{
public:
    bool operator<(testtype &l){
        return this->a < l.a;
    }

    testtype &operator=(testtype &b){
        this->a = b.a;
        return *this;
    }

    testtype(double b):a(b){}
private:
    double a;
};

viod showResult(){
    std::vector<double> a = {1.2, 3.9, 2.4, 6.4, 2.1, 1.3, 2.1, 7.0, 5.2, -3, 0};
    std::cout<<mergeSort(a)<<std::endl;

    std::vector<testtype> b = {1.2, 3.9, 2.4, 6.4, 2.1, 1.3, 2.1, 7.0, 5.2, -3, 0};
    std::cout<<heapSort(a)<<std::endl;
}