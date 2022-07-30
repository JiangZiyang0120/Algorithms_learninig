//
// Created by jiang-ziyang on 22-7-20.
//

#ifndef ALGORITHMS_RADIX_SORT_H
#define ALGORITHMS_RADIX_SORT_H

#include "SortHeader.h"

template <typename T>
inline size_t returnItself(T i){
    return static_cast<size_t>(i);
}

template <typename T = size_t,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &countingSort(CONT<T> &A, T k, size_t (*T2size_t)(T) = returnItself) {
    std::vector<T> Num;
    Num.reserve(A.size());
    for (auto iter = A.begin(); iter != A.end(); ++iter) {
        Num.push_back(T2size_t(*iter));
    }
    CONT<T> Count = CONT<T>(k + 1);
    CONT<T> Temp = CONT<T>(A.size());
    /*
     * Because the countingSort won't change the relative position of each element,
     * we could construct a simple and intuitive map from the sorted vector and A.
     * Each element from two vectors are linked by their T value and T2T value.
     * And just translate elements of Temp into A by their T2T value and their
     * relative position like countingSort. Then it works.
     */
    for (T i = 0; i != Num.size(); ++i)
        ++Count[Num[i]];
    for (T j = 1; j != k + 1; ++j)
        Count[j] += Count[j - 1];
    for (T j = A.size() - 1; j != -1; --j) {
        Temp[Count[T2size_t(A[j])] - 1] = A[j];
        --Count[T2size_t(A[j])];
    }
    A.swap(Temp);
    return A;
}

template <typename T = size_t,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseCountingSort(CONT<T> &A, T k) {
    A = countingSort(A, k);
    std::reverse(A.begin(), A.end());
    return A;
}

#endif //ALGORITHMS_RADIX_SORT_H
