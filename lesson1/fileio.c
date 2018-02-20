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
 * This program generates a 100x100 matrix, populates it with values,
 * and writes it out to two files: one in binary and one in ascii.
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Below are "preprocessor macros". The first stage of the compiler is the
   preprocessing stage, in which these macros are expanded in the rest of the
   code. That is, MAX_STR_LENGTH, wherever it occurs, is replaced by 1024,
   etc. In fact, the above #include statements are also preprocessor direct-
   ives, which literally import the contents of the named files into the
   code.
*/

#define MAX_STR_LENGTH 1024

#define BINARY 1
#define ASCII  2

// Some function prototypes
void usage();

double **create_matrix( int, int );
void destroy_matrix( double **, int );

void make_ripples( double **, int, int );

void write_matrix( FILE *, double **, int, int, int );

int main( int argc, char *argv[] )
{
    // Make sure the user has supplied at least one argument on
    // the command line
    if (argc < 2)
    {
        usage();
        exit(EXIT_FAILURE);
    }

    // Get the supplied basename from the first argument and turn it into
    // two distinct filenames
    char binfile[MAX_STR_LENGTH];
    char txtfile[MAX_STR_LENGTH];

    sprintf( binfile, "%s.bin", argv[1] );
    sprintf( txtfile, "%s.txt", argv[1] );

    // Open two files for writing
    FILE *f_bin = fopen( binfile, "w" );
    FILE *f_txt = fopen( txtfile, "w" );

    // Allocate memory for a 100x100 matrix
    int rows = 100, cols = 100;
    double **M = create_matrix( rows, cols );

    // Populate the matrix array with some values
    make_ripples( M, rows, cols );

    // Write out the matrix to the two files
    write_matrix( f_bin, M, rows, cols, BINARY );
    write_matrix( f_txt, M, rows, cols, ASCII );

    // Close the files
    fclose( f_bin );
    fclose( f_txt );

    // Free memory for matrix
    destroy_matrix( M, rows );

    return EXIT_SUCCESS;
}


void usage()
{
    printf( "usage: fileio [basename]\n\n" );
    printf( "This program will write out matrix data to two files:\n" );
    printf( "  [basename].bin  and  [basename].txt,\n" );
    printf( "in binary and ascii formats, respectively.\n" );
}

double **create_matrix( int rows, int cols )
{
    // Allocate memory for a matrix with the requested size
    double **M;
    M = (double **)malloc( rows * sizeof(double *) );

    // Allocate memory for each row
    int r;
    for (r = 0; r < rows; r++)
    {
        M[r] = (double *)malloc( cols * sizeof(double) );
    }

    return M;
}


void destroy_matrix( double **M, int rows )
{
    // Free memory for each row
    int r;
    for (r = 0; r < rows; r++)
    {
        free( M[r] );
    }

    // Free the top-level allocation
    free( M );
}


void make_ripples( double **M, int rows, int cols )
{
    // This will populate matrix element r,c with the values
    // between 0.0 and 1.0 such that they form a pattern of
    // concentric ripples spreading out from the centre of
    // the array.

    // First, find the centre of the array
    int xc = cols / 2; // <-- Integer division!!
    int yc = rows / 2;

    // Some variables to help calculate the ripples
    double dist; // i.e. distance from centre
    double ripple_size = (rows < cols ? rows / 6.0 : cols / 6.0);
    // C-style ternary operator! -----^------------^
    // (COND ? X : Y) is shorthand for
    // if (COND is true), use value X, otherwise use Y

    // Now, iterate through the array elements
    int r, c;    // to iterate through (r)ows and (c)olumns, respectively
    for (r = 0; r < rows; r++)
    for (c = 0; c < cols; c++)
    {
        // In the following, "hypot", "cos", and "M_PI" are all from math.h
        dist = hypot( c-xc, r-yc );
        M[r][c] = cos( 2.0 * M_PI * dist / ripple_size );
    }
}

void write_matrix( FILE *f, double **M, int rows, int cols, int write_type )
{
    int r, c;
    switch (write_type) // an syntactic alternative to  if...elseif...elseif...
    {
        case BINARY:
            for (r = 0; r < rows; r++)
                fwrite( M[r], sizeof(double), cols, f );
            break;
        case ASCII:
            for (r = 0; r < rows; r++)
            {
                for (c = 0; c < cols; c++)
                    fprintf( f, "%e ", M[r][c] );
                fprintf( f, "\n" );
            }
            break;
        default:
            // Any other write_type is not recognised
            fprintf( stderr, "error: write_matrix: unrecognised write_type "
                             "(=%d)\n", write_type );
            exit(EXIT_FAILURE);
    }
}
