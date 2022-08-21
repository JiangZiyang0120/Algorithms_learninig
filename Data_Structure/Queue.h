//
// Created by jiang-ziyang on 22-8-4.
//

#ifndef MAIN_CPP_QUEUE_H
#define MAIN_CPP_QUEUE_H

#include "DS_Header.h"
#include "Sequence_List.h"

#define DEFAULT_QUEUE_SIZE 100


template<typename T>
class Queue : private Sequence<T> {
    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, Queue<NAME> &);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, Queue<NAME> &&);

public:
    Queue() : Sequence<T>(DEFAULT_QUEUE_SIZE), head(0), tail(0), length(0) {}

    Queue(size_t size) : Sequence<T>(size), head(0), tail(0), length(0) {}

//    template<T,
//            template<typename = T, typename =std::allocator<T>> class CONT>
//    Queue(CONT<T> const &A): Sequence<T>(A), head(0), tail(0), length(A.size()) {}

    void enroll(T);

    T eject();


private:
    void sub(size_t &rs) {
        if (rs != 0)
            --rs;
        else
            rs = this->arraySize-1;
    }

    void add(size_t &rs) {
        if (rs != this->arraySize-1)
            ++rs;
        else
            rs = 0;
    }

private:
    size_t head;
    size_t tail;
    size_t length;
};

template<typename T>
void Queue<T>::enroll(T a) {
    if (this->length == this->arraySize)
        throw std::overflow_error("The queue is overflow");
    this->array[this->head] = a;
    add(this->head);
    ++this->length;
}


template<typename T>
T Queue<T>::eject() {
    if (this->length == 0)
        throw std::underflow_error("Te queue is underflow");
    auto &elem = this->array[this->tail];
    add(this->tail);
    --this->length;
    return std::move(elem);
}


template<typename T>
std::ostream &operator<<(std::ostream &os, Queue<T> &Q) {
    for (size_t i = Q.tail; i != Q.head; Q.add(i)) {
        os << Q.array[i] << ", ";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, Queue<T> &&Q) {
    for (size_t i = Q.tail; i != Q.head; Q.add(i)) {
        os << Q.array[i] << ", ";
    }
    return os;
}

#endif //MAIN_CPP_QUEUE_H
