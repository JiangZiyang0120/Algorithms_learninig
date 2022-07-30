//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_INSERTION_SORT_H
#define ALGORITHMS_INSERTION_SORT_H

#include "SortHeader.h"

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &__orderInsertionSort(CONT<T> &V) {
    size_t length = V.size();
    if (length <= 1) return V;
    for (size_t i = 1; i != length; ++i) {
        T key = V[i];
        size_t j = i;
        while (--j != -1 && V[j] >= key) {
            V[j + 1] = V[j];
        }
        // because j needs to decrease itself one time before matching V[j] <= key
        // Thus we need to use V[j + 1] to replace the index which matches V[index] <= key
        V[j + 1] = key;
    }
    return V;
}


template <typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &insertionSort(CONT<T> &V){
    return __orderInsertionSort(V);
}

template <typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseInsertionSort(CONT<T> &V){
    CONT<T> &A = __orderInsertionSort(V);
    std::reverse(A.begin(), A.end());
    return A;
}
#endif //ALGORITHMS_INSERTION_SORT_H
