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
 * This program illustrates dynamic allocation of heap memory.
 *
 *****************************************************************************/

#include <stdlib.h> // <-- 'malloc', 'free', 'srand', 'rand' defined here
#include <stdio.h>  // <-- 'printf', 'fprintf'               defined here
#include <time.h>   // <-- 'time'                            defined here

void example1();
void example2();
void example3();

/* In this program, we will be using the heap memory, which must be "curated"
   by the programmer. This means that every time you allocate any memory for
   use, you must remember to free it later. Failing to do so will result in
   "memory leaks", which means that your program can potentially continue
   consuming (i.e. allocating) memory you run out!

   The two most basic, important functions you will learn here for memory
   management are:

     1) malloc() -- allocates memory
     2) free()   -- frees memory that you've allocated

   These two functions are found in stdlib.h.
*/

int main()
{
    // Seed the random number generator
    srand( time( NULL ) );

    example1(); // Allocating a 1D array on the heap

    //example2(); // Allocating a contiguous 2D array on the heap

    //example3(); // Allocating a non-contiguous 2D array on the heap

    return 0;
}

void example1()
{
    // Let's allocate a very large 1D array (of ints) on the heap

    long int arr_size = 100000;

    /* After you've gone through this example, and understand how malloc,
       works, just for fun, change the size of the array to something huge,
       by uncommenting the following line, and see what happens when you
       compile and run it. Notice that no error was generated except the
       one that we specifically wrote for just this situation. The lesson
       is: don't assume that everything that fails will have built-in error
       reporting.
    */

    //arr_size = 1000000000000;

    /* Here we meet our first instance of malloc. The function definition is:

         void *malloc( size_t size );

       Notice that it returns a "void *", which is a pointer to an unsepcified
       type. It is up to the programmer to typecast the result into the
       desired pointer type (in this case, a pointer to an int).

       The size_t type is defined in stdlib.h to be an unsigned integer type.
       The size it wants is the number of bytes, NOT the number of elements in
       the array. It is customary to obtain the number of bytes by multing the
       number of elements with the "number of bytes per element", which can
       be obtained using the sizeof() macro.
    */

    int *arr = (int *)malloc( arr_size * sizeof(int) );

    /* Let's double check the allocation was successful.
       If it wasn't, malloc will return a "null pointer", which is a pointer
       with a memory address of zero. This memory address is always out of
       bounds for the user to access, so trying to dereference a null pointer
       will result in a segmentation fault.
    */
    if (arr == NULL)
    {
        fprintf( stderr, "error: example1: memory allocation of 'arr' failed\n" );
        exit(1);
    }

    // Now let's fill it with random values between 10 and 15 inclusive
    int idx;
    for (idx = 0; idx < arr_size; idx++)
    {
        arr[idx] = (rand() % 6) + 10; // Introducing '%' = "mod operator"
    }

    // Print out the first few values
    printf( "Some random integers, 10 <= x <= 15:\n  [ " );
    for (idx = 0; idx < 5; idx++)
    {
        printf( "%d, ", arr[idx] );
    }
    printf( "... ]\n\n" );

    // Free the memory we've allocated
    free( arr );
}

void example2()
{
    /* In this example, we'll be allocating memory for a 5x8 array on ints,
       but we'll be implementing it as a 1D, 40-element array. We'll be
       responsible for doing the pointer arithmetic ourselves.
    */

    // Choose the dimensions of the 2D array
    int rows = 5;
    int cols = 8;

    // Allocate enough memory for rows * cols items
    int nitems = rows * cols;
    int *M = (int *)malloc( nitems * sizeof(int) );

    // Populate the array with some values (just the numbers 0-39)
    int idx;
    for (idx = 0; idx < nitems; idx++)
    {
        M[idx] = idx;
    }

    // Print the array, implementing the split into "rows" ourselves
    int r, c;
    printf( "M =\n" );
    for (r = 0; r < rows; r++)            // Loop over the rows
    {
        printf( "[  " );
        for (c = 0; c < cols; c++)        // Loop over the cols
        {
            idx = r*cols + c;             // Calc the 1D index from 2D coords
            printf( "%2d  ", M[idx] );    // Print out the element
        }
        printf( "]\n" );
    }
    printf( "\n" );

    // Free the memory we allocated
    free( M );
}

void example3()
{
    /* In this example, we'll be allocating memory for a 5x8 array of ints,
       implementing it as five distinct 1D arrays of 8 elements each. We will
       also maintain a separate array (of 5 elements, one for each row) whose
       elements are the pointers to the beginning of each row.

       row0:
       +-------+-------+-------+-------+-------+-------+--
       |   0   |   1   |   2   |   3   |   4   |   5   | ...
       +-------+-------+-------+-------+-------+-------+--

       row1:
       +-------+-------+-------+-------+-------+-------+--
       |   0   |   1   |   2   |   3   |   4   |   5   | ...
       +-------+-------+-------+-------+-------+-------+--

       row2:
       +-------+-------+-------+-------+-------+-------+--
       |   0   |   1   |   2   |   3   |   4   |   5   | ...
       +-------+-------+-------+-------+-------+-------+--

       row3:
       +-------+-------+-------+-------+-------+-------+--
       |   0   |   1   |   2   |   3   |   4   |   5   | ...
       +-------+-------+-------+-------+-------+-------+--

       row4:
       +-------+-------+-------+-------+-------+-------+--
       |   0   |   1   |   2   |   3   |   4   |   5   | ...
       +-------+-------+-------+-------+-------+-------+--

       And one array to rule them all:
       +-------+-------+-------+-------+-------+
       | &row0 | &row1 | &row2 | &row3 | &row4 |
       +-------+-------+-------+-------+-------+
           |       |
           +-------+-- These elements are of type (int *), but this array
                       itself is of type (int **).

       Note the biggest difference between this method and the previous
       methods: the rows are in general NOT contiguous in memory.
    */

    // Choose the dimensions of the 2D array
    int rows = 5;
    int cols = 8;
    int r, c; // I'll use these for the for-loop counters

    // Each row is its own 1D array, and we keep a separate array
    // of their respective memory addresses in an array of POINTERS!

    int **M;  /* <--- This is the master array of pointers.
                      Notice how we call malloc, making sure each element
                      gets sizeof(int *) bytes.
              */

    M = (int **)malloc( rows * sizeof(int *) );

    /* And now, for each element of the master array, allocate memory for each
       of the five rows. Notice that there is no requirement here that the
       rows all have the same number of elements. Implementing non-rectangular
       matrices is, in this method, not really any harder than implementing
       rectangular ones.

       IMPORTANT:

       Notice that you can still use the [] notation to access elements of the
       array. Because this is programmer-managed heap memory, however, C will
       not keep track of the number of bytes allocated, and will not issue any
       warnings if you try to access a memory address outside of your alloc-
       ates array. For example, if I were to write

          M[rows+100] = NULL;

       I would not get any compiler errors or warnings (by default, but we
       have ways of making it talk), and you would get undefined behaviour
       (which often comes in the form of a segmentation fault).
    */
    for (r = 0; r < rows; r++)
    {
        M[r] = (int *)malloc( cols * sizeof(int) );
    }

    // Populate the array with some values
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {
            M[r][c] = r*r - c*c;  // <-- Just me being creative ;-)
        }
    }

    // Print out the array
    printf( "M =\n" );
    for (r = 0; r < rows; r++)
    {
        printf( "[  " );
        for (c = 0; c < cols; c++)
        {
            printf( "%3d  ", M[r][c] );
        }
        printf( "]\n" );
    }
    printf( "\n" );

    /* Free up the memory we've used. This takes a little careful thought,
       because if we free the memory of the master array first, we'll lose
       access to the pointers to each row, so we have to loop through the
       master array first and free each row separately. Only afterwards
       can we safely free the master array.

       IMPORTANT:

       The rule of thumb is: for each malloc() there should be a corre-
       sponding free().
    */

    for (r = 0; r < rows; r++)
    {
        free( M[r] );
    }
    free( M );

    /* Epilogue: It should be realised that this is perfectly generalisable to
       an arbitrary number of dimensions. It may be intimidating if you're not
       used to them, but pointers to pointers to pointers to pointers ... are
       perfectly legitimate.
    */
}
