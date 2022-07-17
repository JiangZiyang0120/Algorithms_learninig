//
// Created by jiang-ziyang on 22-7-17.
//

#ifndef ALGORITHMS_SUPPORTED_TOOLS_H
#define ALGORITHMS_SUPPORTED_TOOLS_H

#include <vector>
#include <iostream>

/*
 * A function to output the vector with iostream
 */
#define MAX_EXHIBIT_NUM 10

template<typename T>
std::ostream &operator<<(std::ostream &os,const std::vector<T> &V) {
    size_t i = 0;
    for (auto iter = V.begin(); iter != V.end(); ++iter) {
        os << *iter << ", ";
        if (++i == MAX_EXHIBIT_NUM) {
            os << std::endl;
            i = 0;
        }
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os,const std::vector<T> &&V) {
    size_t i = 0;
    for (auto iter = V.begin(); iter != V.end(); ++iter) {
        os << *iter << ", ";
        if (++i == MAX_EXHIBIT_NUM) {
            os << std::endl;
            i = 0;
        }
    }
    return os;
}

#endif //ALGORITHMS_SUPPORTED_TOOLS_H
