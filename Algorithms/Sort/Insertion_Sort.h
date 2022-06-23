//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_INSERTION_SORT_H
#define ALGORITHMS_INSERTION_SORT_H

#include <vector>
#include "../algorithmsHeader.h"

template<typename T>
std::vector<T> &__orderInsertionSort(std::vector<T> &V, bool isReverse) {
    size_t length = V.size();
    if (length <= 1) return V;
    for (size_t i = 1; i != length; ++i) {
        T key = V[i];
        size_t j = i;
        while (--j != -1 && !compare(V[j], key, isReverse)) {
            V[j + 1] = V[j];
        }
        // because j needs to decrease itself one time before matching V[j] <= key
        // Thus we need to use V[j + 1] to replace the index which matches V[index] <= key
        V[j + 1] = key;
    }
    return V;
}


template <typename T>
std::vector<T> &insertionSort(std::vector<T> &V){
    return __orderInsertionSort(V, false);
}

template <typename T>
std::vector<T> &reverseInsertionSort(std::vector<T> &V){
    return __orderInsertionSort(V, true);
}
#endif //ALGORITHMS_INSERTION_SORT_H
