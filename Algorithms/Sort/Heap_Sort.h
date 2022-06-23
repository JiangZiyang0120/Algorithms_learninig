//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_HEAP_SORT_H
#define ALGORITHMS_HEAP_SORT_H

#include "SortHeader.h"

inline size_t __parent(size_t i) {
    return i / 2;
}

inline size_t __left(size_t i) {
    return 2 * i;
}

inline size_t __right(size_t i) {
    return 2 * i + 1;
}

template<typename T>
void __maxHeapify(std::vector<T> &A, size_t i) {
    size_t l = __left(i + 1) - 1, r = __right(i + 1) - 1, heapSize = A.size();
    size_t largest = (l < heapSize && A[l] > A[i]) ? l : i;
    largest = (r < heapSize && A[r] > A[largest]) ? r : largest;
    if(largest != i){
        auto temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        __maxHeapify(A, largest);
    }
}

template <typename T>
void __buildMaxHeap(std::vector<T> &A){
    size_t heapSize = A.size();
    for (size_t i = heapSize/2 - 1; i != -1; --i)
        __maxHeapify(A,i);
}

template <typename T>
std::vector<T> &reverseHeapSort(std::vector<T> &A){
    __buildMaxHeap(A);
    std::vector<T> V;
    V.reserve(A.size());
    while (A.size() != 1){
        T temp = A[A.size() - 1];
        A[A.size() - 1] = A[0];
        A[0] = temp;
        V.push_back(*(A.end()-1));
        A.pop_back();
        __maxHeapify(A,0);
    }
    V.push_back(A[0]);
    // swap A with an r-value can decrease the run time
    A.swap(V);
    return A;
}

template <typename T>
std::vector<T> &heapSort(std::vector<T> &A){
    reverseHeapSort(A);
    std::reverse(A.begin(), A.end());
    return A;
}

#endif //ALGORITHMS_HEAP_SORT_H
