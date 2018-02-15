#include <stdlib.h> // <-- 'malloc', 'free', 'srand', 'rand' defined here
#include <stdio.h>  // <-- 'printf', 'fprintf'               defined here
#include <time.h>   // <-- 'time'                            defined here

void example1();
void example2();
void example3();

int main()
{
    // Seed the random number generator
    srand( time( NULL ) );

    example1(); // Allocating a 1D array on the heap
    example2(); // Allocating a contiguous 2D array on the heap
    example3(); // Allocating a non-contiguous 2D array on the heap

    return 0;
}

void example1()
{
    // Let's allocate a very large 1D array (of ints) on the heap
    int *arr;
    //long int arr_size = 1000000000000;
    long int arr_size = 100000;
    arr = (int *)malloc( arr_size * sizeof(arr_size) );

    // Let's double check the allocation was successful
    if (arr == NULL)
    {
        fprintf( stderr, "error: main: memory allocation of 'arr' failed\n" );
        exit(1);
    }

    // Now let's fill it with random values between 10 and 15 inclusive
    int idx;
    for (idx = 0; idx < arr_size; idx++)
    {
        arr[idx] = (rand() % 6) + 10; // Introducing '%' = "mod operator"
    }

    // Print out the first few values
    printf( "Some random integers, 10 ≤ x ≤ 15:\n  [ " );
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
    // Choose the dimensions of the 2D array
    int rows = 5;
    int cols = 8;

    // Allocate enough memory for rows * cols items
    int nitems = rows * cols;
    int *M;
    M = (int *)malloc( rows * cols * sizeof(int) );

    // Populate the array with some values
    int idx;
    for (idx = 0; idx < nitems; idx++)
    {
        M[idx] = idx;
    }

    // Print the array
    int r, c;
    printf( "M =\n" );
    for (r = 0; r < rows; r++)
    {
        printf( "[  " );
        for (c = 0; c < cols; c++)
        {
            idx = r*cols + c;
            printf( "%2d  ", M[idx] );
        }
        printf( "]\n" );
    }
    printf( "\n" );

    // Free the memory we allocated
    free( M );
}

void example3()
{
    // Choose the dimensions of the 2D array
    int rows = 5;
    int cols = 8;
    int r, c;

    // This time, each row is its own 1D array, and we keep a separate array
    // of their respective memory addresses in an array of POINTERS!
    int **M;
    M = (int **)malloc( rows * sizeof(int *) );
    for (r = 0; r < rows; r++)
    {
        M[r] = (int *)malloc( cols * sizeof(int) );
    }

    // Populate the array with some values
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {
            M[r][c] = r*r - c*c;
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

    // Free up the memory we've used
    for (r = 0; r < rows; r++)
    {
        free( M[r] );
    }
    free( M );
}
