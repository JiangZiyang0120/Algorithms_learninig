//
// Created by jiang-ziyang on 22-8-2.
//

#include "../../../Include/Sort_Example_Header.h"

int main(){
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0,1);
    size_t length = 10;
    std::vector<double> A;
    A.reserve(length);
    for(size_t i = 0; i != length; ++i)
        A.push_back(u(e));
    std::cout<<"bucket Sort"<<std::endl<<"The sequence to be sorted:"<<std::endl;
    std::cout<<A<<std::endl;
    Sort S;
    S.reverseBucketSort(A,10);
    std::cout<<"The sorted sequence (in the reverse order) is as below:"<<std::endl;
    std::cout<<A<<std::endl;
    return 0;
}
