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

    static size_t multiplicativeHashing(size_t m, T k);

    static size_t universalHashing(size_t m, T k);

    static size_t universalHashing(size_t m, T k, time_t seed);

    static size_t linearProbing(size_t m, T k, size_t i, size_t (*hashFunction)(size_t, T) = universalHashing);

    static size_t
    linearProbing(size_t m, T k, size_t i, time_t seed, size_t (*hashFunction)(size_t, T, time_t) = universalHashing);

    static size_t quadraticProbing(size_t m, T k, size_t i, double c1, double c2,
                                   size_t (*hashFunction)(size_t, T) = universalHashing);

    static size_t
    quadraticProbing(size_t m, T k, size_t i, time_t seed, double c1, double c2,
                     size_t (*hashFunction)(size_t, T, time_t) = universalHashing);

    static size_t
    doubleHashing(size_t m, T k, size_t i, size_t (*hashFunction)(size_t, T) = universalHashing,
                  size_t (*hashFunction2)(size_t, T) = multiplicativeHashing);

    static size_t
    doubleHashing(size_t m, T k, size_t i, time_t seed1, time_t seed2,
                  size_t (*hashFunction)(size_t, T, time_t) = universalHashing,
                  size_t (*hashFunction2)(size_t, T) = universalHashing);
};

template<typename T>
size_t Hash<T>::divisionHashing(size_t m, T k) {
    return static_cast<size_t>(k) % m;
}

template<typename T>
size_t Hash<T>::multiplicativeHashing(size_t m, T k) {
    double temp = MULTI_FACTOR * k;
    temp = temp - ceil(temp);
    return static_cast<size_t>(m * temp);
}


template<typename T>
size_t Hash<T>::universalHashing(size_t m, T k, time_t seed) {
    largeInt digit = static_cast<largeInt >(m);
    largeInt prime = PrimeNum::getPrimeNum();
    std::default_random_engine e(seed);
    std::uniform_int_distribution<largeInt> a_(1, prime - 1), b_(0, prime - 1);
    largeInt a = a_(e), b = b_(e);
    return static_cast<size_t>((a * k + b) % prime % digit);
}

template<typename T>
size_t Hash<T>::universalHashing(size_t m, T k) {
    largeInt digit = static_cast<largeInt >(m);
    largeInt prime = PrimeNum::getPrimeNum();
    std::default_random_engine e;
    std::uniform_int_distribution<largeInt> a_(1, prime - 1), b_(0, prime - 1);
    largeInt a = a_(e), b = b_(e);
    return static_cast<size_t>((a * k + b) % prime % digit);
}

template<typename T>
size_t Hash<T>::linearProbing(size_t m, T k, size_t i, time_t seed, size_t (*hashFunction)(size_t, T, time_t)) {
    return (hashFunction(m, k, seed) + i) % m;
}

template<typename T>
size_t Hash<T>::linearProbing(size_t m, T k, size_t i, size_t (*hashFunction)(size_t, T)) {
    return (hashFunction(m, k) + i) % m;
}

template<typename T>
size_t Hash<T>::quadraticProbing(size_t m, T k, size_t i, time_t seed, double c1, double c2,
                                 size_t (*hashFunction)(size_t, T, time_t)) {
    return (hashFunction(m, k, seed) + c1 * i + c2 * i * i) % m;
}

template<typename T>
size_t Hash<T>::quadraticProbing(size_t m, T k, size_t i, double c1, double c2, size_t (*hashFunction)(size_t, T)) {
    return (hashFunction(m, k) + c1 * i + c2 * i * i) % m;
}

template<typename T>
size_t
Hash<T>::doubleHashing(size_t m, T k, size_t i, time_t seed1, time_t seed2, size_t (*hashFunction)(size_t, T, time_t),
                       size_t (*hashFunction2)(size_t, T)) {
    return (hashFunction(m, k, seed1) + i * hashFunction2(m, k, seed2)) % m;
}

template<typename T>
size_t
Hash<T>::doubleHashing(size_t m, T k, size_t i, size_t (*hashFunction)(size_t, T), size_t (*hashFunction2)(size_t, T)) {
    return (hashFunction(m, k) + i * hashFunction2(m, k)) % m;
}

#endif //MAIN_CPP_HASH_H