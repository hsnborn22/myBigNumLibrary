typedef struct BIGNUM_INTEGER_STRUCT {
    char * representation;
    short * digits;
    int digitCount;
    int signFlag;
} bigInt;

int max(int a, int b);

int checkIfAllZeros(char * string, int length);

char * removeUnnecessaryZeros(char * string, int length);

char * reverseString(char * string, int len);

short * reverseArray(short * array, int len);

short * actualReverse(short * array, int len);

bigInt * initBigInt(char * numberString);

char * removeMinus(char * string, int length);

char * addMinus(char * string, int length);

bigInt * negateBigInt(bigInt * number);

bigInt * subtractBigInts(bigInt * number1, bigInt * number2);
bigInt * sumBigInts(bigInt * number1, bigInt * number2);

int bigIntIsEqualTo(bigInt * number1, bigInt * number2);
int bigIntLessThan(bigInt * number1, bigInt * number2);
int bigIntIsNequalTo(bigInt * number1, bigInt * number2);
void bigIntCopyInto(bigInt * number1, bigInt * number2);
int bigIntGreaterThan(bigInt * number1, bigInt * number2);

bigInt * bigIntCopy(bigInt * number);
int bigIntLessEqThan(bigInt * number1, bigInt * number2);
int bigIntBiggerEqThan(bigInt * number1, bigInt * number2);
int bigIntIsNegative(bigInt * number);
int bigIntIsPositive(bigInt * number);
int intSgn(bigInt * number);
bigInt * bigIntSgn(bigInt * number);
bigInt * bigIntMax(bigInt * number1, bigInt * number2);
bigInt * bigIntMin(bigInt * number1, bigInt * number2);
bigInt * classicMultiply(bigInt* number1, bigInt* number2);
char * concatenate(char * string1, char * string2, int len1, int len2);
bigInt * increaseDecimalBy(bigInt * number, int n);