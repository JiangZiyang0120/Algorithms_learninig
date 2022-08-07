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

int main(){
    Hash<size_t> h;
    size_t digit;
    for(;;){
        std::cout<<"Please enter the digit"<<std::endl;
        std::cin>>digit;
        std::cout<<"Its hash number is "<<h.function(m,digit)<<std::endl;
    }
    return 0;
}