/* === MIT License ===

Copyright (c) 2018 Kistóf Rozgonyi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
===============================================================================
Fast solution for the 14th problem of the Euler project: https://projecteuler.net/problem=14

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

//=================
//IMPORTS
//=================
#include <stdio.h>

//=================
//FUNCTIONS
//=================
int recursive_collatz(long int x, int l)
{
    //Return the lenght (l) of a collatz sequence for x
        
    if(x == 1)
    {
        return l;
    }
    else
    {
        if(x%2==0)
        {
            return recursive_collatz(x >> 1, l + 1);
        }
        else
        {
            return recursive_collatz((x*3+1) >> 1, l + 2);//using a shortcut
        }
    }
}

//=================
//MAIN
//=================
int main()
{
    long int i;
    int l, solution;
    int placeholder = 0;
    int lenght = 0;
    
    for(i = 3; i < 1000000; ++i)
    {   
        l = 0; 
        lenght = recursive_collatz(i,l);
        if(lenght > placeholder)
        {
            placeholder =  lenght;
            solution = i;
        }
    }        
    printf("%i\n",solution);
}
