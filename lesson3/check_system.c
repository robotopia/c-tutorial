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

#include <stdio.h>  /* <-- We've met this one many times now. This preprocessor
                           directive imports the contents of the named file
                           into this file. */
#include "version.h"


typedef enum menu_choice_t { DEFAULT = 0, LINUX = 1, MAC = 2, WINDOWS = 3, QUIT = 4 } menu_choice;


/* Depending on what operating system you're using, some tokens get
   automatically defined. For example:
*/

#ifdef _WIN32

/*
   ...
   Windows-specific definitions and functions go here
   ...
*/

#define  INSULT  "You should be using a _real_ operating system!"
#define  CORRECT_CHOICE  WINDOWS

#endif

#ifdef __APPLE__

/*
   ...
   Mac-specific definitions and functions go here
   ...
*/

#define  INSULT  "When was the last time you experienced the spinning wheel of death?"
#define  CORRECT_CHOICE  MAC

#endif

#ifdef __linux__

/*
   ...
   Linux-specific definitions and functions go here
   ...
*/

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
        do
        {
            printf( "? " );
        } while ((scanf( "%d", &mc ) != 1));

#ifdef VERBOSE
    fprintf( stderr, "[VERBOSE] Valid input received\n" );
#endif

        switch (mc)
        {
            case LINUX:
            case MAC:
            case WINDOWS:
                if (mc != CORRECT_CHOICE)
                    printf( "LIAR!\n" );
                else
                    printf( "%s\n", INSULT );
                break;
            case QUIT:
                break;
        }
    }
}
