#include <stdio.h>

void example1();
void example2();
void example3();
void example4();

int main( )
{
    example1(); // Basic variable types, memory addresses, and '&' operator
    //example2(); // The pointer variable type
    //example3(); // Creating 1D arrays on the stack
    //example4(); // Creating 2D arrays on the stack

    return 0;
}


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
    printf( "i: %ld byte(s) allocated at memory address %p, which contains value %d\n",  sizeof(int),    &i, i );
    printf( "f: %ld byte(s) allocated at memory address %p, which contains value %f\n",  sizeof(float),  &f, f );
    printf( "d: %ld byte(s) allocated at memory address %p, which contains value %lf\n", sizeof(double), &d, d );
    printf( "c: %ld byte(s) allocated at memory address %p, which contains value %c\n",  sizeof(char),   &c, c );
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

    // Note that char's are really just 1-byte ints, so we can also write
    printf( "c = %d\n", c );
    // ...and "Hello World!\n" as
    printf( "%c%c%c%c%c%c%c%c%c%c%c%c%c",
            72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33, 10 );
    printf( "\n" );

}


void example2()
{
    // Suppose you want to store a memory address as a variable. Use pointers!
    // int   * = pointer to an int,
    // float * = pointer to a float,
    // etc.
    int   i = 128; // Declare and initialise in one step
    int *pi = &i;  // 8 bytes of memory allocated on the stack

    printf( " i: %ld byte(s) allocated at memory address %p, contains value %d\n", sizeof(int)  , &i,  i  );
    printf( "pi: %ld byte(s) allocated at memory address %p, contains value %p\n", sizeof(int *), &pi, pi );
    printf( "\n" );
}


void example3()
{
    // Let's make some arrays!
    // There are a lots of ways to do this, each with pros and cons
    // First, 1D arrays:
    int size = 5;
    int arr1[size]; // "size" x sizeof(int) bytes of contiguous memory allocated on the stack
    int idx;
    for (idx = 0; idx < size; idx++)
    {
        arr1[idx] = idx + 1001;
    }

    // Let's see how this array is laid out in memory:
    printf( "With declaration \"int arr1[%d]\":\n", size );
    for (idx = 0; idx < size; idx++)
    {
        printf( "arr1[%d] = %d,  %ld byte(s) at memory address %p\n", idx, arr1[idx], sizeof(int), &(arr1[idx]) );
    }
    printf( "\n" );

    // A second way to declare a 1D array on the stack
    int arr2[] = { 3, 1, 4, 1, 6 };
    printf( "With declaration \"int arr2[] = {...}\":\n" );
    for (idx = 0; idx < 5; idx++)
    {
        printf( "arr2[%d] = %d,  %ld byte(s) at memory address %p\n", idx, arr2[idx], sizeof(int), &(arr2[idx]) );
    }
    printf( "\n" );

    // In both of the above cases, arr1 and arr2 are themselves actually pointers to the first element of the array:
    printf( "Proving that arr1 is the same as &arr1[0]:\n" );
    printf( "arr1 = %p = %p = &arr1[0]\n", arr1, &arr1[0] );
    printf( "arr2 = %p = %p = &arr2[0]\n", arr2, &arr2[0] );
    printf( "\n" );

    // You can do arithmetic on pointers, giving many ways to get at a value in an array.
    // Introducing * as the "dereferencing operator"
    printf( "*arr1     = %d\n", *arr1 );
    printf( "*(arr1+1) = %d\n", *(arr1+1) );
    printf( "*(arr1+2) = %d\n", *(arr1+2) );
    printf( "*(arr1+3) = %d\n", *(arr1+3) );
    printf( "*(arr1+4) = %d\n", *(arr1+4) );
}

void example4()
{
    // Creating 2D arrays, first method:
    int rows = 2;
    int cols = 3;
    double arr1[rows][cols];

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
