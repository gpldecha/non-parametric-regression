import sys
import os
import shutil

from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext


# clean previous build
for root, dirs, files in os.walk(".", topdown=False):
    for name in files:
        if (name.startswith("myext") and not(name.endswith(".pyx") or name.endswith(".pxd"))):
            os.remove(os.path.join(root, name))
    for name in dirs:
        if (name == "build"):
            shutil.rmtree(name)

# build "myext.so" python extension to be added to "PYTHONPATH" afterwards...
ext_modules = [
        Extension("lwr_options", 
        sources=["lwr_options.pyx"],
        libraries=["../lib/lwr"],          # refers to "libexternlib.so"
        language="c++",                   # remove this if C and not C++
        )]


setup(
    name = 'lwr_opt',
    ext_modules = cythonize(ext_modules),	
)   
