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
 * This program produces a segfault, by design, by addressing memory addresses
 * that haven't been allocated, or which are disallowed.
 *
 *****************************************************************************/

//#include <stdlib.h>
#include <stdio.h>

int main()
{
    // Let's make a pointer and initialise it to NULL (=0)
    int *ptr = NULL;

    // And now let's try and see what's at that memory address.
    // Memory address 0 is forbidden!
    int i = *ptr;
    printf( "The value %d is at memory address %p\n", i, ptr );

    // Return success!
    return 0;
}
