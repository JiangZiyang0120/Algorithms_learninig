//
// Created by jiang-ziyang on 22-8-3.
//

#ifndef MAIN_CPP_STACK_H
#define MAIN_CPP_STACK_H

#include "DS_Header.h"
#include "Sequence_List.h"


template<typename T>
class Stack : private Sequence<T> {
public:
    Stack() : Sequence<T>(), top(0) {}

    Stack(size_t size) : Sequence<T>(size), top(0) {}

//    template<T,
//            template<typename = T, typename = std::allocator<T>> class CONT>
//    Stack<T>(CONT<T> const &A):Sequence<T>(A), top(A.size()) {}

    bool empty();

    void push(T const &);

    T pop();

    size_t size();

    size_t elemNum();

private:
    size_t top;
};

template<typename T>
bool Stack<T>::empty() {
    if (this->top == 0)
        return true;
    else
        return false;
}

template<typename T>
void Stack<T>::push(const T &x) {
    if (this->top == this->arraySize) {
        this->expense(2 * this->arraySize);
    }
    this->array[top++] = x;
}

template<typename T>
T Stack<T>::pop() {
    if(this->top == 0)
        throw std::underflow_error("The Stack is underflow");
    return this->array[--top];
}

template <typename T>
size_t Stack<T>::size() {
    return this->arraySize;
}

template <typename T>
size_t Stack<T>::elemNum() {
    return this->top;
}

#endif //MAIN_CPP_STACK_H
