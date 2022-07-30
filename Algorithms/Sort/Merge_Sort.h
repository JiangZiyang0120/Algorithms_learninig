//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_MERGE_SORT_H
#define ALGORITHMS_MERGE_SORT_H

#include "SortHeader.h"

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &__orderMerge(CONT<T> &A, size_t p, size_t q, size_t r) {
    CONT<T> L, R;
    L.assign(&A[p], &A[q]);
    R.assign(&A[q], &A[r]);
    size_t LSize = q - p, RSize = r - q;
    size_t li = 0, ri = 0, ai = p;
    while (ai != r && li != LSize && ri != RSize) {
        if (L[li]<R[ri]) {
            A[ai] = L[li];
            ++li;
        } else {
            A[ai] = R[ri];
            ++ri;
        }
        ++ai;
    }
    while (ai != r && li != LSize) A[ai++] = L[li++];
    while (ai != r && ri != RSize) A[ai++] = R[ri++];
    return A;
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &__orderMergeSort(CONT<T> &A, size_t p, size_t r) {
    if (p < r - 1) {
        size_t q = (p + r) / 2;
        __orderMergeSort(A, p, q);
        __orderMergeSort(A, q, r);
        __orderMerge(A, p, q, r);
    }
    return A;
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &__orderMergeSort(CONT<T> &A) {
    size_t length = A.size();
    return __orderMergeSort(A, 0, length);
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &mergeSort(CONT<T> &A) {
    return __orderMergeSort(A);
}

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseMergeSort(CONT<T> &A) {
    auto &temp = __orderMergeSort(A);
    std::reverse(temp.begin(), temp.end());
    return temp;
}

#endif //ALGORITHMS_MERGE_SORT_H
