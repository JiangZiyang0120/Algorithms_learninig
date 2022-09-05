//
// Created by jiang-ziyang on 22-9-2.
//
#include <vector>
#include "../../Include/Supported_Tools.h"

class SteelCutting {
public:
    explicit SteelCutting(std::vector<std::pair<size_t, double>> &P) : profit(P), optimalProfit(), optimalLength() {}

    void getSolution(size_t length){
        if(length > optimalProfit.size())
            calculateOptimalProfit(length);
        std::cout<<"The optimal profit is "<<optimalProfit[length]<<std::endl;
        std::cout<<"The optimal cutting length is :";
        for(size_t l = length; l != 0;){
            std::cout<<" "<<optimalLength[l]<<",";
            l -= optimalLength[l];
        }
        std::cout<<std::endl;
    }

private:
    void calculateOptimalProfit(size_t length) {
        size_t originSize = optimalProfit.size();
        optimalProfit.resize(length+1);
        optimalLength.resize(length+1);
        optimalProfit[0] = 0;
        optimalLength[0] = 0;
        for (size_t i = originSize; i != length + 1; ++i) {
                for (auto iter = profit.begin(); iter != profit.end() && iter->first <= i; ++iter) {
                    if (optimalProfit[i] < optimalProfit[i - iter->first] + iter->second) {
                        optimalProfit[i] = optimalProfit[i - iter->first] + iter->second;
                        optimalLength[i] = iter->first;
                    }
            }
        }
    }

private:
    std::vector<double> optimalProfit;
    std::vector<std::pair<size_t, double>> profit;
    std::vector<size_t> optimalLength;
};

int main() {
    std::vector<std::pair<size_t, double>> profit = {
            {1,  1},
            {2,  5},
            {3,  8},
            {4,  9},
            {5,  10},
            {6,  17},
            {7,  17},
            {8,  20},
            {9,  24},
            {10, 30}
    };
    SteelCutting S(profit);
    S.getSolution(25);
    S.getSolution(27);
    S.getSolution(10);
}