//
// Created by jiang-ziyang on 22-9-2.
//
#include <vector>
#include "../../Include/Supported_Tools.h"
#include <Eigen/Core>
#include <cfloat>
#include <cstdio>

class ArrayChains {
public:
    int maxChain(std::vector<int> Array) {
        size_t MatrixSize = Array.size() - 1;
        Eigen::MatrixXi times(MatrixSize, MatrixSize);
        Eigen::MatrixXi M(MatrixSize, MatrixSize);
        for (size_t i = 0; i != MatrixSize; ++i)
            times(i, i) = 0;
        int temp;
        for (size_t i = 1; i != MatrixSize; ++i) {
            for (size_t j = 0; j != MatrixSize - i; ++j) {
                temp = i + j;
                times(j, temp) = DBL_MAX;
                for (int k = j; k != temp; ++k) {
                    if(times(j, temp)>(times(j, k) + times(k + 1, temp) + Array[j] * Array[k + 1] * Array[temp + 1])){
                        times(j, temp)=times(j, k) + times(k + 1, temp) + Array[j] * Array[k + 1] * Array[temp + 1];
                        M(j,temp) = k;
                    }
                }
            }
        }
        getBracket(M,0,MatrixSize-1);
        return times(MatrixSize - 1, MatrixSize - 1);
    }

    void getBracket(Eigen::MatrixXi &M, size_t i, size_t j){
        if(i == j)
            printf("A");
        else{
            printf("(");
            getBracket(M,i,M(i,j));
            getBracket(M,M(i,j)+1,j);
            printf(")");
        }
    }
};

int main() {
    ArrayChains AC;
    std::vector<int> v = {30, 35, 15, 5, 10, 20, 25};
    AC.maxChain(v);
}