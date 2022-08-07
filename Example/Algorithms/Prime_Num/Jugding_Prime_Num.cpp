//
// Created by jiang-ziyang on 22-8-7.
//

#include "../../../Algorithms/Prime_Num.h"
#include "../../../Include/Supported_Tools.h"

int main() {
    std::cout << "please enter a number" << std::endl;
    largeInt digit;
    std::cin >> digit;
    std::cout << "number " << digit << (PrimeNum::isPrimeNum(digit) ? " is " : " is not ") << "a prime number."
              << std::endl;
    return 0;
}
