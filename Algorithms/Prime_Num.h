//
// Created by jiang-ziyang on 22-8-7.
//

#ifndef MAIN_CPP_PRIME_NUM_H
#define MAIN_CPP_PRIME_NUM_H

#include "Algo_Header.h"

typedef long long largeInt;
#define MIN_LIMIT 3221225472
#define MAX_LIMIT 4294967296
#define DIGIT_BOUNDARY 100000000

namespace algo_learning {
    const largeInt primeNum[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
}

class PrimeNum {
public:
    static bool isPrimeNum(largeInt);

    static bool circularlyJudged(largeInt);

    static bool millerRabin(largeInt);

    static largeInt getPrimeNum(largeInt min = MIN_LIMIT, largeInt max = MAX_LIMIT);

private:
    static largeInt mod_mul(largeInt, largeInt, largeInt);

    static largeInt mod_pow(largeInt, largeInt, largeInt);
};

bool PrimeNum::isPrimeNum(largeInt num) {
    return ((num > DIGIT_BOUNDARY) ? millerRabin(num) : circularlyJudged(num));
}

bool PrimeNum::circularlyJudged(largeInt num) {
    if (num == 1 || num == 4)
        return false;
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    size_t tmp = static_cast<size_t>(sqrt(static_cast<double >(num)));
    for (size_t i = 5; i <= tmp; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

bool PrimeNum::millerRabin(largeInt x) {
    largeInt i, j, k;
    largeInt s = 0, t = x - 1;
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false;
    while (!(t & 1)) //divide x-1 into type like (2^s)
    {
        s++;
        t >>= 1;
    }
    for (i = 0; i < 10 && algo_learning::primeNum[i] < x; i++) //select a prime number and test
    {
        largeInt a = algo_learning::primeNum[i];
        largeInt b = mod_pow(a, t, x);   //calculate a^t
        for (j = 1; j <= s; j++) //and execute s times square operating
        {
            k = mod_mul(b, b, x);  //calculate square of b
            if (k == 1 && b != 1 && b != x - 1)
                return false;
            b = k;
        }
        if (b != 1) return false;    //judging by Fermat's little theorem
    }
    return true;
}

largeInt PrimeNum::getPrimeNum(largeInt min, largeInt max) {
    std::default_random_engine e(time(0));
    std::uniform_int_distribution<unsigned> u(min, max);
    largeInt temp = u(e), digit = (temp % 2) ? temp : temp + 1;
    auto functionPinter = digit > DIGIT_BOUNDARY ? millerRabin : circularlyJudged;
    while (!functionPinter(digit))
        digit += 2;
    return digit;
}

largeInt PrimeNum::mod_mul(largeInt a, largeInt b, largeInt mod) {
    largeInt res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

largeInt PrimeNum::mod_pow(largeInt a, largeInt n, largeInt mod) {
    largeInt res = 1;
    while (n) {
        if (n & 1)
            res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        n >>= 1;
    }
    return res;
}

#endif //MAIN_CPP_PRIME_NUM_H
