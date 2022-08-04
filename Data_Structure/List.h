//
// Created by jiang-ziyang on 22-8-4.
//

#ifndef MAIN_CPP_LIST_H
#define MAIN_CPP_LIST_H

#include "DS_Header.h"

template<typename T>
class List;

template<typename T>
class Node {
    friend class List<T>;

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, Node<NAME> &);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, Node<NAME> &&);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, List<NAME> &);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, List<NAME> &&);

private:
    Node() : prevNode(NULL), nextNode(NULL) {}

    Node(T rs) : elem(rs), prevNode(NULL), nextNode(NULL) {}

    Node(T rs, class Node<T> *prev) : elem(rs), prevNode(prev), nextNode(NULL) {}

    Node(T rs, class Node<T> *prev, class Node<T> *next) :
            elem(rs), prevNode(prev), nextNode(next) {}

    T elem;

    class Node<T> *prevNode;

    class Node<T> *nextNode;
};

template<typename T>
class List {
    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, List<NAME> &);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, List<NAME> &&);

public:
    List() : head(new class Node<T>), tail(new class Node<T>) {
        head->nextNode = tail;
        tail->prevNode = head;
    }

    List(T rs) : List() {
        insert(rs);
    }

    class Node<T> *search(T);

    void insert(T);

    void insert(T, class Node<T> *);

    void remove(class Node<T> *);

    void remove(T);

private:
    class Node<T> *head;

    class Node<T> *tail;
};

template<typename T>
class Node<T> *List<T>::search(T rs) {
    for (auto pointer = head->nextNode; pointer != tail; pointer = pointer->nextNode) {
        if (pointer->elem == rs)
            return pointer;
    }
    return NULL;
}

template<typename T>
void List<T>::insert(T rs) {
    tail->prevNode = new class Node<T>(rs, tail->prevNode, tail);
    tail->prevNode->prevNode->nextNode = tail->prevNode;
}

template<typename T>
void List<T>::insert(T rs, class Node<T> *pointer) {
    pointer->nextNode = new class Node<T>(rs, pointer, pointer->nextNode);
    pointer->nextNode->nextNode->prevNode = pointer->nextNode;
}

template<typename T>
void List<T>::remove(class Node<T> *pointer) {
    if (pointer == NULL)
        throw std::runtime_error("No pointer points an Node");
    pointer->prevNode->nextNode = pointer->nextNode;
    pointer->nextNode->prevNode = pointer->prevNode;
    delete pointer;
}


template<typename T>
void List<T>::remove(T rs) {
    class Node<T> *pointer = search(rs);
    remove(pointer);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, Node<T> &N) {
    return os << N.elem;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, Node<T> &&N) {
    return os << N.elem;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, List<T> &L) {
    for(auto pointer = L.head->nextNode; pointer != L.tail; pointer = pointer->nextNode){
        os<<*pointer<<", ";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, List<T> &&L) {
    for(auto pointer = L.head->nextNode; pointer != L.tail; pointer = pointer->nextNode){
        os<<*pointer<<", ";
    }
    return os;
}

#endif //MAIN_CPP_LIST_H