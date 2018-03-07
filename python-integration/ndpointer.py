import ctypes as ctp   # Import the ctypes module, which does the heavy lifting for us.\
import sys

# NEW!!
# The numpy library has pointers built-in that can be interpreted as a numpy array.
from numpy.ctypeslib import ndpointer
import numpy as np

# First we need to load the shared library.
# Just use the cdll.LoadLibrary() function, passing the path to the shared object.

lib = ctp.cdll.LoadLibrary("./cfunctions.so")

# Now access the fib function from our shared library.
fib_sequence = lib.fib_sequence


# Now tell Python what parameters and return types it expects.
fib_sequence.argtypes = [ctp.c_int, ndpointer(np.uint64), ndpointer(np.uint64)]


if __name__=="__main__":
    n = 10
    seq0 = np.empty(n, dtype=np.uint64)
    seq1 = np.empty(n, dtype=np.uint64)

    # seq0 and seq1 get filled up in the C function
    fib_sequence()

    print(seq0, seq1)

