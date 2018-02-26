/*****************************************************************************
 * C Mini-tutorial
 * ---------------
 *
 * Sam McSweeney, 2018
 *
 * This is a mini tutorial aimed primarily at scientists who are familiar with
 * a programming language already (usually Python), and who want to understand
 * the C language and syntax a bit better.
 *
 * This program is designed to demonstrate how to keep your code in several
 * different source files and how to link them together when compiling. It's
 * function is trivial: it takes two numbers, and performs +,-,*,/ on them
 * using custom-made functions defined in mymath.c.
 *
 *****************************************************************************/

#include <stdio.h>

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
