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
 * This program is designed to demonstrate what the compiler is actually doing
 * when you ask it to compile a program.
 *
 *****************************************************************************/

/* In this source file, I'm defining four functions but no main() function.
   This means that I won't be able to turn this source code into an executable
   program, but we still will be able to use the compiler (gcc) to perform the
   first stage of the compilation, which is to convert this code into binary.
*/

double add( double x, double y )
{
    return x+y;
}

double subtract( double x, double y )
{
    return x-y;
}

double multiply( double x, double y )
{
    return x*y;
}

double divide( double x, double y )
{
    return x/y;
}


