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
 * This program demostrates preprocessor directives, and how they might be
 * used to
 *   1) turn on a debugging option for code under active development,
 *   2) maintain version numbers,
 *   3) write code for different computer architectures
 *
 *****************************************************************************/

#include <stdio.h>  /* <-- We've met these many times now. This preprocessor
                           directive imports the contents of the named file
                           into this file. */
#include <stdlib.h>
#include "version.h"


/* There are two new things here: the "enum" statement, and the "typedef"
   statement.
  
   The enum statement is a short way to associate tokens with integers, not
   entirely unlike a simple Python dictionary. You don't have to set numbers
   to each token explicitly, but I wanted to do it in this example because I
   wanted to make sure that the numbers match the menu item numbers.
  
   The typedef statement is a way of abbreviating your code. Its syntax is
      typedef [something complicated, like a struct or an enum] name;
   Then, whenever you write "name" in your code, it will be the same as if you
   had written the the thing that comes before. That way, if you create a
   struct with a typedef, you can simply write "name" instead of
   "struct [structname]", if that's your preferred style.
*/

typedef enum menu_choice_t
{
    DEFAULT = 0,
    LINUX   = 1,
    MAC     = 2,
    WINDOWS = 3,
    QUIT    = 4
} menu_choice;

/* The #define directive has the syntax
     #define  TOKEN  [anything you like]
   and has the effect of replacing TOKEN with [anything you like] in your code
   verbatim.
*/

#define  MY_FAVOURITE_NUMBER  256

/* Actually, it is allowed to simply define a token without giving it any
   "value". The token is still "defined", but is simply empty.
*/

#define EMPTY

/* The #ifdef directive allows you to test if a token has been defined. If it
   has, then the code between it and the next #endif directive will be
   included. If not, then the sandwiched code will be completely ignored.
   The #ifndef directive works similarly, but tests if a token is NOT defined.
*/

/* Macros look and smell like functions, and are also defined with the #define
   directive:
*/

#define  ADD_ONE(x)  ((x)+1)

/* It's not a function, though -- it's just an instruction for the
   preprocessor to replace every instance of ADD_ONE(...) with what follows,
   but also replacing "x" with whatever you supply as the argument. In this
   sense, they are more like "inline" functions. Because the substitutions
   happen literally, it's vital to over-use brackets. Consider the following
   example:
*/

#define NEGATIVE(x)  -x

/* If I had a line of code that read:
     int x = NEGATIVE(3+4);
   you would find that what the preprocessor has done is turned that into
     int x = -3+4;
   which is 1, instead of the -7 you were expecting.
   As a rule, then, use brackets around the whole expression, and also use
   brackets around each instance of each argument.
*/

/* Depending on what operating system you're using, some tokens get
   automatically defined. For example:
*/

#ifdef _WIN32    /* Windows-specific definitions and functions go here */

#define  INSULT  "You should be using a _real_ operating system!"
#define  CORRECT_CHOICE  WINDOWS

#endif


#ifdef __APPLE__   /* Mac-specific definitions and functions go here */

#define  INSULT  "When was the last time you experienced the spinning wheel of death?"
#define  CORRECT_CHOICE  MAC

#endif


#ifdef __linux__   /* Linux-specific definitions and functions go here */

#define  INSULT  "Yeah? Well I got open source. How d'ya like DEM apples?"
#define  CORRECT_CHOICE  LINUX

#endif


void print_menu()
{
    printf( "What system are you using?\n" );
    printf( "  1. Linux\n" );
    printf( "  2. Mac\n" );
    printf( "  3. Windows\n" );
    printf( "  4. Quit\n" );
}


int main()
{
#ifdef VERBOSE
    fprintf( stderr, "[VERBOSE] VERBOSE is switched on\n" );
#endif

#ifdef VERBOSE
    fprintf( stderr, "[VERBOSE] Printing menu\n" );
#endif

    print_menu();

    menu_choice mc = DEFAULT;
    while (1)
    {
        printf( "? " );
        scanf( "%d", (int *)&mc );

        switch (mc)  /* <-- a switch statement, syntactic sugar for
                        if / else if / else */
        {
            case LINUX:
            case MAC:
            case WINDOWS:
#ifdef VERBOSE
    fprintf( stderr, "[VERBOSE] Valid input received\n" );
#endif
                if (mc != CORRECT_CHOICE)
                    printf( "LIAR!\n" );
                else
                    printf( "%s\n", INSULT );
                break;
            case QUIT:
                printf( "Using macro: ADD_ONE(2) = %d\n", ADD_ONE(2) );
                exit(EXIT_SUCCESS);
                break;
            default:
#ifdef VERBOSE
    fprintf( stderr, "[VERBOSE] Invalid input received\n" );
#endif
                break;
        }
    }
}
