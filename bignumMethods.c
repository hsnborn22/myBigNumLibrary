#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bignum.h"

bigInt * subtractor(bigInt * value) {
    bigInt * zero = initBigInt("0");
    bigInt * one = initBigInt("1");
    while (bigIntIsNequalTo(value, zero)) {
        value = subtractBigInts(value, one);
    }
    return value;
}

// Factorial algorithm for bignums written using the classic multiplication algorithm. 
// It's pretty slow :(

bigInt * classicFactorial(bigInt * value) {
    // Initialize the bigInt * zero variable, equal to the additive identity 0 in bignum format
    bigInt * zero = initBigInt("0");
    // Initialize the bigInt * variable result, that will be returned by the function
    // We also allocate the space for it with calloc
    bigInt * result = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
    // We check that the bigInt value is greater than or equal to zero: the classic discrete factorial
    // is in fact not defined for negative integers, and not even the gamma function extrapolation is 
    // (since they are singularities in that case).We would have to use the hadamard pseudogamma extrapolation
    // to give meaning to those values, but here we're working with integers, so we will just return -1.
    if (bigIntGreaterThan(value, zero)) {
        // Initialize the result to 1.
        result = initBigInt("1");
        // Initialize the variable 1, that we will use to decrement the bigInt.
        bigInt * one = initBigInt("1");
        while (bigIntIsNequalTo(value, zero)) {
            result = classicMultiply(result, value);
            value = subtractBigInts(value, one);
        }
        result->representation = removeUnnecessaryZeros(result->representation, strlen(result->representation));
    } else if (bigIntIsEqualTo(value, zero)) {
        result = initBigInt("1");
        return result;
    } else {
        result = initBigInt("-1");
    }
    return result;
}

int main(void) {
    bigInt * abc = initBigInt("22");
    bigInt * abc2 = initBigInt("123405");
    bigInt * abc3 = splitBigIntHigh(abc2, 2);
    printf("%s \n", abc3->representation);
    free(abc);
    free(abc3);
    return 0;
}