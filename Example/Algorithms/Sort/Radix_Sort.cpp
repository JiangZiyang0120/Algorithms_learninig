//
// Created by jiang-ziyang on 22-7-22.
//

#include "../../../Include/Sort_Example_Header.h"

void showDefiniteCountingSort(){
    std::vector<size_t> A = {3,2,6,4,7,5,4,3,1};
    countingSort(A, *std::max_element(A.begin(),A.end()));
    std::cout << A << std::endl;
}

int main(){
    showDefiniteCountingSort();
    return 0;
}