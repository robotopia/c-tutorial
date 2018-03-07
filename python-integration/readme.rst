Integrating C Code with Python
==============================

This is a small tutorial about how to integrate C code into Python applications/libraries,
with a few hands-on exercises. It should follow the rest of the lessons in this repository.
This is written by Steven Murray, but it tries to follow the basic layout/philosophy
of the rest of this C tutorial written by Sammy McSweeney.


Introduction
------------

There are many ways to integrate C into Python, due to the popularity of doing so. Remember
that Python itself is written in C, so many of the standard library routines are merely
wrapped C code.

In this tutorial, I'll only cover the most *simple* way of integrating the two. This way
may not be the best if you have a large C library which needs to be carefully wrapped
and updated regularly. To do that, you might want to take a look at one of Swig, CFFI or
Cython. We, however, will just basic ctypes.

We will look at how to wrap simple functions, specify argument and return types, wrap
arbitrary structures, compile C code upon Python library installation and deal with
C arrays/pointers.  We *won't* look at Python callbacks (i.e. calling Python functions
from C) or making the C functions behave like a Python function internally.


Philosophy
----------

The general idea of how this integration works is that the C code is compiled to a shared
library, which can be directly imported within Python using a special standard library
function. This shared library should contains symbols -- corresponding to functions and
variables -- which can be identified within Python. The most common case is a function.

To enable the calling of this function within Python, Python needs to know how to convert
the arguments it gives the function to the correct C type, and also needs to know about
what type the C function returns. Libraries like Swig can help to specify these things
within the C code itself. But typically I find that we inherit C code that we don't really
want to change (or we can't, otherwise we'd have to keep changing it every time it's
externally updated). So we need to specify them for Python, and we do that using the
standard lib ``ctypes``.

All of this has a few implications for what makes good C code to wrap. First of all, we
don't really want to wrap an *application* -- we don't want to wrap the ``main()`` function.
We want to wrap the library functions within the C code. Second, dealing with C globals
makes things tricky. If you want to update a global from Python, you need to be reasonably
careful, and I'm not even sure what happens if you try to update a global to different
values using multiple processes. The *best* attitude to have in writing the C code is to make
everything as modular and standalone as possible. Let each C function contain all it needs
to run itself, either as passed arguments, or as variables defined within the function.
This gives the most flexibility and simplicity when calling from Python. Having pre-processor
#define statements means those variables will be unchangeable without re-compilation, which
is something we almost never want to do in Python-land.


What kinds of functions should we try to write in C, rather than Python? Usually, the sole
purpose of writing in C is speed. Typically, the largest slow-downs in Python are due to
large loops over smallish operations. Due to the dynamic typing of Python, it has to check
on each iteration what to do with your variables. If the loop can be vectorized (in Numpy),
then this slow-down is largely avoided, and you shouldn't need to write C. Some problems
are either impossible, or too unwieldy, to vectorize. This is when C can really help. You want
C to help speed up as small units as possible, so that the logic and flexibility can be aided
from Python.



Wrapping Simple Function Types
------------------------------
Open up ``cfunctions.c``, and you'll see a bunch of functions defined. This is going to be
the C library that we will try to wrap, bit by bit. The first thing that changes is
that to call the functions from Python, we need to compile as a shared library.

You can open the ``Makefile-cfunctions`` to have a look at how we do this.

Run

```
$ cp Makefile-cfunctions Makefile
$ make
```

Now you should see a ``cfunction.so`` file in your directory. This is what we will use.

Open up ``fib.py``. This file goes through in some detail how to load the library and use it.
One could just as well load up the library in an IPython/Jupyter notebook and use it
interactively. You can then run ``python fib.py`` to see its output.

Try to keep ``cfunctions.c`` open in a tab somewhere, so we can reference it. We'll now
see how to wrap the  ``weirdfunction``. Open up ``multiple_types.py``. It's your job
to add in the correct restype and argtypes. Note that every type is its C name, prefixed
by ``c``_. When done, run ``python multiple_types.py`` to see the output.



Finally, open up ``strings.py``. This shows how to pass strings (not just char). The 
``c_char_p`` type is a pointer to a C char. Try running ``python strings.py <your_name>``.
You might get an error, if using Python3. Here, you need to be careful to encode your strings
before passing them. Change ``hello(name)`` to ``hello(str.encode(name))``.



Wrapping Structure Return Types
--------------------------------
If you want to get more than one value back from your C function, you can either
pass a pointer to a value, and let the function fill up that pointer's memory, or
you can pass back a custom struct.

Look at the struct we have defined for the ``simulate()`` function. To wrap this in Python,
ctypes provides a ``Structure`` class, which can be subclassed to create a proper return
type. See ``structs.py`` to see how this is defined. Here, you'll have to add the correct
argtypes and restype before it will run properly.


Pointers
--------
The ctypes module includes a POINTER function, which can be applied to any type to indicate
that the argtype is a pointer of that kind. However, for our applications, we usually use
pointers for arrays, and numpy has its own ctypes library which allows to interpret pointers
as numpy arrays.

The easiest (but not only) way to do this is to create the memory using numpy, and pass the
array to the C function, for it to fill up or use. Your job in ``ndpointer.py`` is to pass
in the correct arguments to ``fib_sequence``. 

You should beware of creating memory in C which gets passed back to Python. You then have
to manually manage the memory, making sure you free it when you need to. An ``ndpointer``
can also be part of a struct. The ndpointer function takes a few keyword arguments which can 
specify the number of dimensions, and how the array is laid out in memory.




Creating a Python Wrapper Library
---------------------------------

You will have noticed that every python script has similar boilerplate code to read the shared
object. Usually, the C functions will be a little more unified in purpose than in our case,
and usually, we will want to provide wrappers to them all in one importable library. 

The setuptools library has a nice selection of tools for doing this. It will compile the C code
within a package, and install it wherever your package goes, so it can be imported. As an example
of how to do this, you'll see that there is a setup.py file in this directory. There is also
a Python package, with an ``__init__.py`` file in it. Open that up. You'll see it consists
of basically the same boilerplate (though notice some subtle differences in loading,
because we have to be able to load it from any working directory). Then, each of the wrappers
is just copied in. 

Now open ``setup.py``. This is a very normal setup, if you've ever created one of these before. 
The interesting part is the ``ext_modules``, for which we use the ``Extension`` class to create 
our C extension. The first argument is the location of the cfunctions "module", which will be
the .so file. The second argument is just the source files, relative to the setup.py. The third
argument are any arguments used in the compilation. Notice we don't need the ``-shared`` option,
since it will put all of these kinds of things in for us. 

We can simply run ``python setup.py install``, and the package will be installed into your 
Python environment. You can import this within IPython directly:

```
>>> import mypackage
>>> mypackage.fib(10)
```

If you end up uploading your package to PyPi, then others will be able to install your code,
automatically compiling everything, just by doing ``pip install mypackage``. 


Some Other Notes
----------------
To the setup.py file you can also include lots of other options, like include directories, and includes. 
You can compile against openmp and blas and gsl etc. This is a cheap way of getting multi-threading
support in your application. 




















