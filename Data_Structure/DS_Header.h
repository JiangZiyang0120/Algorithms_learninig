//
// Created by jiang-ziyang on 22-8-3.
//

#ifndef MAIN_CPP_DS_HEADER_H
#define MAIN_CPP_DS_HEADER_H

#include <cstdlib>
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <memory>
#include <sstream>
#include <map>
#include <set>

inline std::string repeatString(size_t tier, std::string &&str) {
    std::string returnStr;
    for (size_t i = 0; i != tier; ++i)
        returnStr.insert(returnStr.end(), str.begin(), str.end());
    return std::move(returnStr);
}

template<class T>
class MyIterator : public std::iterator<std::input_iterator_tag, T> {
public:
    MyIterator(T *p) : _ptr(p) {}

    MyIterator<T> &operator=(const MyIterator &);

    bool operator!=(const MyIterator &);

    bool operator==(const MyIterator &);
    
    MyIterator<T> &operator++();
    
    MyIterator<T> operator++(int);
    
    T& operator*();

    T *operator->();

protected:
    T *_ptr;
};

template<class T>
MyIterator<T> &MyIterator<T>::operator=(const MyIterator<T> &iter) {
    _ptr = iter._ptr;
}

template<class T>
bool MyIterator<T>::operator!=(const MyIterator<T> &iter) {
    return _ptr != iter._ptr;
}

template<class T>
bool MyIterator<T>::operator==(const MyIterator<T> &iter) {
    return _ptr == iter._ptr;
}

template<class T>
MyIterator<T> &MyIterator<T>::operator++() {
    ++_ptr;
    return *this;
}

template<class T>
MyIterator<T> MyIterator<T>::operator++(int) {
    MyIterator temp = *this;
    ++_ptr;
    return temp;
}

template<class T>
T &MyIterator<T>::operator*() {
    return *_ptr;
}

template<class T>
T *MyIterator<T>::operator->() {
    return _ptr;
}
#endif //MAIN_CPP_DS_HEADER_H
