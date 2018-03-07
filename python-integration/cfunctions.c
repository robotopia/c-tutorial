/*
  cfunctions.c -- a random collection of simple functions in C

  These are written to be imported in Python.
 */
#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
  // Determine the nth fibbonacci number
  // Used in fib.py
  int a = 0, b = 1;
  for (int i=0; i<n; i++) {
    int tmp = b;
    b = a;
    a += tmp;
  }
  return a;
}


double weird_function(int n, float x, char c){
  // Used in multiple_types.py
  if(c=='y') return n*x;
  else return n*x*x;
}

void hello(char *name){
  // Used in strings.py
  printf("Hello, %s!\n", name);
}



/* =================================================
   The following functions/structures are used in
   structs.py.
   =================================================
*/
struct Result{
  int N;
  float L;
};

struct Result simulate(float L, float dx){
  struct Result result;

  result.N = L/dx;
  result.L = dx*result.N;
  return result;
}
// =================================================


int fib_sequence(int n, unsigned long *seq0, unsigned long *seq1){
  // used in ndpointer.py

  for (int i=0; i<n; i++){
    seq0[i] = fib(i);
    seq1[i] = fib(seq0[i]);
  }
  return 0;
}

