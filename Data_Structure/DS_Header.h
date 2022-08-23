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

inline std::string repeatString(size_t tier, std::string &&str) {
    std::string returnStr;
    for (size_t i = 0; i != tier; ++i)
        returnStr.insert(returnStr.end(), str.begin(), str.end());
    return std::move(returnStr);
}

#endif //MAIN_CPP_DS_HEADER_H
