//
// Created by jiang-ziyang on 22-7-17.
//

#ifndef ALGORITHMS_SUPPORTED_TOOLS_H
#define ALGORITHMS_SUPPORTED_TOOLS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Core>

/*
 * A function to output the vector with iostream
 */

template <typename T>
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


template <class TreeClass>
void printTree(std::ofstream &ofs, std::string &fileName,TreeClass &TC){
    if(ofs)
        ofs.close();
    ofs.open(fileName);
    ofs<<TC<<std::endl;
    ofs.close();
    system("pytm-cli -i data.json -t 1 -d TB");
    system("firefox ./TreeMap.html");
}

template <class TreeClass>
void printTree(TreeClass &TC){
    std::string fileName = "data.json";
    std::ofstream ofs;
    printTree(ofs,fileName,TC);
}


template <typename T, int row, int col>
std::ostream &operator<<(std::ostream &os, Eigen::Matrix<T,row,col> &M){
    size_t rowNum = M.rows(),colNum = M.cols();
    for (size_t i = 0; i != rowNum; ++i) {
        for (size_t j = 0; j != colNum; ++j) {
            os.width(10);
            os << M(i, j);
        }
        os << "\n";
    }
    return os;
}
#endif //ALGORITHMS_SUPPORTED_TOOLS_H
