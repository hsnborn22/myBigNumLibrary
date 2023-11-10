#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// short --> 2 bytes, but we really just need 4 bits! optimize later.

/*
Define our struct for bignum integers were gonna use here.
*/

typedef struct BIGNUM_INTEGER_STRUCT {
    char * representation;
    short * digits;
    int digitCount;
    int signFlag;
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

// This function checks if a string is comprised of only zeros

int checkIfAllZeros(char * string, int length) {
    int nonZeroFlag = 1;
    for (int i = 0; i < length; i++) {
        if (string[i] > 48 && string[i] <= 57) {
            nonZeroFlag = 0;
        } else {
            // Do nothing
        }
    }
    return nonZeroFlag;
}

/* Remove unnecessary zero method:
Input: a string representation of a bigInt
output: a string representation of the same bigInt without the unnecessary 0s. 
*/

char * removeUnnecessaryZeros(char * string, int length) {
    if (checkIfAllZeros(string, length)) {
        char * result = calloc(1, sizeof(char));
        result[0] = '0';
        return result;
    } else {
        int newStringLength = 0;
        char * newString;
        newString = calloc(1,sizeof(char));
        if (string[0] == '0') {
            int index;
            for (int j = 1; j < length; j++) {
                if (string[j] == '0') {
                    // skip
                } else {
                    // save the index where the string of 'unnecessary' zeros end
                    index = j;
                    break;
                }
            }
            for (int i = index; i < length; i++) {
                newStringLength++;
                newString = realloc(newString,sizeof(char)*newStringLength);
                newString[i - index] = string[i];
            }
            return newString;
        } else if (string[0] == '-') {
            newString[0] = '-';
            if (string[1] == '0') {
                int index;
                for (int j = 2; j < length; j++) {
                    if (string[j] == '0') {
                        // skip
                    } else {
                        // save the index where the string of 'unnecessary' zeros end
                        index = j;
                        break;
                    }
                }
                for (int i = index; i < length; i++) {
                    newStringLength++;
                    newString = realloc(newString,sizeof(char)*newStringLength);
                    newString[i - index+1] = string[i];
                }
                return newString;
            } else {
                return string;
            }
        } else {
            return string;
        }
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
    int negativeFlag;
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
    if (numberString[i] == '-') {
        negativeFlag = 1;
        outputRepresentation[0] = '-';
        length++;
        outputRepresentation = realloc(outputRepresentation, sizeof(char) * length);
        i++;
    } else {
        negativeFlag = 0;
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
    outputBigInt->representation = removeUnnecessaryZeros(outputRepresentation, outputBigInt->digitCount);
    outputBigInt->signFlag = negativeFlag;
    return outputBigInt;
}
/*removeMinus function:
input: char * string and its length (integer)
output: another string without the minus at the beginning*/

char * removeMinus(char * string, int length) {
    if (string[0] == '-') {
        int newLength = length - 1;
        char * newString = calloc(1,sizeof(char)*newLength);
        for (int i = 1; i <= length + 1; i++) {
            newString[i - 1] = string[i];
        }
        return newString;
    } else {
        return string;
    }
}

/* addMinus method:
input: char * (string) and its length (integer)
output: a string with a - in the beginning.
*/

char * addMinus(char * string, int length) {
    if (string[0] != '-' && checkIfAllZeros(string,length) == 0) {
        int newLength = length + 1;
        char * newString = calloc(1,sizeof(char) * newLength);
        newString[0] = '-';
        for (int i = 0; i < length; i++) {
            newString[i+1] = string[i];
        }
        return newString;
    } else {
        return string;
    }
}

/* negateBigInt method: 
returns the input bigInt with the opposite sign
*/

bigInt * negateBigInt(bigInt * number) {
    bigInt * result = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
    // Negate the sign with signFlag
    result->signFlag = number->signFlag ? 0 : 1;
    result->representation = number->signFlag ? removeMinus(number->representation, number->digitCount - 1) : addMinus(number->representation, number->digitCount);
    result->digits = number->digits;
    result->digitCount = number->digitCount;
    return result;
}

/*
                    sumBigInts method:
Input: 2 bigInt pointers
Output: 1 bigInt pointer (the result of the addition)
It outputs the result of the addition of two ordinary big ints. The algorithm employed is
the classic digit-wise addition algorithm we are all familiar with. 
*/

// declare the subtractBigInts function because we'll need it in the sumBigInts function.

bigInt * subtractBigInts(bigInt * number1, bigInt * number2);

bigInt * sumBigInts(bigInt * number1, bigInt * number2) {
    if (number1->signFlag == 0 && number2->signFlag == 0) {
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
    } else if (number1->signFlag == 0 && number2->signFlag == 1) {
        // Initialize a temporary variable temp2, storing the same digits as number2
        // but with positive sign.
        bigInt * temp2 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp2->digitCount = number2->digitCount;
        temp2->signFlag = 0;
        temp2->digits = number2->digits;
        // We then calculate number1 - temp2 = number1 - |number2| 
        bigInt * result = subtractBigInts(number1,temp2);
        return result;
    } else if (number1->signFlag == 1 && number2->signFlag == 0) {
        // Initialize a temporary variable temp1, storing the same digits as number1
        // but with positive sign.
        bigInt * temp1 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp1->digitCount = number1->digitCount;
        temp1->signFlag = 0;
        temp1->digits = number1->digits;
        bigInt * result = subtractBigInts(number2,temp1);
        return result;
    } else {
        // Initialize two temporary variables, temp1 and temp2 storing
        // the same digits as number1 and number2, but with positive sign.
        bigInt * temp1 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp1->digitCount = number1->digitCount;
        temp1->signFlag = 0;
        temp1->digits = number1->digits;
        bigInt * temp2 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp2->digitCount = number2->digitCount;
        temp2->signFlag = 0;
        temp2->digits = number2->digits;
        // Sum them
        bigInt * negatedResult = sumBigInts(temp1,temp2);
        // Negate the result:
        bigInt * result = negateBigInt(negatedResult);
        return result;
    }
}

/* Function to determine whether two bigInts are equal*/

int bigIntIsEqualTo(bigInt * number1, bigInt * number2) {
    if (strcmp(number1->representation, number2->representation) == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Function to determine whether two bigInts are not equal

int bigIntIsNequalTo(bigInt * number1, bigInt * number2) {
    return bigIntIsEqualTo(number1,number2) ? 0: 1;
}

int bigIntLessThan(bigInt * number1, bigInt * number2);

/* Function to determine whether a bigInt is greater than another bigInt*/

int bigIntGreaterThan(bigInt * number1, bigInt * number2) {
    if (number1->signFlag == 0 && number2->signFlag == 0) {
        if (number1->digitCount > number2->digitCount) {
            return 1;
        } else if (number1->digitCount < number2->digitCount) {
            return 0;
        } else {
            if (number1->digits[0] == number2->digits[0]) {
                int j = 0;
                while (number1->digits[j] == number2->digits[j] && j < number1->digitCount) {
                    j++;
                }
                if (j == number1->digitCount) {
                    return 0;
                } else {
                    if (number1->digits[j] > number2->digits[j]) {
                        return 1;
                    } else if (number1->digits[j] < number2->digits[j]) {
                        return 0;
                    }
                }
            } else if (number1->digits[0] > number2->digits[0]) {
                return 1;
            } else {
                return 0;
            }
        }
    } else if (number1->signFlag == 1 && number2->signFlag == 0) {
        return 0;
    } else if (number1->signFlag == 0 && number2->signFlag == 1) {
        return 1;
    } else {
        bigInt * temp1 = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
        bigInt * temp2 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp1->signFlag = 0;
        temp2->signFlag = 0;
        temp1->digits = number1->digits;
        temp2->digits = number2->digits;
        temp1->digitCount = number1->digitCount;
        temp2->digitCount = number2->digitCount;
        int abc = bigIntLessThan(temp1,temp2);
        return abc;
    }
}

/* Function to determine whether a bigInt is smaller than another bigInt*/

int bigIntLessThan(bigInt * number1, bigInt * number2) {
    if (number1->signFlag == 0 && number2->signFlag == 0) {
        if (number1->digitCount > number2->digitCount) {
            return 0;
        } else if (number1->digitCount < number2->digitCount) {
            return 1;
        } else {
            if (number1->digits[0] == number2->digits[0]) {
                int j = 0;
                while (number1->digits[j] == number2->digits[j] && j < number1->digitCount) {
                    j++;
                }
                if (j == number1->digitCount) {
                    return 0;
                } else {
                    if (number1->digits[j] > number2->digits[j]) {
                        return 0;
                    } else if (number1->digits[j] < number2->digits[j]) {
                        return 1;
                    }
                }
            } else if (number1->digits[0] > number2->digits[0]) {
                return 0;
            } else {
                return 1;
            }
        }
    } else if (number1->signFlag == 0 && number2->signFlag == 1) {
        return 0;
    } else if (number1->signFlag == 1 && number2->signFlag == 0) {
        return 1;
    } else {
        bigInt * temp1 = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
        bigInt * temp2 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp1->signFlag = 0;
        temp2->signFlag = 0;
        temp1->digits = number1->digits;
        temp2->digits = number2->digits;
        temp1->digitCount = number1->digitCount;
        temp2->digitCount = number2->digitCount;
        int abc = bigIntGreaterThan(temp1,temp2);
        return abc;
    }
}

/* bigIntCopyInto function:
input 1: (bigInt * pointer type) the bigInt to copy
input 2: (bigInt * pointer type) the bigInt we're copying the first bigInt to
*/

void bigIntCopyInto(bigInt * number1, bigInt * number2) {
    // copy all attributes of number 1 into number2:
    number2->representation = number1->representation;
    number2->signFlag = number1->signFlag;
    number2->digitCount = number1->digitCount;
    number2->digits = number1->digits;
}

// bigIntCopy function (this time we're not copying a big int into another)
// but rather we're returning a copy of a bigInt

bigInt * bigIntCopy(bigInt * number) {
    bigInt * result = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
    result->digits = number->digits;
    result->representation = number->representation;
    result->signFlag = number->signFlag;
    result->digitCount = number->digitCount;
    return result;
}

/* Function to determine whether a bigInt is less than or equal to another bigInt */

int bigIntLessEqThan(bigInt * number1, bigInt * number2) {
    if (bigIntLessThan(number1,number2) || bigIntIsEqualTo(number1,number2)) {
        return 1;
    } else {
        return 0;
    }
}

/* Function to determine whether a bigInt is greater than or equal to another bigInt */

int bigIntBiggerEqThan(bigInt * number1, bigInt * number2) {
    if (bigIntGreaterThan(number1,number2) || bigIntIsEqualTo(number1,number2)) {
        return 1;
    } else {
        return 0;
    }
}

/* bigIntIsNegative function
returns 1 if a bigInt is negative, returns 0 if a bigInt is positive.
*/

int bigIntIsNegative(bigInt * number) {
    return number->signFlag;
}

/* bigIntIsPositive function
returns 0 if a bigInt is negative, returns 1 if a bigInt is positive.
*/

int bigIntIsPositive(bigInt * number) {
    switch(number->signFlag) {
        case 1:
            return 0;
            break;
        case 0:
            return 1;
            break;
        default:
            return -1;
            break;
    }
}

/* intSgn function:
Returns the sign of a bigInt in the format of a standard int.
*/

int intSgn(bigInt * number) {
    if (bigIntIsPositive(number)) {
        return 1;
    } else {
        return -1;
    }
}

/* bigIntSgn function:
Returns the sign of a bigInt in the format of a bigInt 
(it might often ome in handy to want the sign of a number directly in the bigInt format to use it
in calculations directly).
*/

bigInt * bigIntSgn(bigInt * number) {
    if (bigIntIsPositive(number)) {
        bigInt * output = initBigInt("1");
        return output;
    } else {
        bigInt * output = initBigInt("-1");
        return output;
    }
}

/* Function max:
input: 2 bigInt pointers, number1 and number2
output: another bigInt pointer.
Returns the bigger between the two big ints.
*/

bigInt * bigIntMax(bigInt * number1, bigInt * number2) {
    if (bigIntBiggerEqThan(number1,number2)) {
        return number1;
    } else {
        return number2;
    }
}

/* Function max:
input: 2 bigInt pointers, number1 and number2
output: another bigInt pointer.
Returns the smaller between the two big ints.
*/

bigInt * bigIntMin(bigInt * number1, bigInt * number2) {
    if (bigIntLessEqThan(number1,number2)) {
        return number1;
    } else {
        return number2;
    }
}

/* subtractBigInts function:
input: 2 big ints number1 and number2 
output: the difference between the two, number1 - number2 
*/

bigInt * subtractBigInts(bigInt * number1, bigInt * number2) {
    // Initialize the carry flag
    int carryFlag = 0;
    int negativeFlag;
    // Initialize the bigInt we're going to return (the output)
    bigInt * result = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
    short * resultDigits;
    char * outputRepresentation;
    // Reverse the digit lists for the inputs
    short * temp1 = actualReverse(number1->digits, number1->digitCount);
    short * temp2 = actualReverse(number2->digits, number2->digitCount);

    // some if-else case checking
    // case #1: the number of digits of the first number is the same as the second
    if (number1->signFlag == 0 && number2->signFlag == 0) {
        if (number1->digitCount == number2->digitCount) {
            if (bigIntBiggerEqThan(number1,number2)) {
                int count = number1->digitCount;
                // Allocate space for our resultDigits output bigInt.
                resultDigits = calloc(1, sizeof(short) * count);
                // Loop through the digits:
                for (int i = 0; i < count; i++) {
                    // Place the difference of temp1[i] and temp2[i] in resultDigits[i], i.e
                    // the difference between the ith digits of the 1st and 2nd number.
                    resultDigits[i] = temp1[i] - temp2[i];
                    // Implement the carry logic:
                    // We check if the ith element of the resultDigits array is less than zero:
                    // if that is the case, we will borrow one from the next digit (on the left).
                    if (resultDigits[i] < 0) {
                        resultDigits[i] += 10;
                        int j = 0;
                        temp1[i+1] -= 1;

                    }
                }
                // Check if the subtraction reduced the number of digits by one.
                if (resultDigits[count - 1] == 0) {
                    carryFlag = -1;
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
                result->representation = removeUnnecessaryZeros(outputRepresentation, result->digitCount);
                // We now return the result of our bigInt addition.  
                return result;
            } else {
                int count = number1->digitCount;
                // Allocate space for our resultDigits output bigInt.
                resultDigits = calloc(1, sizeof(short) * count);
                // Loop through the digits:
                for (int i = 0; i < count; i++) {
                    // Place the difference of temp1[i] and temp2[i] in resultDigits[i], i.e
                    // the difference between the ith digits of the 1st and 2nd number.
                    resultDigits[i] = temp1[i] - temp2[i];
                    // Implement the carry logic:
                    // We check if the ith element of the resultDigits array is less than zero:
                    // if that is the case, we will borrow one from the next digit (on the left).
                    if (resultDigits[i] < 0) {
                        resultDigits[i] += 10;
                        int j = 0;
                        temp1[i + 1] -= 1;
                    }
                }
                // Check if the subtraction reduced the number of digits by one.
                if (resultDigits[count - 1] == 0) {
                    carryFlag = -1;
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
                result->representation = removeUnnecessaryZeros(outputRepresentation, result->digitCount);
                // We now return the result of our bigInt addition.  
                char * aidBigIntString = calloc(1, sizeof(char)* (number1->digitCount + 1));
                aidBigIntString[0] = '1';
                for (int j = 1; j <= number1->digitCount; j++) {
                    aidBigIntString[j] = '0';
                }
                bigInt * aidBigInt = initBigInt(aidBigIntString);
                bigInt * actualOutput = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
                actualOutput = subtractBigInts(aidBigInt, result);
                return negateBigInt(actualOutput);
            }
        } else if (number1->digitCount > number2->digitCount) {
            int count = number2->digitCount;
            // Allocate space for our resultDigits output bigInt.
            resultDigits = calloc(1, sizeof(short) * number1->digitCount);
            // Loop through the digits:
            for (int i = 0; i < count; i++) {
                // Place the difference of temp1[i] and temp2[i] in resultDigits[i], i.e
                // the difference between the ith digits of the 1st and 2nd number.
                resultDigits[i] = temp1[i] - temp2[i];
                // Implement the carry logic:
                // We check if the ith element of the resultDigits array is less than zero:
                // if that is the case, we will borrow one from the next digit (on the left).
                if (resultDigits[i] < 0) {
                    resultDigits[i] = (resultDigits[i] % 10) + 10;
                    int j = 0;
                    subtractionIterationLabel2:
                    j++;
                    temp1[i + j] -= 1;
                    if (temp1[i+j] < 0) {
                        temp1[i+j] = (temp1[i+j]%10) + 10;
                        goto subtractionIterationLabel2;
                    }
                }
            }
            for (int i = count; i < number1->digitCount; i++) {
                resultDigits[i] = temp1[i];
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
            result->representation = removeUnnecessaryZeros(outputRepresentation, result->digitCount);
            // We now return the result of our bigInt addition.  
            return result;
        } else {
            // Handle the case in which the number of digits of number2 is bigger than the one of number1
            return negateBigInt(subtractBigInts(number2,number1));
        }
    } else if (number1->signFlag == 1 && number2->signFlag == 0) {
        bigInt * temp1 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp1->digitCount = number1->digitCount;
        temp1->signFlag = 0;
        temp1->digits = number1->digits;
        bigInt * resultIntermediate = sumBigInts(temp1, number2);
        bigInt * result2 = negateBigInt(resultIntermediate);
        return result2;
    } else if (number1->signFlag == 0 && number2->signFlag == 1) {
        bigInt * temp2 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp2->digitCount = number2->digitCount;
        temp2->signFlag = 0;
        temp2->digits = number2->digits;
        bigInt * result2 = sumBigInts(number1,temp2);
        return result2;
    } else {
        bigInt * temp1 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp1->digitCount = number1->digitCount;
        temp1->signFlag = 0;
        temp1->digits = number1->digits;
        bigInt * temp2 = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp2->digitCount = number2->digitCount;
        temp2->signFlag = 0;
        temp2->digits = number2->digits;
        bigInt * result2 = subtractBigInts(temp2,temp1);
        return result2;
    }
}

/*
Multiplication via classical algorithm 
time complexity: O(n^2)
*/

bigInt * classicMultiply(bigInt* number1, bigInt* number2) {
    int len1 = number1->digitCount;
    int len2 = number2->digitCount;
    if (number1->signFlag == number2->signFlag) {
        bigInt * output = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
        short * num1 = number1->digits;
        short * num2 = number2->digits;
        // Allocate memory for the result and initialize it to 0
        int resultLen = len1 + len2;
        short * result = calloc(1,sizeof(short)*resultLen);
        for (int i = 0; i < resultLen; i++) {
            result[i] = 0;
        }

        // Perform multiplication
        for (int i = 0; i < len1; i++) {
            int carry = 0;
            for (int j = 0; j < len2; j++) {
                int product = num1[len1 - 1 - i] * num2[len2 - 1 - j] + result[i + j] + carry;
                result[i + j] = product % 10; // Store the units place
                carry = product / 10;          // Update the carry
            }
            result[i + len2] = carry;
        }
        // We need to reverse the digits to keep it consistent with the others.
        short * actualDigits = actualReverse(result, resultLen);
        output->digits = actualDigits;
        output->signFlag = 0;
        output->digitCount = resultLen;
        char * outputRepresentation = calloc(1, sizeof(char) * (output->digitCount));
        for (int i = 0; i < output->digitCount; i++) {
            outputRepresentation[i] = (char)(output->digits[i]) + 48;
        }
        output->representation = outputRepresentation;
    } else if (number1->signFlag == 1 && number2->signFlag == 0) {
        bigInt * temp1 = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp1->digits = number1->digits;
        temp1->signFlag = 0;
        temp1->digitCount = number1->digitCount; 
        bigInt * temporaryRes = classicMultiply(temp1,number2);
        return negateBigInt(temporaryRes);
    } else {
        bigInt * temp2 = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
        temp2->digits = number2->digits;
        temp2->signFlag = 0;
        temp2->digitCount = number2->digitCount; 
        bigInt * temporaryRes = classicMultiply(number1,temp2);
        return negateBigInt(temporaryRes);
    }
}

bigInt ** splitBigInt(bigInt * number, int index) {
    bigInt * leftInt = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
    bigInt * rightInt = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
    rightInt->digitCount = number->digitCount - index;
    leftInt->digitCount = number->digitCount - index; 
    rightInt->signFlag = 0;
    leftInt->signFlag = 0;
    char * repr1 = calloc(1,sizeof(char) * (number->digitCount - index));
    char * repr2 = calloc(1,sizeof(char) * (number->digitCount - index));
    short * digits1 = calloc(1,sizeof(short) * (number->digitCount - index));
    short * digits2 = calloc(1,sizeof(short) * (number->digitCount - index));
    for (int i = 0; i < number->digitCount - index; i++) {
        digits1[i] = number->digits[i];
        digits2[i] = number->digits[index + i];
        repr1[i] = (char)(digits1[i]) + 48;
        repr2[i] = (char)(digits2[i]) + 48;
    }
    short * actualDigits1 = actualReverse(digits1, number->digitCount - index);
    short * actualDigits2 = actualReverse(digits2, number->digitCount - index);
    leftInt->digits = actualDigits1;
    rightInt->digits = actualDigits2;
    leftInt->representation = repr1; 
    rightInt->representation = repr2;
    bigInt ** output = malloc(2* sizeof(struct BIGNUM_INTEGER_STRUCT *));
    printf("%s : %s \n", leftInt->representation, rightInt->representation);
    output[0] = leftInt;
    output[1] = rightInt; 
    return output;
}

char * concatenate(char * string1, char * string2, int len1, int len2) {
    char * output = calloc(1,sizeof(char) * (len1 + len2));
    for (int i = 0; i < len1; i++) {
        output[i] = string1[i];
    }
    for (int i = 0; i < len2; i++) {
        output[i + len1] = string2[i];
    }
    return output;
}

/* Increase decimal places by n method
(it is equivalent to multiplying by 10^n but considerably faster)
*/

bigInt * increaseDecimalBy(bigInt * number, int n) {
    if (n == 0) {
        return number; 
    } else if (n > 0) {
        bigInt * output = calloc(1,sizeof(struct BIGNUM_INTEGER_STRUCT));
        char * zeroStrings = calloc(1,sizeof(char) * n);
        short * zeroArray = calloc(1,sizeof(short)*n);
        for (int i = 0; i < n; i++) {
            zeroStrings[i] = '0';
            zeroArray[i] = 0;
        }
        char * temp = concatenate(number->representation, zeroStrings, number->digitCount + number->signFlag, n);
        output->representation = temp;
        short * total = malloc((number->digitCount + n) * sizeof(short)); 
        memcpy(total,number->digits, (number->digitCount) * sizeof(short)); 
        memcpy(total + number->digitCount, zeroArray, n * sizeof(short));
        output->digits = total;
        return output;
    } else {
        return initBigInt("0");
    }
}

/* Multiplication via Karatsuba's algorithm
Time complexity: O(n^1.59) (approx.)
*/

bigInt * karatsuba(bigInt * number1, bigInt * number2) {
    if (number1->signFlag == 0 && number2->signFlag == 0) {
        if (number1->digitCount == 1 || number2->digitCount == 1) {
            return classicMultiply(number1,number2);
        }

        // Calculate the max of the sizes of the two bigInt numbers we got as an input
        int m = max(number1->digitCount, number2->digitCount);
        // This is the index where we will perform the splitting
        int splitIndex = m / 2;

        // bigInt * z0 = karatsuba(&low1,&low2);
        // bigInt * z1 = karatsuba(sumBigInts(&low1,&high1), sumBigInts(&low2,&high2));
        // bigInt * z2 = karatsuba(&high1, &high2);

        return number1;
    }   
}

/* Multiplication via fast fourier transform (FFT)
(this will be the "official" one used in the library)
Time complexity: O(n log(n))
*/
