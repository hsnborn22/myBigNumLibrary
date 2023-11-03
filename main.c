#include <stdio.h>
#include <math.h>

// Insert expression for function you want to approximate here

double function(double x) {
    double value = pow(x,4);
    return value;
}

double midpointRule(double start, double end, int precision) {
    /* We're integrating our function over [start,end].
    We split it into n (n = precision) sub-intervals of length d
    */
    double d = (end - start)/((double)precision);
    // Initialize the result of our integral approximation
    double result = 0;
    for (int i = 0; i < precision; i++) {
        double startSubInterval = start + (d * i);
        double endSubInterval = start + (d * (i+1));
        double midPoint = (startSubInterval + endSubInterval) / ((double)2);
        double funcMidPointValue = function(midPoint);
        result += funcMidPointValue * d;
    }
    return result;
}

double trapezoidalRule(double start, double end, int precision) {
    // We're integrating over [start,end]. We split it into n (n = precision) sub-intervals of length d
    // Initialize the result of our integral approximation.
    double result = 0;
    double d = (end - start)/((double) precision);
    for (int i = 0; i <= precision; i++) {
        double y = start + (d * i);
        double functionValue = function(y);
        if (i == 0 || i == precision) {
            result += functionValue;
        } else {
            result += (2*functionValue);
        }
    }
    // return the result
    result *= (d/((double)2));
    return result;
}

int main(void) {
    // sps we want to return /int_0^5 f(x)dx -> trapezoidalRule(f(x),0,5,precision)
    double value = trapezoidalRule(1,2,10);
    printf("%lf\n", value);
    return 0;
}