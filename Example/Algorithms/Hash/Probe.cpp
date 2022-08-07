//
// Created by jiang-ziyang on 22-8-7.
//

#include "../../../Algorithms/Hash.h"
#include "../../../Include/Supported_Tools.h"

#define m 2431

/*
 * Comment out the two function names you do not want tested
 */
#define function universalHashing
//#define function divisionHashing
//#define function multiplicativeHashing

int main() {
    Hash<size_t> h;
    size_t digit, i = 0;
    std::cout << "Please enter the digit" << std::endl;
    std::cin >> digit;
    for (; i != 10; ++i) {
        std::cout << "Its " << std::to_string(i + 1)
                  << ((i + 1 == 1) ? "st" : (i + 1 == 2) ? "nd" : (i + 1 == 3) ? "rd" : "th")
                  << " doubleHashing probe number is "
                  << h.doubleHashing(m, digit, i) << std::endl;
    }
    return 0;
}