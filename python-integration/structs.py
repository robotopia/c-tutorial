import ctypes as ctp   # Import the ctypes module, which does the heavy lifting for us.
import os
import sys

# First we need to load the shared library.
# Just use the cdll.LoadLibrary() function, passing the path to the shared object.

lib = ctp.cdll.LoadLibrary("%s/cfunctions.so"%os.getcwd())

# Now access the fib function from our shared library.
simulate= lib.simulate

# NEW!!!
# We create a structure from C in Python as the following:
class Result(ctp.Structure):
    _fields_ = [
        ("N", ctp.c_int),
        ("L", ctp.c_float),
    ]

# Now tell Python what parameters and return types it expects.
# The types are includes in the ctypes module.
simulate.argtypes = 
simulate.restype = 


if __name__=="__main__":
    res = simulate(12.0, 0.1)

    print(res.N)
    print(res.L)

