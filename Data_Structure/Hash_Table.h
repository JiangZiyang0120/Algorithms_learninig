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
                            size_t (*theProbeFunction)(size_t m, T k, size_t i)) :
            HashTableOpeningAddress(theSeed, theHashFunction), probeFunction(theProbeFunction) {}

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

    size_t search(T k);

    void remove(T k);

    T &operator[](size_t);

private:
    size_t linearProbing(T k, size_t i);

    size_t quadraticProbing(T k, size_t i);

    size_t doubleHashing(T k, size_t i);

private:
    const size_t tableSize;
    size_t elemNum;
    T *hashTable;
    status *statusTable;
    const time_t seed;
    const time_t doubleSeed;
    const double c1 = 2, c2 = 3;

    size_t (*const hashFunction)(size_t m, T k, time_t theSeed);

    size_t (*const probeFunction)(T k, size_t i) = doubleHashing;
};

template<typename T>
size_t HashTableOpeningAddress<T>::linearProbing(T k, size_t i) {
    return Hash<T>::linearProbing(this->tableSize, k, i, this->seed, this->hashFunction);
}

template<typename T>
size_t HashTableOpeningAddress<T>::quadraticProbing(T k, size_t i) {
    return Hash<T>::quadraticProbing(this->tableSize, k, i, this->seed, this->c1, this->c2, this->hashFunction);
}

template<typename T>
size_t HashTableOpeningAddress<T>::doubleHashing(T k, size_t i) {
    return Hash<T>::doubleHashing(this->tableSize, k, i, this->seed1, this->doubleSeed, this->hashFunction,
                                  this->hashFunction);
}

template<typename T>
void HashTableOpeningAddress<T>::insert(T k) {
    size_t i = 0;
    size_t dictation = this->probeFunction(this->tableSize, k, i), index = dictation;
    do {
        if (this->statusTable[index] == NIL || this->statusTable == DELETED) {
            this->hashTable[index] = k;
            this->statusTable[index] = FILLED;
            return;
        }
    } while ((index = this->probeFunction(this->tableSize, k, ++i)) != dictation);
    throw std::overflow_error("hash table overflow");
}

template<typename T>
size_t HashTableOpeningAddress<T>::search(T k) {
    size_t i = 0, index;
    //add 1 to prevent the case that index = 0
    while ((index = this->probeFunction(k, i)) + 1 || this->statusTable[index] != NIL) {
        if (this->hashTable[index] == k)
            return index;
    }
    return NIL;
}

template <typename T>
void HashTableOpeningAddress<T>::remove(T k) {
    auto index = search(k);
    if(index != NIL){
        this->statusTable[index] = DELETED;
        return;
    }
    throw std::runtime_error("element doesn't exist");
}

template<typename T>
T &HashTableOpeningAddress<T>::operator[](size_t index) {
    if(this->statusTable[index] == FILLED)
        return this->hashTable[index];
    return this->statusTable[index];
}



#endif //MAIN_CPP_HASH_TABLE_H