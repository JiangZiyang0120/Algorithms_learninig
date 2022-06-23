//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_MERGE_SORT_H
#define ALGORITHMS_MERGE_SORT_H

#include "SortHeader.h"

template<typename T>
std::vector<T> &__orderMerge(std::vector<T> &A, size_t p, size_t q, size_t r) {
    std::vector<T> L, R;
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

template<typename T>
std::vector<T> &__orderMergeSort(std::vector<T> &A, size_t p, size_t r) {
    if (p < r - 1) {
        size_t q = (p + r) / 2;
        __orderMergeSort(A, p, q);
        __orderMergeSort(A, q, r);
        __orderMerge(A, p, q, r);
    }
    return A;
}

template<typename T>
std::vector<T> &__orderMergeSort(std::vector<T> &A) {
    size_t length = A.size();
    return __orderMergeSort(A, 0, length);
}

template<typename T>
std::vector<T> &mergeSort(std::vector<T> &A) {
    return __orderMergeSort(A);
}

template<typename T>
std::vector<T> &reverseMergeSort(std::vector<T> &A) {
    auto &temp = __orderMergeSort(A);
    std::reverse(temp.begin(), temp.end());
    return temp;
}

#endif //ALGORITHMS_MERGE_SORT_H
