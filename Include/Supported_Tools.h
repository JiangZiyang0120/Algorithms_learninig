//
// Created by jiang-ziyang on 22-7-17.
//

#ifndef ALGORITHMS_SUPPORTED_TOOLS_H
#define ALGORITHMS_SUPPORTED_TOOLS_H

#include <iostream>
#include <vector>

/*
 * A function to output the vector with iostream
 */

template<typename T>
std::ostream &operator<<(std::ostream &os,const std::vector<T> &V) {
    for (auto iter = V.begin(); iter != V.end(); ++iter) {
        os << *iter << ", ";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os,const std::vector<T> &&V) {
    for (auto iter = V.begin(); iter != V.end(); ++iter) {
        os << *iter << ", ";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os,const std::vector<std::vector<T>> &V) {
    for (auto iter = V.begin(); iter != V.end(); ++iter) {
        for(auto Viter = iter->begin(); Viter != iter->end(); ++Viter){
            std::cout<<*Viter<<", ";
        }
        std::cout<<"\n";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os,const std::vector<std::vector<T>> &&V) {
    for (auto iter = V.begin(); iter != V.end(); ++iter) {
        for(auto Viter = iter->begin(); Viter != iter->end(); ++Viter){
            std::cout<<*Viter<<", ";
        }
        std::cout<<"\n";
    }
    return os;
}

#endif //ALGORITHMS_SUPPORTED_TOOLS_H
