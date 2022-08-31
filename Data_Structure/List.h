//
// Created by jiang-ziyang on 22-8-4.
//

#ifndef MAIN_CPP_LIST_H
#define MAIN_CPP_LIST_H

#include "DS_Header.h"

template<typename T>
class List;

template<class T>
class ListIterator;

template<typename T>
class Node {
    friend class ListIterator<T>;

    friend class List<T>;

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, Node<NAME> &);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, Node<NAME> &&);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, List<NAME> &);

    template<typename NAME>
    friend std::ostream &operator<<(std::ostream &, List<NAME> &&);

public:
    T getElem();

private:
    Node() = default;

    explicit Node(T rs) : elem(rs), prevNode(NULL), nextNode(NULL) {}

    Node(T rs, class Node<T> *prev, class Node<T> *next) :
            elem(rs), prevNode(prev), nextNode(next) {}

    T elem;

    class Node<T> *prevNode;

    class Node<T> *nextNode;
};

template<typename T>
T Node<T>::getElem() {
    return elem;
}

template<class T>
class ListIterator : public MyIterator<Node<T>> {
public:

    explicit ListIterator(Node<T> *p) : MyIterator<Node<T>>(p) {}

    ListIterator<T> &operator++();

    const ListIterator<T> operator++(int);

    T &operator*();

    T *operator->();

    Node<T> *get();
};

template<typename T>
ListIterator<T> &ListIterator<T>::operator++() {
    this->_ptr = this->_ptr->nextNode;
    return *this;
}

template<typename T>
const ListIterator<T> ListIterator<T>::operator++(int) {
    MyIterator<Node<T>> temp = *this;
    this->_ptr = this->_ptr->nextNode;
    return temp;
}

template <typename T>
Node<T> *ListIterator<T>::get() {
    return this->_ptr;
}

template<typename T>
T &ListIterator<T>::operator*() {
    return this->_ptr->elem;
}

template <typename T>
T *ListIterator<T>::operator->() {
    return &(this->_ptr->elem);
}

template<typename T>
class List {
public:
    List() : head(new class Node<T>), tail(new class Node<T>) {
        head->nextNode = tail;
        tail->prevNode = head;
    }

    explicit List(T rs) : List() {
        insert(rs);
    }

    ~List() {
        for (class Node<T> *pointer = tail; pointer != head;) {
            auto temp = pointer;
            pointer = pointer->prevNode;
            delete temp;
        }
        delete head;
    }

    List<T> &operator=(List<T> const &RS) {
        class Node<T> *thisHead = new class Node<T>, *thisPointer;
        for (auto pointer = RS.head->nextNode; pointer != RS.tail; pointer = pointer->nextNode) {
            thisPointer->nextNode = new class Node<T>(pointer->getElem());
            thisPointer->nextNode->prevNode = thisPointer;
            thisPointer = thisPointer->nextNode;
        }
        clear();
        head->nextNode = thisHead->nextNode;
        tail->prevNode = thisPointer;
        thisPointer->nextNode = tail;
        return *this;
    }

    List<T> &operator=(List<T> &&RS) noexcept {
        clear();
        if (!RS.empty()) {
            head->nextNode = RS.head->nextNode;
            RS.head->nextNode->prevNode = head;
            tail->prevNode = RS.tail->prevNode;
            RS.tail->prevNode->nextNode = tail;
            RS.head->nextNode = RS.tail;
            RS.tail->prevNode = RS.head;
        }
        return *this;
    }

    List<T>(List<T> const &RS) {
        head = new class Node<T>;
        tail = new class Node<T>;
        head->nextNode = tail;
        tail->prevNode = head;
        for (auto pointer = RS.head->nextNode; pointer != RS.tail; pointer = pointer->nextNode) {
            insert(pointer->getElem());
        }
    }

    List<T>(List<T> &&RS) noexcept {
        head = new class Node<T>;
        tail = new class Node<T>;
        head->nextNode = tail;
        tail->prevNode = head;
        if (!RS.empty()) {
            head->nextNode = RS.head->nextNode;
            RS.head->nextNode->prevNode = head;
            tail->prevNode = RS.tail->prevNode;
            RS.tail->prevNode->nextNode = tail;
            RS.head->nextNode = RS.tail;
            RS.tail->prevNode = RS.head;
        }
    }

    class Node<T> *search(T);

    void insert(T);

    void insert(T, class Node<T> *);

    void remove(class Node<T> *);

    void remove(T);

    void clear();

    bool empty();

    explicit operator bool();

    ListIterator<T> begin();

    ListIterator<T> end();

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
    auto pointer = new class Node<T>(rs, tail->prevNode, tail);
    tail->prevNode = pointer;
    pointer->prevNode->nextNode = pointer;
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
void List<T>::clear() {
    if (empty())
        return;
    for (auto pointer = tail->prevNode; pointer != head;) {
        auto temp = pointer;
        pointer = pointer->prevNode;
        delete temp;
    }
    head->nextNode = tail;
    tail->prevNode = head;
}

template<typename T>
ListIterator<T> List<T>::begin() {
    return ListIterator<T>(head->nextNode);
}

template<typename T>
ListIterator<T> List<T>::end() {
    return ListIterator<T>(tail);
}

template<typename T>
bool List<T>::empty() {
    return head->nextNode == tail;
}

template<typename T>
List<T>::operator bool() {
    return !empty();
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
    for (auto pointer = L.begin(); pointer != L.end(); ++pointer) {
        os << *pointer << ", ";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, List<T> &&L) {
    for (auto pointer = L.begin(); pointer != L.end(); ++pointer) {
        os << *pointer << ", ";
    }
    return os;
}

#endif //MAIN_CPP_LIST_H