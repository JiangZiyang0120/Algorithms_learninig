//
// Created by jiang-ziyang on 22-8-3.
//

#include "../../../Include/Select_Example_Header.h"
#include "../../../Include/Sort_Example_Header.h"

int main() {
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0, 1);
    size_t length = 10;
    std::vector<double> A;
    A.reserve(length);
    for (size_t i = 0; i != length; ++i)
        A.push_back(u(e));
    std::cout << "The sequence is as below:" << std::endl;
    std::cout << A << std::endl;
    std::vector<double> B(A);
    std::cout << "The sorted sequence is:"<<std::endl<<Sort::quickSort(B)<<std::endl;
    std::cout << "Which sort rank element do you want to know?" << std::endl
              << "Please Enter a number between 1 and " << A.size() << std::endl;
    size_t quantile;
    std::cin >> quantile;
    std::string s = std::to_string(quantile);
    s += (1 == quantile)? "st" : (2 == quantile) ? "rd" : "st";
    auto iter = Select::select(A.begin(),A.end(),quantile);
    std::cout<< "The "<<s<<" element is " << *iter<<std::endl;
}