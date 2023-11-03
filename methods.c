// Dependencies:
#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------

    Small num general purpose math library 
Use this only if performance is crucial and you don't care about precision
or you don't need to work with big numbers.
To work with big numbers use the bignum library.
-------------------------------------------- */

/* --------------------------------------------
              Factorial function:
Input: integer n
Output: the factorial of n, n! := n(n-1)...2*1
-------------------------------------------- */

int factorial(int n) {
    // First check if the input is a positive integer (in order for it to make sense)
    // (For negative integers we would have to use the Hadamard's pseudogamma function as our extrapolation)
    if (n > 0) {   
        // Initialize the result as 1, the multiplicative identity of the real field.
        int result = 1;
        for (int i = 1; i <= n; i++) {
            result *= i;
        }
        // Return the result
        return result;
    } else if (n == 0) {
        // Since 0! = 1
        return 1;    
    } else {
        // Input not valid
        return -1;
    }
}

/* --------------------------------------------
              Absolute value function:
Input: double x
Output: the absolute value |x| of x.
Remember |x| = x if x > 0 and |x| = -x if x < 0
-------------------------------------------- */

double abs2(double x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

/* --------------------------------------------
              The sign function:
Input: double x
Output: the sign of x, sgn(x).
Remember sgn(x) = 1 if x > 0, sgn(x) = -1 if x < 0.
sgn is often defined as sgn(x) := x/|x|
-------------------------------------------- */

double sgn(double x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        // Input not valid: in this case the sgn function is not defined.
        return 0;
    }
}

/* --------------------------------------------
              Double Factorial function:
Input: integer n
Output: the double factorial of n, n!! := n(n-2)(n-4)...
-------------------------------------------- */

int doubleFactorial(int n) {
    if (n > 0) {
        // Initialize the result as 1
        int result = 1;
        // Initialize our loop variable i as 0:
        int i = 0;
        // We will keep multiplying our result by (n-i) until n-i is 0 or less.
        while (n - i > 0) {
            result *= (n-i);
            i += 2;
        }
        return result;
    } else if (n == 0) {
        // Since 0!! = 1
        return 1;
    } else {
        // Input not valid
        return -1;
    }
}

/* --------------------------------------------
              Wilson's theorem-based primality algorithm implementation:
Input: integer n
Output: whether n is prime or not
We are using wilson's theorem here, that states:
n > 1 is prime iff (n-1)! = -1(mod n)
-------------------------------------------- */

int isPrimeWilson(int n) {
    if (n > 1) {
        int ourFactorial = factorial(n-1);
        printf("%d %d \n", ourFactorial, ourFactorial % n);
        if (ourFactorial % n == n - 1) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

/* --------------------------------------------
              Better primality algorithm:
Input: integer n
Output: whether n is prime or not
Not very fast for large n.
Time complexity: O(sqrt(n))
-------------------------------------------- */

int IsPrime(int n) {
    if (n == 2 || n == 3) {
        return 1;
    }
    if (n <= 1 || n % 2 == 0 || n % 3 == 0){
        return 0;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0){
            return 0;
        }
    }
    return 1;
}

/* --------------------------------------------
              Sieve of Eratosthenes:
Input: integer n
Output: int * , all primes up to n 
The output will be in the form of an array, containing in the first entry the length
of it (so the number of primes up to n incremented by one) and in the remaining ones
the actual list of prime numbers up to that number.
-------------------------------------------- */

int * allPrecedingPrimes(int n) {
    if (n > 1) {
        int primeCount = 1;
        int * primeNumbersList = calloc(1,sizeof(int) * primeCount);
        primeNumbersList[0] = primeCount;
        int * primality = calloc(1,sizeof(int) * (n - 1));
        for (int i = 0; i < n - 1; i++) {
            primality[i] = 1;
        }
        for (int j = 2; j * j <= n; j++) {
            if (primality[j - 2] == 1) {
                for (int k = j* j; k <= n; k += j) {
                    primality[k - 2] = 0;
                }
            }
        }
        for (int i = 0; i <= n-1; i++) {
            if (primality[i] == 1) {
                primeCount++;
                primeNumbersList = realloc(primeNumbersList, sizeof(int) * primeCount);
                primeNumbersList[0] = primeCount;
                primeNumbersList[primeCount - 1] = i + 2;
            }
        }
        free(primality);
        return primeNumbersList;
    } else {
        int result[] = {-1};
        return result;
    }
}

/* --------------------------------------------
        Find the number of preceding primes using the sieve of Erathostenes
Input: integer n
Output: integer: the number of all primes less than or equal to n.
-------------------------------------------- */

int numberOfPrecedingPrimes(int n) {
    if (n > 1) {
        int * listOfPrimes = allPrecedingPrimes(n);
        int numberOfPrimes = allPrecedingPrimes[0] -1;
        return numberOfPrimes;
    }
    else {
        return -1;
    }
}

/* --------------------------------------------
              Primorial function:
Input: integer n
Output: the primorial of n, i.e the products of all prime numbers less than or equal to n.
-------------------------------------------- */

int primorial(int n) {
    if (n > 0) { 
        // Initialize the result to 1, the multiplicative identity of R.
        int result = 1;
        // Loop through all integers bigger than 1 and less than or equal to n.
        for (int i = 1; i <= n; i++) {
            // If the integer we're looping through is prime, we multiply result by it.
            if (isPrimeWilson(n)) {
                result *= i;
            } else {
                // If not, we just go to the next iteration
            }
        }
    } else if (n == 0) {
        // Since p(0) = 1
        return 1;
    } else {
        // Input not valid
        return -1;
    }
}

int main(void) {
    int * list = allPrecedingPrimes(15);
    for (int i = 0; i < list[0]; i++) {
        printf("%d \n", list[i]);
    }
    free(list);
    return 0;
}