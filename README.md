# Non-parametric regression

[![Build Status](https://travis-ci.org/gpldecha/non-parametric-regression.svg?branch=master)](https://travis-ci.org/gpldecha/non-parametric-regression)

This package provides a set of non-parametric methods for regression. The implementation of the methods is done in C++ whilst the interface is python. 

# Installation

This library is based on  [**Armadillo**](http://arma.sourceforge.net/download.html) which is an intuitive interface
to Eigen. Make sure you have installed all the dependencies to Eigen perfor proceedind to install armadillo. You 
can simply run the following commnad to install all the dependencies:

sudo apt-get install libarmadillo-dev

Checkout the repository:

$ https://github.com/gpldecha/non-parametric-regression.git


# Quick start


# Regression methods



Library of locally weighted (LWR) regression. LWR is a memory based regression which is non-parameteric. 
It stores a set of input, X, and target values, y which form the desired training data for the regressor 
function y = f(X).

When a new data point is queried X*, to be evaluated by the regressor f(X*), the K closest points to X* are found. 
On these points a linear regressor function is fitted and when evaluated at the point X* gives the value y*.
