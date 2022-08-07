//
// Created by jiang-ziyang on 22-8-7.
//

#include "../../../Algorithms/Prime_Num.h"
#include "../../../Include/Supported_Tools.h"

int main() {
    std::cout << "please enter the range of your envisaged prime number(like \"700 1000\")" << std::endl;
    largeInt min, max;
    std::cin >> min >> max;
    std::cout << "We get a prime number " << PrimeNum::getPrimeNum(min, max) << " successfully!" << std::endl;
    return 0;
}