//
// Created by jiang-ziyang on 22-8-5.
//

#ifndef MAIN_CPP_HASH_H
#define MAIN_CPP_HASH_H

#include "Algo_Header.h"
#include "Prime_Num.h"

//MULTI_FACTOR = (sqrt(5)-1)/2
#define MULTI_FACTOR 0.6180339887498949

template<typename T>
class Hash {
public:
    static size_t divisionHashing(size_t m, T k);

    static size_t multiplicativeHashing(size_t m, T k, double mul = MULTI_FACTOR);

    static size_t universalHashing(size_t m, T k, size_t prime, size_t a, size_t b);
};

template<typename T>
size_t Hash<T>::divisionHashing(size_t m, T k) {
    return static_cast<size_t>(k) % m;
}

template<typename T>
size_t Hash<T>::multiplicativeHashing(size_t m, T k, double mul) {
    double temp = mul * k;
    temp = temp - ceil(temp);
    return static_cast<size_t>(m * temp);
}

template<typename T>
size_t Hash<T>::universalHashing(size_t m, T k, size_t prime, size_t a, size_t b) {
    return (a * k + b) % prime % m;
}

#endif //MAIN_CPP_HASH_H