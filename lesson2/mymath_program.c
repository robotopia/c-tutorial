#include <stdio.h>
#include "mymath.h"

int main()
/* A demonstration of the functions written in mymath.c" */
{
    // Make some numbers
    double x = 5.0, y = 4.0;

    // Do some calculations
    double a = add(x,y);
    double s = subtract(x,y);
    double m = multiply(x,y);
    double d = divide(x,y);

    // Print out the results
    printf( "x + y = %.1lf\n", a );
    printf( "x - y = %.1lf\n", s );
    printf( "x * y = %.1lf\n", m );
    printf( "x / y = %.2lf\n", d );

    // Return success!
    return 0;
}
