# Non-parametric regression

[![Build Status](https://travis-ci.org/gpldecha/non-parametric-regression.svg?branch=master)](https://travis-ci.org/gpldecha/non-parametric-regression) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/a1fad67f83ce442aabc2805d4bd2d6fd)](https://www.codacy.com/app/chambrierg/non-parametric-regression?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=gpldecha/non-parametric-regression&amp;utm_campaign=Badge_Grade)


This package provides a set of non-parametric methods for regression. The implementation of the methods are in **C++** 
[npr](https://github.com/gpldecha/non-parametric-regression/tree/master/npr) and **Python** interface is available 
[pynpr](https://github.com/gpldecha/non-parametric-regression/tree/master/pynpr). This library is built on [**FLANN**](http://www.cs.ubc.ca/research/flann/) which is a fast approximate nearest neighbour algorithm.


<img src="/docs/images/lwr_2D_example1_train.png" width="400"/><img src="/docs/images/lwr_2D_mid.png" width="400"/>
<img src="/docs/images/lwr_1D.png" width="400"><img src="/docs/images/lwr_1D_example2.png" width="400">



# Dependencies

```sh
sudo apt-get install libboost-python-dev libflann-dev libarmadillo-dev python-numpy
```

# Installation

1. Checkout the repository

  ```sh
    clone https://github.com/gpldecha/non-parametric-regression.git
  ```
2. Run the install.py script (from within the folder non-parametric-regression)

  ```bash
    python install.py
  ```
The script will check the dependencies and install them if missing and then will first 
build and install the [npr](https://github.com/gpldecha/non-parametric-regression/tree/master/npr) C++ library
and then build and install the python interface library [pynpr](https://github.com/gpldecha/non-parametric-regression/tree/master/pynpr).

# Examples

1. [examples/python](https://github.com/gpldecha/non-parametric-regression/tree/master/examples/python)
    
    A set of python interface examples for 1D, 2D and 3D regressions.
    
2. [examples/cpp](https://github.com/gpldecha/non-parametric-regression/tree/master/examples/cpp)    

    A set of examples on how to use the C++ interface.

# Regression methods

* Locally weighted regression (LWR)

Library of locally weighted (LWR) regression. LWR is a memory based regression which is non-parameteric. 
It stores a set of input, X, and target values, y which form the desired training data for the regressor 
function y = f(X).

When a new data point is queried X*, to be evaluated by the regressor f(X*), the K closest points to X* are found. 
On these points a linear regressor function is fitted and when evaluated at the point X* gives the value y*.
