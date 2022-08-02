//
// Created by DYF on 2022/6/23.
//

#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H

#include <random>
#include <algorithm>
#include <cmath>
#include <utility>
#include <exception>
#include <list>
#include <map>
#include <memory>


class Sort {
public:
    template<typename T>
    std::vector<T> &insertionSort(std::vector<T> &);

    template<typename T>
    std::vector<T> &reverseInsertionSort(std::vector<T> &);

    template<typename T>
    std::vector<T> &heapSort(std::vector<T> &);

    template<typename T>
    std::vector<T> &reverseHeapSort(std::vector<T> &);

    template<typename T>
    std::vector<T> &mergeSort(std::vector<T> &);

    template<typename T>
    std::vector<T> &reverseMergeSort(std::vector<T> &);

    template<typename T>
    std::vector<T> &countingSort(std::vector<T> &, size_t, size_t (*T2size_t)(T) = NULL);

    template<typename T>
    std::vector<T> &reverseCountingSort(std::vector<T> &, size_t, size_t (*T2size_t)(T) = NULL);

    template<typename T>
    std::vector<T> &quickSort(std::vector<T> &);

    template<typename T>
    std::vector<T> &reverseQuickSort(std::vector<T> &);

    //where beginIndex and endIndex illustrate the column section participate in Sorting
    //column section: [beginIndex, endIndex]
    template<typename T>
    std::vector<std::vector<T>> &radixSort(std::vector<std::vector<T>> &, size_t beginIndex, size_t endIndex,
                                           size_t max, size_t (*T2size_t)(T) = NULL);

    template<typename T>
    std::vector<std::vector<T>> &reverseRadixSort(std::vector<std::vector<T>> &, size_t beginIndex, size_t endIndex,
                                                  size_t max, size_t (*T2size_t)(T) = NULL);

    template<typename T>
    std::vector<T> &bucketSort(std::vector<T> &, size_t sectionNum, double (*T2Unit)(T) = NULL);

    template<typename T>
    std::vector<T> &reverseBucketSort(std::vector<T> &, size_t sectionNum, double (*T2Unit)(T) = NULL);

private:
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
        if (largest != i) {
            auto temp = A[i];
            A[i] = A[largest];
            A[largest] = temp;
            __maxHeapify(A, largest);
        }
    }

    template<typename T>
    void __buildMaxHeap(std::vector<T> &A) {
        size_t heapSize = A.size();
        for (size_t i = heapSize / 2 - 1; i != -1; --i)
            __maxHeapify(A, i);
    }

    template<typename T>
    std::vector<T> &__orderMerge(std::vector<T> &A, size_t p, size_t q, size_t r) {
        std::vector<T> L, R;
        L.assign(&A[p], &A[q]);
        R.assign(&A[q], &A[r]);
        size_t LSize = q - p, RSize = r - q;
        size_t li = 0, ri = 0, ai = p;
        while (ai != r && li != LSize && ri != RSize) {
            if (L[li] < R[ri]) {
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
    size_t __partition(std::vector<T> &A, size_t p, size_t r) {
        T x = A[r - 1];
        size_t i = p - 1;
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

    template<typename T>
    size_t __randomPartition(std::vector<T> &A, size_t p, size_t r) {
        std::default_random_engine e;
        std::uniform_int_distribution<unsigned> u(p, r - 1);
        size_t i = u(e);
        T temp = A[r - 1];
        A[r - 1] = A[i];
        A[i] = temp;
        return __partition(A, p, r);
    }

    template<typename T>
    void __randomQuickSort(std::vector<T> &A, size_t p, size_t r) {
        if (p < r - 1) {
            size_t q = __randomPartition(A, p, r);
            __randomQuickSort(A, p, q);
            __randomQuickSort(A, q + 1, r);
        }
    }

    template<typename T>
    bool judgingForIndex(std::vector<T> &A, std::vector<T> &B, size_t index) {
        return A[index] < B[index];
    }

    template<typename T>
    inline static size_t returnItself(T i) {
        return static_cast<size_t>(i);
    }
};

template<typename T>
std::vector<T> &Sort::insertionSort(std::vector<T> &A) {
    size_t length = A.size();
    if (length <= 1) return A;
    for (size_t i = 1; i != length; ++i) {
        T key = A[i];
        size_t j = i;
        while (--j != -1 && A[j] >= key) {
            A[j + 1] = A[j];
        }
        // because j needs to decrease itself one time before matching A[j] <= key
        // Thus we need to use A[j + 1] to replace the index which matches A[index] <= key
        A[j + 1] = key;
    }
    return A;
}


template<typename T>
std::vector<T> &Sort::reverseInsertionSort(std::vector<T> &A) {
    insertionSort(A);
    std::reverse(A.begin(),A.end());
    return A;
}

template<typename T>
std::vector<T> &Sort::heapSort(std::vector<T> &A) {
    reverseHeapSort(A);
    std::reverse(A.begin(),A.end());
    return A;
}

template<typename T>
std::vector<T> &Sort::reverseHeapSort(std::vector<T> &A) {
    __buildMaxHeap(A);
    std::vector<T> V;
    V.reserve(A.size());
    while (A.size() != 1) {
        T temp = A[A.size() - 1];
        A[A.size() - 1] = A[0];
        A[0] = temp;
        V.push_back(*(A.end() - 1));
        A.pop_back();
        __maxHeapify(A, 0);
    }
    V.push_back(A[0]);
    // swap A with an r-value can decrease the run time
    A.swap(V);
    return A;
}

template<typename T>
std::vector<T> &Sort::mergeSort(std::vector<T> &A) {
    size_t length = A.size();
    return __orderMergeSort(A, 0, length);
}

template<typename T>
std::vector<T> &Sort::reverseMergeSort(std::vector<T> &A) {
    mergeSort(A);
    std::reverse(A.begin(),A.end());
    return A;
}

template<typename T>
std::vector<T> &Sort::countingSort(std::vector<T> &A, size_t k, size_t (*T2size_t)(T)) {
    std::vector<T> Count = std::vector<T>(k + 1);
    std::vector<T> Temp = std::vector<T>(A.size());
    if (T2size_t) {
        std::vector<T> Num;
        Num.reserve(A.size());
        for (auto iter = A.begin(); iter != A.end(); ++iter) {
            Num.push_back(T2size_t(*iter));
        }
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
    } else {
        for (T i = 0; i != A.size(); ++i)
            ++Count[A[i]];
        for (T j = 1; j != k + 1; ++j)
            Count[j] += Count[j - 1];
        for (T j = A.size() - 1; j != -1; --j) {
            Temp[Count[A[j]] - 1] = A[j];
            --Count[A[j]];
        }
    }
    A.swap(Temp);
    return A;
}


template<typename T>
std::vector<T> &Sort::reverseCountingSort(std::vector<T> &A, size_t k, size_t (*T2size_t)(T)) {
    countingSort(A);
    std::reverse(A.begin(),A.end());
    return A;
}

template<typename T>
std::vector<T> &Sort::quickSort(std::vector<T> &A) {
    size_t length = A.size();
    __randomQuickSort(A, 0, length);
    return A;
}


template<typename T>
std::vector<T> &Sort::reverseQuickSort(std::vector<T> &A) {
    quickSort(A);
    std::reverse(A.begin(),A.end());
    return A;
}

template<typename T>
std::vector<std::vector<T>> &Sort::radixSort(std::vector<std::vector<T>> &A, size_t beginIndex, size_t endIndex,
                                                size_t max, size_t (*T2size_t)(T)) {
    size_t length = A.size();
    std::vector<std::vector<T>> Temp(length);

    if (!T2size_t) {
        for (size_t index = endIndex; index != beginIndex - 1; --index) {
            std::vector<T> Count(max + 1, 0);
            for (size_t i = 0; i != length; ++i) {
                ++Count[A[i][index]];
            }
            for (size_t i = 1; i != max + 1; ++i) {
                Count[i] += Count[i - 1];
            }
            for (size_t i = length - 1; i != -1; --i) {
                size_t AIndex = A[i][index];
                --Count[AIndex];
                Temp[Count[AIndex]].swap(A[i]);
            }
            A.swap(Temp);
        }
    } else {
        for (size_t index = endIndex; index != beginIndex - 1; --index) {
            std::vector<T> Count(max + 1, 0);
            for (size_t i = 1; i != length; ++i) {
                ++Count[T2size_t(A[i][index])];
            }
            for (size_t i = 1; i != max + 1; ++i) {
                Count[i] += Count[i - 1];
            }
            for (size_t i = length - 1; i != -1; --i) {
                Temp[Count[T2size_t(A[i][index])]].swap(A[i]);
                --Count[T2size_t(A[i][index])];
            }
            A.swap(Temp);
        }
    }
    return A;
}

template<typename T>
std::vector<std::vector<T>> &Sort::reverseRadixSort(std::vector<std::vector<T>> &A, size_t beginIndex, size_t endIndex,
                                                size_t max, size_t (*T2size_t)(T)){
    radixSort(A,beginIndex,endIndex,max,T2size_t);
    std::reverse(A.begin(),A.end());
    return A;
}


template<typename T>
std::vector<T> &Sort::bucketSort(std::vector<T> &A, size_t sectionNum, double (*T2Unit)(T)) {
    std::vector<std::vector<T>> B(sectionNum);
    size_t length = A.size();
    if(!T2Unit){
        for(size_t i = 0; i != length; ++i){
            B[static_cast<size_t>(sectionNum*A[i])].push_back(A[i]);
        }
    } else{
        for(size_t i = 0; i != length; ++i){
            B[static_cast<size_t>(sectionNum*T2Unit(A[i]))].push_back(A[i]);
        }
    }
    for(size_t i = 0; i != sectionNum; ++i){
        insertionSort(B[i]);
    }
    A.clear();
    A.reserve(length);
    for(size_t i = 0; i != sectionNum; ++i){
        if(!B[i].empty())
            A.insert(A.end(),B[i].begin(),B[i].end());
    }
    return A;
}

template<typename T>
std::vector<T> &Sort::reverseBucketSort(std::vector<T> &A, size_t sectionNum, double (*T2Unit)(T)){
    A = bucketSort(A,sectionNum,T2Unit);
    std::reverse(A.begin(),A.end());
    return A;
}
#endif //ALGORITHMS_SORT_H
