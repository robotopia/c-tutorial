#!/usr/bin/env python
# -*- encoding: utf-8 -*-

from __future__ import absolute_import
from __future__ import print_function


from setuptools import Extension
from setuptools import find_packages
from setuptools import setup


setup(
    name='mypackage',
    version='0.1.0',
    license='MIT license',
    description='A set of python bindings for weird c functions',
    author='Steven Murray',
    packages=find_packages(),

    ext_modules=[
        Extension(
            'mypackage.cfunctions',
            sources=['cfunctions.c'],
            extra_compile_args = ['-Ofast']
        )
        
    ],
)
    
