# lwr_options.pxd

import cython
from libcpp.vector cimport vector

cdef extern from "lwr_options.h" namespace "lwr":
	cdef cppclass lwr_options:
		lwr_options() except +
		lwr_options(int,bool,std::vector<double>&,double,double,int) except +
		void print() const
