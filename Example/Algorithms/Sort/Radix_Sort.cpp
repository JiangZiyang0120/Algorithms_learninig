//
// Created by jiang-ziyang on 22-7-30.
//

#include "../../../Include/Sort_Example_Header.h"

int main(){
    std::vector<std::vector<size_t>> A = {
            {9,3,6},
            {2,4,1},
            {5,2,5}
    };
    Sort S;
    S.radixSort(A,0,2,10);
    std::cout<<A<<std::endl;
}