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
 * This program illustrates the relationship between C variables and memory.
 * It also introduces pointers in a hopefully accessible way.
 *
 *****************************************************************************/

// Like in hello_world.c, this program uses the printf() family of functions,
// so we need to include stdio.h.
#include <stdio.h>

/* Here are function prototypes used in this code. A function prototype serves
   to tell the C compiler the name, return type, and parameter types of a
   function. This lets me write code that uses these functions without having
   to define their behaviour straight away. In this example, I have defined
   the four example functions below the main function. Without these proto-
   types here, the compiler would have first encountered, say, example1() in
   the main function, and complained with "warning: implicit declaration
   of function". However, if I moved the main function to the end of this file
   (and therefore after the definitions of the example functions), everything
   would work as expected.
*/

void example1();
void example2();
void example3();
void example4();

// (A little helper function for drawing some ASCII art)
void draw_connector( int left, int right );

// The main function. Execution starts here
int main( )
{
    /* I've divided up the code in this source file into four "example"
       functions. These can be commented and uncommented at will, but will
       obviously need to be recompiled with every change. (This is why having
       a Makefile comes in so handy, since all you have to remember is 'make')
    */

    //example1(); // Basic variable types, memory addresses, and '&' operator

    //example2(); // The pointer variable type

    //example3(); // Creating 1D arrays on the stack

    example4(); // Creating 2D arrays on the stack

    return 0;
}

/* Stack vs heap:
  
   The C compiler makes a distinction between "stack" memory and "heap"
   memory. In fact, there is no physical difference between these two memory
   types, but they are handled differently by the compiler. For the purposes
   of this tutorial, all we need to know for now is that "stack" memory is
   managed by the compiler, whereas "heap" memory must be managed by the
   programmer. Unless using a specific function for managing heap memory,
   all default behaviour (e.g. when you declare a variable) occurs on the
   stack.
*/

void example1()
{
    // Basic variable types
    int    i; // 4 bytes of memory allocated on the stack (compiler dependent)
    float  f; // 4 bytes of memory allocated on the stack (compiler dependent)
    double d; // 8 bytes of memory allocated on the stack (compiler dependent)
    char   c; // 1 byte  of memory allocated on the stack ("kind of" standard)

    // Let's see what values happen to be at those memory addresses
    // at the moment...
    // We will use the '&' operator, which means "address of"
    printf( "Before initialisation...\n" );

    printf( "i: %ld byte(s) allocated at memory address %p, which contains "
            "value %d\n",  sizeof(int),    &i, i );
    printf( "f: %ld byte(s) allocated at memory address %p, which contains "
            "value %f\n",  sizeof(float),  &f, f );
    printf( "d: %ld byte(s) allocated at memory address %p, which contains "
            "value %lf\n", sizeof(double), &d, d );
    printf( "c: %ld byte(s) allocated at memory address %p, which contains "
            "value %c\n",  sizeof(char),   &c, c );
    printf( "\n" );

    // Change the values at these memory addresses
    i = -10;
    f = 2.3456e3;
    d = 7.6544e3;
    c = 'a';

    // ... and now let's check that it worked:
    printf( "After initialisation...\n" );

    printf( "i: memory address %p now contains %d\n",  &i, i );
    printf( "f: memory address %p now contains %f\n",  &f, f );
    printf( "d: memory address %p now contains %lf\n", &d, d );
    printf( "c: memory address %p now contains %c\n",  &c, c );
    printf( "\n" );

    // And just for fun...
    // Note that char's are really just 1-byte ints, so we can also write
    printf( "c = %d\n", c );
    // ...and "Hello World!\n" as
    printf( "%c%c%c%c%c%c%c%c%c%c%c%c%c",
            72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33, 10 );
    printf( "\n" );

}


void example2()
{
    /* Suppose you want to store a memory address as a variable. Use pointers!
       A pointer is simply a type (just like int or double), whose value is
       itself a memory address. C requires that you specify what variable type
       is located at the target memory address, e.g.
      
       int   * = pointer to an int,
       float * = pointer to a float.
    */

    int   i = 128; // Declare and initialise in one step
    int *pi = &i;  // 8 bytes of memory allocated on the stack

    printf( "  i: %ld byte(s) allocated at memory address %p, contains value "
            "%d\n", sizeof(int)  , &i,  i  );

    draw_connector( 50, 75 );

    printf(  " pi: %ld byte(s) allocated at memory address %p, contains value "
            "%p\n", sizeof(int *), &pi, pi );

    // And since a pointer is itself a valid variable type, you can even make
    // a pointer that points to a pointer!
    int **ppi = &pi;

    draw_connector( 50, 75 );

    printf( "ppi: %ld byte(s) allocated at memory address %p, contains value "
            "%p\n", sizeof(int **), &ppi, ppi );

    printf( "\n" );

    // So now we have a "chain" of pointers:  int ** --> int * --> int
}


void example3()
{
    // Let's make some 1D arrays!
    // There are a few ways to do this, each with pros and cons
    int size = 5;
    int arr1[size]; /* "size times sizeof(int)" bytes of contiguous memory
                       allocated on the stack */

    // Let's put some values in the array
    int idx;
    for (idx = 0; idx < size; idx++)
    {
        arr1[idx] = idx + 1001;
    }

    // Let's see how this array is laid out in memory:
    printf( "With declaration \"int arr1[%d]\":\n", size );
    for (idx = 0; idx < size; idx++)
    {
        printf( "arr1[%d] = %d,  %ld byte(s) at memory address %p\n",
                idx, arr1[idx], sizeof(int), &(arr1[idx]) );
    }
    printf( "\n" );

    // A second way to declare a 1D array on the stack
    int arr2[] = { 3, 1, 4, 1, 6 };
    printf( "With declaration \"int arr2[] = {...}\":\n" );
    for (idx = 0; idx < 5; idx++)
    {
        printf( "arr2[%d] = %d,  %ld byte(s) at memory address %p\n",
                idx, arr2[idx], sizeof(int), &(arr2[idx]) );
    }
    printf( "\n" );

    // In both of the above cases, arr1 and arr2 are themselves actually
    // pointers to the first element of the array:
    printf( "Proving that arr1 is the same as &arr1[0]:\n" );
    printf( "arr1 = %p = %p = &arr1[0]\n", arr1, &arr1[0] );
    printf( "arr2 = %p = %p = &arr2[0]\n", arr2, &arr2[0] );
    printf( "\n" );

    /* Introducing * as the "dereferencing operator": if you have a pointer
       named p, then *p refers to the thing pointed to. For example, if
      
       int  i = 5;
       int *p = &i;
      
       Then the following are equivalent:
      
       int j = i + 1;
       int k = *p + 1;
      
       You can think of the deferencing operator as the inverse of the
       address-of operator: the former tells you what's at a memory address,
       while the latter tells you what memory address a thing is at.
    */

    // Since the values of an array are placed in contiguous locations we can
    // also use "pointer arithmetic to access the elements of the array:
    printf( "*arr1     = %d\n", *arr1 );
    printf( "*(arr1+1) = %d\n", *(arr1+1) );
    printf( "*(arr1+2) = %d\n", *(arr1+2) );
    printf( "*(arr1+3) = %d\n", *(arr1+3) );
    printf( "*(arr1+4) = %d\n", *(arr1+4) );

    /* In fact, the square bracket notation is really just syntactic sugar for
       pointer arrithmetic. That is:
      
         arr[2] is really *(arr+2)
    */
}

void example4()
{
    // Creating 2D arrays, first method:
    int rows = 2;
    int cols = 3;
    double arr1[rows][cols];

    /*       ^----^----^------ This method of declaring arrays still uses
       stack memory, and also ensures that the are all contiguous in memory,
       with row number moving the "slowest" (different from Fortran).
      
       In memory, a 2x3 array still looks like this:
       +-------+-------+-------+-------+-------+-------+
       |   0   |   1   |   2   |   3   |   4   |   5   |
       +-------+-------+-------+-------+-------+-------+
      
       but you can access it like this:
       +-------+-------+-------+-------+-------+-------+
       | r0,c0 | r0,c1 | r0,c2 | r1,c0 | r1,c1 | r1,c2 |
       +-------+-------+-------+-------+-------+-------+

       or, in other words:
       +--------+--------+--------+--------+--------+--------+
       | [0][0] | [0][1] | [0][2] | [1][0] | [1][1] | [1][2] |
       +--------+--------+--------+--------+--------+--------+

    */

    // Populate the array with some values
    int r, c;
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {
            arr1[r][c] = 0.5 * (double)(r+1) * (double)(c+1);
        }
    }

    // Print out arr1
    printf( "arr1 =\n" );
    for (r = 0; r < rows; r++)
    {
        printf( "[  " );
        for (c = 0; c < cols; c++)
        {
            printf( "%.3f  ", arr1[r][c] );
        }
        printf( "]\n" );
    }

    // Second method:
    // This is a direct analogue to the 1D case, but notice that you have to
    // now use nested brackets.
    double arr2[][3] = { {0.0, 0.2, -0.4}, {3.14, -0.5, 1.0} };

    // Print out arr2
    printf( "arr2 =\n" );
    for (r = 0; r < 2; r++)
    {
        printf( "[  " );
        for (c = 0; c < 3; c++)
        {
            printf( "%.3f  ", arr2[r][c] );
        }
        printf( "]\n" );
    }

}



void draw_connector( int left, int right )
{
    int i;
    for (i = 0; i < left      ; i++)
        printf(" ");                   // Line 1: spaces
    printf("\\\n");                    //         '\' + newline
    for (i = 0; i < left+1    ; i++) 
        printf(" ");                   // Line 2: spaces
    for (i = 0; i < right-left; i++)  
        printf("-");                   //         dashes
    printf("\n");                      //         newline
    for (i = 0; i < right+1   ; i++)  
        printf(" ");                   // Line 3: spaces
    printf("\\\n");                    //         '\' + newline
}
