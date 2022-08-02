//
// Created by jiang-ziyang on 22-7-22.
//

#include "../../../Include/Sort_Example_Header.h"

void showCountingSort(){
    std::vector<size_t> A = {3,2,6,4,7,5,4,3,1};
    Sort S;
    S.countingSort(A, *std::max_element(A.begin(),A.end()));
    std::cout << A << std::endl;
}

size_t T2size_t(int a){
    return static_cast<size_t>(a+3);
}

void showT2size_t(){
    std::vector<int> A = {3,2,5,-3,1,5,-2};
    Sort S;
    S.countingSort(A,10,T2size_t);
    std::cout<<A<<std::endl;
}

int main(){
    showCountingSort();
    showT2size_t();
    return 0;
}