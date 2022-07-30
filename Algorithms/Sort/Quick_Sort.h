//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_QUICK_SORT_H
#define ALGORITHMS_QUICK_SORT_H

#include "SortHeader.h"

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
size_t __partition(CONT<T> &A, size_t p, size_t r) {
    T x = A[r - 1];
    size_t i = p-1;
    for (size_t j = p; j < r - 1; ++j) {
        if (A[j] <= x) {
            ++i;
            T temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    T temp = A[i + 1];
    A[i + 1] = A[r - 1];
    A[r - 1] = temp;
    return i + 1;
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
size_t __randomPartition(CONT<T> &A, size_t p, size_t r) {
    std::default_random_engine e;
    std::uniform_int_distribution<unsigned> u(p, r - 1);
    size_t i = u(e);
    T temp = A[r-1];
    A[r-1] = A[i];
    A[i] = temp;
    return __partition(A, p, r);
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
void __randomQuickSort(CONT<T> &A, size_t p, size_t r) {
    if (p < r - 1) {
        size_t q = __randomPartition(A, p, r);
        __randomQuickSort(A, p, q);
        __randomQuickSort(A, q + 1, r);
    }
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &quickSort(CONT<T> &A) {
    size_t length = A.size();
    __randomQuickSort(A, 0, length);
    return A;
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseQuickSort(CONT<T> &A) {
    quickSort(A);
    std::reverse(A.begin(), A.end());
    return A;
}

#endif //ALGORITHMS_QUICK_SORT_H
