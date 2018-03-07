import ctypes as ctp   # Import the ctypes module, which does the heavy lifting for us.
import os
import sys
import glob

from numpy.ctypeslib import ndpointer
import numpy as np

# Here we tell Python which objects in this module to actually export.
__all__ = ['fib', 'weird_function', 'hello', 'simulate', 'fib_sequence']


# Read in the shared object
LOCATION = os.path.dirname(os.path.abspath(__file__))
SharedLibraryLocation = glob.glob("%s/cfunctions.*.so" % LOCATION)[0]
lib = ctp.cdll.LoadLibrary(SharedLibraryLocation)


# Now access all the functions from our shared library.
fib = lib.fib
weird_function = lib.weird_function
hello = lib.hello
simulate = lib.simulate
fib_sequence = lib.fib_sequence


# Create the wrappers for each
# ============================
fib.restype = ctp.c_int    
fib.argtypes = [ctp.c_int] 


weird_function.restype = ctp.c_double 
weird_function.argtypes = [ctp.c_int, ctp.c_float, ctp.c_char]


hello.argtypes = [ctp.c_char_p]


class Result(ctp.Structure):
    _fields_ = [
        ("N", ctp.c_int),
        ("L", ctp.c_float),
    ]
simulate.argtypes = [ctp.c_float, ctp.c_float]
simulate.restype = Result 

        
fib_sequence.argtypes = [ctp.c_int, ndpointer(np.uint64), ndpointer(np.uint64)]
