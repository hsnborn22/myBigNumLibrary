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

bigInt * sumBigInts(bigInt * number1, bigInt * number2) {
    int carryFlag = 0;
    bigInt * result;
    result = calloc(1, sizeof(struct BIGNUM_INTEGER_STRUCT));
    short * resultDigits;
    short * temp1 = reverseArray(number1->digits, number1->digitCount);
    short * temp2 = reverseArray(number2->digits, number2->digitCount);
    if (number1->digitCount == number2->digitCount) {
        int count = number1->digitCount;
        resultDigits = calloc(1,sizeof(short) * count);
        for (int i = 1; i <= count; i++) {
            resultDigits[i - 1] = temp1[i] + temp2[i];
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
        result->digits = resultDigits;
        result->digitCount = number1->digitCount + carryFlag;
        return result;
    } else if (number1->digitCount > number2->digitCount) {
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
        result->digits = resultDigits;
        result->digitCount = number1->digitCount + carryFlag;
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
        result->digits = resultDigits;
        result->digitCount = number2->digitCount + carryFlag;
        return result;
    }
}

int main(void) {
    char string[] = "121313212131321202301213132120230913891238912312032301823018123081230121313212131321202309138912389123120323018230181230812301213132913891238912312032301823018123081230121313212023012131321202309138912389123120323018230181121313212023012131321202309138912389123120323018230181230812301213132121313212023091389123891231203230182301812308123012131329138912389123120323018230181230812301213132121313212023012131321202309138912389123120323018230181230812301213132121313212023091389123891231203230182301812308123012131329138912389123120323018230181230812301213132230812301213132121313212023091389123891231203230182301812308123012131329138912389123120323018230181230812301213132";
    char string2[] = "12131321202309138912389123120323018230181230812301213132230920120212308123123121313212023012131321202309138912389123120323018230181230812301213132121313212023091389123891231203230182301812308123012131329138912389123120323018230181230812301213132121313212023012131321202309138912389123120323018230181230812301213132121313212023091389123891231203230182301812308123012131329138912389123120323018230181230812301213132782104402416";
    bigInt * lol = initBigInt(string);
    bigInt * lol2 = initBigInt(string2);
    bigInt * result = sumBigInts(lol,lol2);
    short * temp1 = reverseArray(lol->digits, lol->digitCount);
    for (int i = 0; i < result->digitCount; i++) {
        printf("%d \n", result->digits[i]);
    }
    free(lol);
    free(lol2);
    free(result);
    free(temp1);
    return 0;
}