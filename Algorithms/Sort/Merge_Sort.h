//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_MERGE_SORT_H
#define ALGORITHMS_MERGE_SORT_H

#include "../algorithmsHeader.h"

template<typename T>
std::vector<T> &__orderMerge(std::vector<T> &A, size_t p, size_t q, size_t r, bool isReverse) {
    std::vector<T> L, R;
    L.assign(&A[p], &A[q]);
    R.assign(&A[q], &A[r]);
    size_t ASize = r - p, LSize = q - p, RSize = r - q;
    for (size_t ai = 0, li = 0, ri = 0;
         ai != ASize; ++ai) {
        if(ri == RSize || compare(L[li],R[li],isReverse)){
            A[ai] = L[li];
            ++li;
        } else if(li == LSize || !compare(L[li],R[li],isReverse)){
            A[ai] = R[ri];
            ++ ri;
        }
    }
    return A;
}

template <typename T>
std::vector<T> &__orderMergeSort(std::vector<T> &A, size_t p, size_t r, bool isReserve){
    if(p < r){
        size_t q = (p+r)/2;
        __orderMergeSort(A,p,q,isReserve);
        __orderMergeSort(A,q,r,isReserve);
        __orderMerge(A,p,q,r,isReserve);
    }
}

template <typename T>
std::vector<T> &__orderMergeSort(std::vector<T> &A, bool isReserve){
    size_t length = A.size();
    return __orderMergeSort(A,0,length,isReserve);
}

template <typename T>
std::vector<T> &mergeSort(std::vector<T> &A){
    return __orderMergeSort(A, false);
}

template <typename T>
std::vector<T> &reverseMergeSort(std::vector<T> &A){
    return __orderMergeSort(A, true);
}

#endif //ALGORITHMS_MERGE_SORT_H
