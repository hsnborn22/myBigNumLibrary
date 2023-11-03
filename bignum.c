#include <stdio.h>
#include <stdlib.h>

// short --> 2 bytes, but we really just need 4 bits! optimize later.

/*
Define our struct for bignum integers were gonna use here.
*/

typedef struct BIGNUM_INTEGER_STRUCT {
    char * representation;
    short * digits;
    int digitCount;
} bigInt;

/* Max Method:
Input: 2 integers a and b
Output: the maximum between the 2, max(a,b)
*/

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

/* Reverse string method:
Input: a string (char *) and its length (int)
Output: The string reversed (char * )
*/

char * reverseString(char * string, int len) {
    // allocate memory for the reversed string we're gonna return
    char * newString = calloc(1, sizeof(char)* len);
    for (int i = 0; i < len; i++) {
        // reverse
        newString[len - i] = string[i];
    }
    // return the string
    return newString;
}

/* Reverse array method:
Input: an array of shorts (short *) and its length (int)
Output: The array reversed (short * )
*/

short * reverseArray(short * array, int len) {
    // allocate memory for the reversed array we're gonna return
    short * newArray = calloc(1, sizeof(short)* len);
    // the reversing is done here
    for (int i = 0; i < len; i++) {
        newArray[len - i] = array[i];
    }
    // return the array
    return newArray;
}

short * actualReverse(short * array, int len) {
    short * newArray = calloc(1,sizeof(short) * len);
    for (int i = 1; i <= len;i++) {
        newArray[len - i] = array[i-1];
    }
    return newArray;
}

/* initBigInt method:
Input: a number represented as a string.
Output: The bigInt * object representing it.
It works similarly to how a constructor would work in OOP languages like Java. 
*/

bigInt * initBigInt(char * numberString) {
    int length = 1;
    char * outputRepresentation = calloc(1, sizeof(char)*length);
    int digitCount = 1;
    short * digits;
    bigInt * outputBigInt = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
    digits = calloc(1, sizeof(short) * digitCount);
    // "   1290123128123    "
    int i = 0;
    if (numberString[i] == ' ') {
        i++;
        while (numberString[i] == ' ') {
            i++;
        }
    }
    while (numberString[i] >= 48 && numberString[i] <= 57) {
        char currentChar = numberString[i] - 48;
        short currentDigit = (short)currentChar;
        digits[digitCount - 1] = currentDigit;
        digitCount++;
        digits = realloc(digits, sizeof(short) * digitCount);
        outputRepresentation[length - 1] = numberString[i];
        length++;
        outputRepresentation = realloc(outputRepresentation, sizeof(char) * length);
        i++;
    }
    outputBigInt->digitCount = digitCount - 1;
    short * newDigits = calloc(1, sizeof(short)* (digitCount-1));
    for (int j = 0; j < digitCount - 1; j++) {
        newDigits[j] = digits[j];
    }
    outputBigInt->digits = newDigits;
    outputBigInt->representation = outputRepresentation;
    return outputBigInt;
}

/*
                    sumBigInts method:
Input: 2 bigInt pointers
Output: 1 bigInt pointer (the result of the addition)
It outputs the result of the addition of two ordinary big ints. The algorithm employed is
the classic digit-wise addition algorithm we are all familiar with. 
*/

bigInt * sumBigInts(bigInt * number1, bigInt * number2) {
    // Init the carry flag to 0; it will be used to check if the number of digits
    // will be increased during the addition.
    int carryFlag = 0;
    // Initialize the return value of bigInt type and allocate space for it with calloc.
    bigInt * result;
    result = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
    // Initialize the array of short ints that will represent the digits of our return value
    short * resultDigits;
    /* Initialize the reversed arrays of the digits of the 2 initial numbers (bigInt numbers)
        We do this in order to start from  the smallest digit and go up to the largest one.
        If we didnt do this we would go the other way around.
    */ 
    short * temp1 = reverseArray(number1->digits, number1->digitCount);
    short * temp2 = reverseArray(number2->digits, number2->digitCount);
    // Initialize our representation string
    char * outputRepresentation;
    // Some if-else clauses:
    // First case: we are summing two numbers with the same number of digits
    if (number1->digitCount == number2->digitCount) {
        // Initialize the variable count; it doesn't matter if we initialize it to be equal to
        // number1->digitCount or number2->digitCount since we're supposing they are the same.
        int count = number1->digitCount;
        // Allocate bytes for it using calloc
        resultDigits = calloc(1,sizeof(short) * count);
        // We now loop through the digits and performing the digit-wise summing algorithm we are all familiar with.
        for (int i = 1; i <= count; i++) {
            // We place the sum of the digits at index i of the reversed digit lists for number1 and number2 
            // in the (i-1)th index of the resultDigits array.
            resultDigits[i - 1] = temp1[i] + temp2[i];
            // We now check if it is bigger than or equal to 10: if that is the case we implement the carry logic. 
            if (resultDigits[i-1] >= 10) {
                if (i == count) {
                    resultDigits = realloc(resultDigits, sizeof(short)* (count + 1));
                    resultDigits[count] = 1;
                    resultDigits[count - 1] %= 10; 
                    carryFlag = 1;
                }
                else {
                    resultDigits[i-1] %= 10;
                    int j = 0;
                    H:
                    j++;
                    temp1[i + j] += 1;
                    if (temp1[i+j] >= 10) {
                        temp1[i+j] %= 10;
                        goto H;
                    }
                }
                
            }
        }
        // We know reverse back the result to keep it consistent.
        short * actualDigits = actualReverse(resultDigits, number1->digitCount + carryFlag);
        // We place the object properties that we desire
        result->digits = actualDigits;
        result->digitCount = number1->digitCount + carryFlag;
        // We now calculate the string representation of our bignum.
        // (I wanna remove this extra loop someday)
        outputRepresentation = calloc(1, sizeof(char) * (result->digitCount));
        for (int i = 0; i < result->digitCount; i++) {
            outputRepresentation[i] = (char)(result->digits[i]) + 48;
        }
        result->representation = outputRepresentation;
        // We now return the result of our bigInt addition.  
        return result;
    } else if (number1->digitCount > number2->digitCount) {
        // case #2: number1 has more digits than number2
        // Most of the logic is the same: for this reason I will only comment the different parts.
        int count = number2->digitCount;
        int thisDigit = number1->digits[0];
        resultDigits = calloc(1,sizeof(short)* (number1->digitCount));
        for (int i = 1; i <= count; i++) {
            resultDigits[i - 1] = temp1[i] + temp2[i];
            if (resultDigits[i-1] >= 10) {
                resultDigits[i-1] %= 10;
                int j = 0;
                L:
                j++;
                temp1[i + j] += 1;
                if (temp1[i+j] >= 10 && i + j != number1->digitCount) {
                    temp1[i+j] %= 10;
                    goto L;
                } else if (temp1[i+j] >= 10 && i + j == number1->digitCount) {
                    thisDigit = temp1[i+j] % 10;
                    carryFlag = 1;
                    temp1[i+j] %= 10;
                    temp1[i + j + 1] = 1;
                }
            }
        }
        for (int i = count; i < number1->digitCount - 1 ;i++) {
            resultDigits[i] = temp1[i+1];
        }
        if (carryFlag == 0) {
            resultDigits[number1->digitCount - 1] = thisDigit;
        } else {
            resultDigits[number1->digitCount -1] = thisDigit;
            resultDigits = realloc(resultDigits, sizeof(short)* (count + 1));
            resultDigits[number1->digitCount] = 1;
        }
        short * actualDigits = actualReverse(resultDigits, number1->digitCount + carryFlag);
        result->digits = actualDigits;
        result->digitCount = number1->digitCount + carryFlag;
        // We now calculate the string representation of our bignum.
        // (I wanna remove this extra loop someday)
        outputRepresentation = calloc(1, sizeof(char) * (result->digitCount));
        for (int i = 0; i < result->digitCount; i++) {
            outputRepresentation[i] = (char)(result->digits[i]) + 48;
        }
        result->representation = outputRepresentation;
        return result;
    } else {
        int count = number1->digitCount;
        int thisDigit = number2->digits[0];
        resultDigits = calloc(1,sizeof(short)* (number2->digitCount));
        for (int i = 1; i <= count; i++) {
            resultDigits[i - 1] = temp1[i] + temp2[i];
            if (resultDigits[i-1] >= 10) {
                resultDigits[i-1] %= 10;
                int j = 0;
                case3loop:
                j++;
                temp2[i + j] += 1;
                if (temp2[i+j] >= 10 && i + j != number2->digitCount) {
                    temp2[i+j] %= 10;
                    goto case3loop;
                } else if (temp2[i+j] >= 10 && i + j == number2->digitCount) {
                    thisDigit = temp2[i+j] % 10;
                    carryFlag = 1;
                    temp2[i+j] %= 10;
                    temp2[i + j + 1] = 1;
                }
            }
        }
        for (int i = count; i < number2->digitCount - 1;i++) {
            resultDigits[i] = temp2[i+1];
        }
        if (carryFlag == 0) {
            resultDigits[number2->digitCount - 1] = thisDigit;
        } else {
            resultDigits[number2->digitCount -1] = thisDigit;
            resultDigits = realloc(resultDigits, sizeof(short)* (count + 1));
            resultDigits[number2->digitCount ] = 1;
        }
        short * actualDigits = actualReverse(resultDigits, number2->digitCount + carryFlag);
        result->digits = actualDigits;
        result->digitCount = number2->digitCount + carryFlag;
        // We now calculate the string representation of our bignum.
        // (I wanna remove this extra loop someday)
        outputRepresentation = calloc(1, sizeof(char) * (result->digitCount));
        for (int i = 0; i < result->digitCount; i++) {
            outputRepresentation[i] = (char)(result->digits[i]) + 48;
        }
        result->representation = outputRepresentation;
        return result;
    }
}

int main(void) {
    char string[] = "546";
    char string2[] = "341";
    bigInt * lol = initBigInt(string);
    bigInt * lol2 = initBigInt(string2);
    bigInt * result = sumBigInts(lol,lol2);
    short * temp1 = actualReverse(result->digits, result->digitCount);
    for (int i = 0; i < result->digitCount; i++) {
        printf("%d \n", result->digits[i]);
    }
    for (int i = 0; i< lol->digitCount; i++) {
        printf("%d \n", lol->digits[i]);
    }
    free(lol);
    free(lol2);
    free(result);
    free(temp1);
    return 0;
}