import ctypes as ctp   # Import the ctypes module, which does the heavy lifting for us.
import os

# First we need to load the shared library.
# Just use the cdll.LoadLibrary() function, passing the path to the shared object.

lib = ctp.cdll.LoadLibrary("%s/cfunctions.so"%os.getcwd())

# Now access the fib function from our shared library.
cfunc = lib.weird_function


# Now tell Python what parameters and return types it expects.
# The types are includes in the ctypes module.
cfunc.restype = 
cfunc.argtypes = 


if __name__=="__main__":
    ans = 'x'
    while ans not in 'yn':
        if ans=='x':
            ans = input("Would you really like to actually run this properly?: [y/n]")
        else:
            ans = input("Come on, it's not that hard just to press y or n... try again: ")

    i = int(input("Okay, give me an int: "))
    x = float(input("And a float: "))
    
    print("Answer is: %s"%(cfunc(i,x,ctp.c_char(str.encode(ans)))))
