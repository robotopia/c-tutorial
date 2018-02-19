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
 * This program is the canonical "hello world" program, showing the essential
 * components of a minimal C program.
 *
 *****************************************************************************/

// This is a single line comment
/* This is a multi-
                line comment.    */

// ------------------------------------------------------------------------- //

#include <stdio.h> // <-- This is where the printf() family of functions lives

/* #include <...>
 *
 * The #include directive is C's way of incorporating other people's code
 * into your own program. It is analogous to Python's "import".
 *
 * The '.h' files that are #include'd are called "header" files, and they
 * contain function (and other) definitions.
 *
 * The header file included here is part of the "C Standard Library" and
 * contains definitions and functions relating to File I/O. In this particular
 * case, we're interested in the printf() family of functions.
 */

// ------------------------------------------------------------------------- //

int main( )

/* int main( )
 *
 * This is a function definition. This one is special because the compiler will
 * look for a function named "main" to know where to start execution.
 *
 * "int" here refers to the return type of the function. It can be any valid
 * variable type, or "void" if no value is to be returned. The "main" function
 * should return an int, with a value of 0 if execution succeeds and non-zero
 * if execution fails.
 *
 * Inside the brackets go any variables passed into the function. The
 * canonical "main" function is usually defined thus:
 *
 *   int main( int argc, char *argv[] )
 *
 * where the two arguments are the number and values of the command line
 * arguments when the program was run. These will be explained later.
 *
 * The function body is enclosed within {}'s, which is C's way of treating a
 * block of code as a "unit", in a sense.
 */

{
    // Print out the canonical message to stdout
    printf( "Hello world!\n" );

    // Exit successfully
    return 0;
}
