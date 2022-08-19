//
// Created by jiang-ziyang on 22-8-7.
//

#ifndef MAIN_CPP_HASH_TABLE_H
#define MAIN_CPP_HASH_TABLE_H

#include "DS_Header.h"
#include "../Algorithms/Hash.h"
#include "../Algorithms/Prime_Num.h"

#define AS_PROBE_FUNCTOR(functor) [this](size_t m,T k, size_t i) { return functor(m,k, i); }
#define AS_HASH_FUNCTOR(functor) [this]( size_t m,T k) { return functor(m, k); }

enum status {
    NIL, DELETED, FILLED
};


template<typename T>
class HashFactor {
public:
    HashFactor(std::string handle, double mul, size_t primeNum, size_t aNum, size_t bNum) :
            hashFunction(this->hashFunctionMap[handle]), mulFactor(mul), prime(primeNum), a(aNum), b(bNum) {

    }

    HashFactor(std::string handle = "universalHashing") :
            hashFunction(this->hashFunctionMap[handle]), mulFactor(MULTI_FACTOR), prime(PrimeNum::getSizeTPrimeNum()) {
        std::default_random_engine e(time(0));
        std::uniform_int_distribution<size_t> _a(1, prime - 1), _b(0, prime - 1);
        a = _a(e);
        b = _b(e);
    }

    size_t divisionHashing(size_t m, T k);

    size_t multiplicativeHashing(size_t m, T k);

    size_t universalHashing(size_t m, T k);

private:
    const double mulFactor;
    const size_t prime;
    size_t a, b;

    std::map<std::string, std::function<size_t(size_t, T)>> hashFunctionMap = {
            {"divisionHashing",       AS_HASH_FUNCTOR(divisionHashing)},
            {"multiplicativeHashing", AS_HASH_FUNCTOR(multiplicativeHashing)},
            {"universalHashing",      AS_HASH_FUNCTOR(universalHashing)}
    };

public:
    std::function<size_t(size_t, T)> hashFunction;
};


template<typename T>
class ProbeFactor {
public:
    ProbeFactor(std::string probeHandle, std::string hashHandle1 = "universalHashing",
                std::string hashHandle2 = "universalHashing", double c1Num = 2, double c2Num = 5) :
            hash1(hashHandle1), hash2(hashHandle2), c1(c1Num), c2(c2Num) {
        probeFunction = this->probeFunctionMap[probeHandle];
    }

    size_t linearProbing(size_t m, T k, size_t i);

    size_t quadraticProbing(size_t m, T k, size_t i);

    size_t doubleHashing(size_t m, T k, size_t i);

private:
    const double c1, c2;
    HashFactor<T> const hash1, hash2;

    std::map<std::string, std::function<size_t(size_t, T, size_t)>> probeFunctionMap = {
            {"linearProbing",    AS_PROBE_FUNCTOR(linearProbing)},
            {"quadraticProbing", AS_PROBE_FUNCTOR(quadraticProbing)},
            {"doubleHashing",    AS_PROBE_FUNCTOR(doubleHashing)}
    };
public:
    std::function<size_t(size_t, T, size_t)> probeFunction;
};

template<typename T>
class HashTableOpeningAddress : private ProbeFactor<T> {
    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &os, HashTableOpeningAddress<NAME> &H);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &os, HashTableOpeningAddress<NAME> &&H);
public:
    HashTableOpeningAddress(size_t size,
                            std::string probeFunctionHandle = "doubleHashing",
                            std::string hashHandle1 = "universalHashing",
                            std::string hashHandle2 = "universalHashing") :
            tableSize(size), elemNum(0), hashTable(new T[this->tableSize]), statusTable(new status[this->tableSize]),
            ProbeFactor<T>(probeFunctionHandle, hashHandle1, hashHandle2) {}

    void insert(T k);

    size_t search(T k);

    void remove(T k);

    T &operator[](size_t);

    double loadFactor();

private:
    const size_t tableSize;
    size_t elemNum;
    T *hashTable;
    status *statusTable;
};

// class HashFactor's member functions' complement
template<typename T>
size_t HashFactor<T>::divisionHashing(size_t m, T k) {
    return Hash<T>::divisionHashing(m, k);
}

template<typename T>
size_t HashFactor<T>::multiplicativeHashing(size_t m, T k) {
    return Hash<T>::multiplicativeHashing(m, k, this->mulFactor);
}


template<typename T>
size_t HashFactor<T>::universalHashing(size_t m, T k) {
    return Hash<T>::universalHashing(m, k, this->prime, this->a, this->b);
}

// class ProbeFactor's member functions' complement
template<typename T>
size_t ProbeFactor<T>::linearProbing(size_t m, T k, size_t i) {
    return (this->hash1.hashFunction(m, k) + i) % m;
}

template<typename T>
size_t ProbeFactor<T>::quadraticProbing(size_t m, T k, size_t i) {
    return static_cast<size_t>((this->hash1.hashFunction(m, k) + this->c1 * i + this->c2 * i * i)) % m;
}

template<typename T>
size_t ProbeFactor<T>::doubleHashing(size_t m, T k, size_t i) {
    return (this->hash1.hashFunction(m, k) + i * this->hash2.hashFunction(m, k)) % m;
}

// class HashTable's member functions' complement
template<typename T>
void HashTableOpeningAddress<T>::insert(T k) {
    if (search(k) != NIL)
        return;
    size_t i = 0;
    size_t dictation = this->probeFunction(this->tableSize, k, i), index = dictation;
    do {
        if (this->statusTable[index] == NIL || this->statusTable[index] == DELETED) {
            this->hashTable[index] = k;
            this->statusTable[index] = FILLED;
            ++(this->elemNum);
            return;
        }
    } while ((index = this->probeFunction(this->tableSize, k, ++i)) != dictation);
    throw std::overflow_error("hash table overflow");
}

template<typename T>
size_t HashTableOpeningAddress<T>::search(T k) {
    size_t i = 0, index = this->probeFunction(this->tableSize, k, i);
    while (this->statusTable[index] != NIL) {
        if (this->hashTable[index] == k)
            return index;
        index = this->probeFunction(this->tableSize, k, ++i);
    }
    return NIL;
}

template<typename T>
void HashTableOpeningAddress<T>::remove(T k) {
    auto index = search(k);
    if (index != NIL) {
        this->statusTable[index] = DELETED;
        --this->elemNum;
        return;
    }
    throw std::runtime_error("element doesn't exist");
}

template<typename T>
T &HashTableOpeningAddress<T>::operator[](size_t index) {
    if (this->statusTable[index] == FILLED)
        return this->hashTable[index];
    return this->statusTable[index];
}

template<typename T>
double HashTableOpeningAddress<T>::loadFactor() {
    return 1.0 * this->elemNum / this->tableSize;
}


template<typename T>
std::ostream &operator<<(std::ostream &os, HashTableOpeningAddress<T> &H) {
    for (size_t i = 0; i != H.tableSize; ++i) {
        if (H.statusTable[i] == FILLED)
            os << H.hashTable[i] << ", ";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, HashTableOpeningAddress<T> &&H) {
    for (size_t i = 0; i != H.tableSize; ++i) {
        if (H.statusTable[i] == FILLED)
            os << H.hashTable[i] << ", ";
    }
    return os;
}


#endif //MAIN_CPP_HASH_TABLE_H