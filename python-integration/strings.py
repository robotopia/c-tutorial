import ctypes as ctp   # Import the ctypes module, which does the heavy lifting for us.
import os
import sys

# First we need to load the shared library.
# Just use the cdll.LoadLibrary() function, passing the path to the shared object.

lib = ctp.cdll.LoadLibrary("%s/cfunctions.so"%os.getcwd())

# Now access the fib function from our shared library.
hello = lib.hello


# Now tell Python what parameters and return types it expects.
# The types are includes in the ctypes module.
hello.argtypes = [ctp.c_char_p] # argtypes is always a list/tuple.


if __name__=="__main__":

    name = sys.argv[1]      # Grab the first cmdline argument
    hello(name)
