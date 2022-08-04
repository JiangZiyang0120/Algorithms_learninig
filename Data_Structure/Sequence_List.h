//
// Created by jiang-ziyang on 22-8-3.
//

#ifndef MAIN_CPP_SEQUENCE_LIST_H
#define MAIN_CPP_SEQUENCE_LIST_H

#include "DS_Header.h"

#define DEFAULT_ARRAY_LENGTH 1

template<typename T>
class Sequence {
public:
    Sequence(size_t size) : arraySize(size) {
        this->array = new T[size];
    }

    Sequence() : arraySize(DEFAULT_ARRAY_LENGTH) {
        this->array = new T[this->arraySize];
    }

//    template<T,
//            template<typename = T, typename =std::allocator<T>> class CONT>
//    Sequence(CONT<T> const &A): Sequence(A.size()), size(A.size()){
//        size_t index = 0;
//        for (auto iter = A.begin(); iter != A.end(); ++iter) {
//            this->array[index] = *iter;
//        }
//    }

    ~Sequence() {
        delete[]this->array;
        this->arraySize = 0;
    }

protected:
    void expense(size_t length);

    void expense();

protected:
    T *array;
    size_t arraySize;
};

template<typename T>
void Sequence<T>::expense(size_t length) {
    T *temp = new T[length];
    for (size_t i = 0; i != this->arraySize; ++i) {
        temp[i] = this->array[i];
    }
    this->arraySize = length;
    delete[] this->array;
    this->array = temp;
}

template<typename T>
void Sequence<T>::expense() {
    expense(2 * this->arraySize);
}

#endif //MAIN_CPP_SEQUENCE_LIST_H
