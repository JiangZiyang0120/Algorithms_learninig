//
// Created by jiang-ziyang on 22-8-2.
//

#ifndef MAIN_CPP_SELECT_H
#define MAIN_CPP_SELECT_H

#include "Algo_Header.h"

class Select {
public:
    template<typename Iterator>
    static Iterator min(Iterator begin, Iterator end, bool (*isALess)(Iterator A, Iterator B) = compare);

    template<typename Iterator>
    static Iterator max(Iterator begin, Iterator end, bool (*isALess)(Iterator A, Iterator B) = compare);

    template<typename Iterator>
    static std::pair<Iterator, Iterator> minmax(Iterator begin, Iterator end,
                                                bool (*isALess)(Iterator A, Iterator B) = compare);

    template<typename Iterator>
    static Iterator
    select(Iterator begin, Iterator end, size_t quantile, bool (*isALess)(Iterator A, Iterator B) = compare);

private:
    template<typename Iterator>
    inline static bool compare(Iterator A, Iterator B) {
        return *A < *B;
    }

    template<typename T>
    static void __randomQuickSort(std::vector<T> &A, size_t p, size_t r) {
        if (p < r - 1) {
            size_t q = __randomPartition(A, p, r);
            __randomQuickSort(A, p, q);
            __randomQuickSort(A, q + 1, r);
        }
    }

    template<typename Iterator>
    static Iterator __partition(Iterator begin, Iterator end) {
        Iterator x = end - 1;
        Iterator i = begin - 1;
        for (Iterator j = begin; j < end - 1; ++j) {
            if (compare(j, x)) {
                ++i;
                auto temp = *i;
                *i = *j;
                *j = temp;
            }
        }
        auto temp = *(i + 1);
        *(i + 1) = *x;
        *x = temp;
        return i + 1;
    }

    template<typename Iterator>
    static Iterator __randomPartition(Iterator begin, Iterator end) {
        std::default_random_engine e;
        size_t interval = end - begin;
        std::uniform_int_distribution<unsigned> u(0, interval - 1);
        Iterator i = u(e) + begin;
        auto temp = *(end - 1);
        *(end - 1) = *i;
        *i = temp;
        return __partition(begin, end);
    }
};

template<typename Iterator>
Iterator Select::min(Iterator begin, Iterator end, bool (*isALess)(Iterator, Iterator)) {
    Iterator min_element = begin;
    for (Iterator iter = begin + 1; iter != end; ++iter)
        if (isALess(iter, min_element))
            min_element = iter;
    return min_element;
}

template<typename Iterator>
Iterator Select::max(Iterator begin, Iterator end, bool (*isALess)(Iterator, Iterator)) {
    Iterator max_element = begin;
    for (Iterator iter = begin + 1; iter != end; ++iter)
        if (isALess(max_element, iter))
            max_element = iter;
    return max_element;
}

template<typename Iterator>
std::pair<Iterator, Iterator> Select::minmax(Iterator begin, Iterator end,
                                             bool (*isALess)(Iterator, Iterator)) {
    Iterator min_element, max_element, iter, lower, upper;
    if ((end - begin) % 2 == 0) {
        min_element = (isALess(begin, (begin + 1))) ? (max_element = begin + 1, begin) : (max_element = begin, begin +
                                                                                                               1);
        iter = begin + 2;
    } else {
        min_element = max_element = begin;
        iter = begin + 1;
    }
    for (; iter != end; iter += 2) {
        lower = (isALess(iter, (iter + 1))) ? (upper = iter + 1, iter) : (upper = iter, iter + 1);
        min_element = (isALess(min_element, lower)) ? min_element : lower;
        max_element = (isALess(iter, max_element)) ? max_element : upper;
    }
    return std::pair<Iterator, Iterator>(min_element, max_element);
}

template<typename Iterator>
Iterator Select::select(Iterator begin, Iterator end, size_t quantile, bool (*isALess)(Iterator, Iterator)) {
    if (begin == end - 1)
        return begin;
    Iterator iter = __randomPartition(begin, end);
    size_t k = iter - begin + 1;
    if (k == quantile)
        return iter;
    else if(quantile < k)
        return select(begin,iter,quantile);
    else
        return select(iter+1, end, quantile-k);
}

#endif //MAIN_CPP_SELECT_H
