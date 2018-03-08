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
#include <omp.h>

//=================
//STRUCTS
//=================
struct comp
{
    long int x; // The starting number of a chain
    int l; // The length of the chain
};

//=================
//OPENMP
//=================
#pragma omp declare reduction(maximum : struct comp : omp_out = omp_in.l > omp_out.l ? omp_in : omp_out)

//=================
//FUNCTIONS
//=================
int recursive_collatz(struct comp *c)
{
    //Return the lenght (l) of a collatz sequence for x
        
    struct comp next;
    if(c->x == 1)
    {
        return c->l;
    }
    else
    {
        if(c->x%2==0)
        {
            next.x = c->x >> 1;
            next.l = c->l + 1;
        }
        else
        {
            next.x = (c->x*3+1) >> 1;
            next.l = c->l + 2;
        }
        return recursive_collatz(&next);
    }
}

//=================
//MAIN
//=================
int main()
{
    struct comp min;
    min.x = 0;
    min.l = 0;
    long int i;
    
#pragma omp parallel for reduction(maximum:min)
    for(i = 3; i < 1000000; ++i)
    {   
        struct comp c;
        c.x = i;
        c.l = 0;
        int lenght = recursive_collatz(&c);
        if(lenght > min.l)
        {
            min.l = lenght;
            min.x = i;
        }
    }        
    printf("%ld\n",min.x);
}
