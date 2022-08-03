//
// Created by jiang-ziyang on 22-8-2.
//

#include "../../../Include/Select_Example_Header.h"
#include "../../../Include/Sort_Example_Header.h"

template <typename T>
void showMinElement(std::vector<T> &A){
    Select S;
    std::cout<<"The min element is"<<std::endl;
    std::cout<<*S.min(A.begin(),A.end())<<std::endl;
}

template <typename T>
void showMaxElement(std::vector<T> &A){
    Select S;
    std::cout<<"The max element is"<<std::endl;
    std::cout<<*S.max(A.begin(),A.end())<<std::endl;
}

template <typename T>
void showMinMaxElement(std::vector<T> &A){
    Select S;
    std::cout<<"The min and the max element are"<<std::endl;
    auto P = S.minmax(A.begin(),A.end());
    std::cout<<"min: "<<*P.first<<"\n"<<"max: "<<*P.second<< std::endl;
}

int main(){
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0,1);
    size_t length = 10;
    std::vector<double> A;
    A.reserve(length);
    for(size_t i = 0; i != length; ++i)
        A.push_back(u(e));
    std::cout<<"The sequence is as below:"<<std::endl;
    std::cout<<A<<std::endl;
    std::vector<double> B(A);
    std::cout<<"Its ordered sequence is:"<<std::endl<<Sort::quickSort(B)<<std::endl;
    showMinElement(A);
    showMaxElement(A);
    showMinMaxElement(A);
}