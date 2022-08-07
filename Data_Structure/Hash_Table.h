//
// Created by jiang-ziyang on 22-8-7.
//

#ifndef MAIN_CPP_HASH_TABLE_H
#define MAIN_CPP_HASH_TABLE_H

#include "../Algorithms/Algo_Header.h"
#include "../Algorithms/Hash.h"

enum status {
    NIL, DELETED, FILLED
};

template<typename T>
class HashTableOpeningAddress {
public:
    HashTableOpeningAddress(size_t size, time_t theSeed,
                            size_t (*theHashFunction)(size_t m, T k, time_t theSeed),
                            size_t (*theProbeFunction)(size_t m, T k, size_t i)):
            HashTableOpeningAddress(size, theSeed, theHashFunction), probeFunction(theProbeFunction) {}

    HashTableOpeningAddress(size_t size, time_t theSeed,
                            size_t (*function)(size_t m, T k, time_t theSeed)) :
            tableSize(size), elemNum(0), hashTable(new T[tableSize]), statusTable(new status[tableSize]),
            hashFunction(function), seed(theSeed), doubleSeed(static_cast<time_t>(seed * 3.2 / 2.7)) {}

    HashTableOpeningAddress(size_t size, time_t theSeed) : HashTableOpeningAddress(size, theSeed,
                                                                                   Hash<T>::universalHashing) {}

    HashTableOpeningAddress(size_t size, size_t (*function)(size_t m, T k, time_t theSeed)) :
            HashTableOpeningAddress(size, time(0), function) {}

    HashTableOpeningAddress(size_t size) : HashTableOpeningAddress(size, time(0), Hash<T>::universalHashing) {}

    HashTableOpeningAddress(size_t size, double var1, double var2) : HashTableOpeningAddress(size, time(0),
                                                                                             Hash<T>::quadraticProbing),
                                                                     c1(var1), c2(var2),
                                                                     probeFunction(quadraticProbing) {}

    void insert(T k);

private:
    size_t linearProbing(size_t m, T k, size_t i);

    size_t quadraticProbing(size_t m, T k, size_t i);

    size_t doubleHashing(size_t m, T k, size_t i);

private:
    const size_t tableSize;
    size_t elemNum;
    T *hashTable;
    status *statusTable;
    const time_t seed;
    const time_t doubleSeed;
    const double c1 = 2, c2 = 3;

    size_t (*const hashFunction)(size_t m, T k, time_t theSeed);

    size_t (*const probeFunction)(size_t m, T k, size_t i) = doubleHashing;
};

template<typename T>
size_t HashTableOpeningAddress<T>::linearProbing(size_t m, T k, size_t i) {
    return Hash<T>::linearProbing(m, k, i, this->seed, this->hashFunction);
}

template<typename T>
size_t HashTableOpeningAddress<T>::quadraticProbing(size_t m, T k, size_t i) {
    return Hash<T>::quadraticProbing(m, k, i, this->seed, this->c1, this->c2, this->hashFunction);
}

template<typename T>
size_t HashTableOpeningAddress<T>::doubleHashing(size_t m, T k, size_t i) {
    return Hash<T>::doubleHashing(m, k, i, this->seed1, this->doubleSeed, this->hashFunction, this->hashFunction);
}

template<typename T>
void HashTableOpeningAddress<T>::insert(T k) {
    size_t i = 0;
    size_t dictation = this->probeFunction(this->tableSize,k,i),index = dictation;
    do {
        if(this->statusTable[index] == NIL || this->statusTable == DELETED) {
            this->hashTable[index] = k;
            return;
        }
    } while ((index = this->probeFunction(this->tableSize,k,++i))!=dictation);
    throw std::overflow_error("hash table overflow");
}

#endif //MAIN_CPP_HASH_TABLE_H