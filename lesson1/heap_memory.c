#include <stdlib.h> // <-- 'malloc', 'free', 'srand', 'rand' defined here
#include <stdio.h>  // <-- 'printf', 'fprintf'               defined here
#include <time.h>   // <-- 'time'                            defined here

int main( )
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
    // First, seed the random number generator:
    srand( time( NULL ) );
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

    // Freeing the memory we've allocated
    free( arr );

    return 0;
}
