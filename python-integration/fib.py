import ctypes as ctp   # Import the ctypes module, which does the heavy lifting for us.

# First we need to load the shared library.
# Just use the cdll.LoadLibrary() function, passing the path to the shared object.
lib = ctp.cdll.LoadLibrary("./cfunctions.so")

# Now access the fib function from our shared library.
fib = lib.fib


# Now tell Python what parameters and return types it expects.
# The types are includes in the ctypes module.
fib.restype = ctp.c_int    # restype is always a single type, since C only passes back a single value.
fib.argtypes = [ctp.c_int] # argtypes is always a list/tuple.



# We want to use this function in some way.
# Do this in a name=main construct because it's the right thing to do.
if __name__=="__main__":

    # We do something slightly fancy, to show that you'd usually
    # do the logic part in Python, and the crunching part in C.
    # We're printing the first ten values in fib(fib(i))
    for i in range(10):
        n = fib(i)
        print(fib(n))
