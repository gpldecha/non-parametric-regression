import cython
from libcpp.vector cimport vector
from libcpp cimport bool

cdef extern from "../include/lwr/lwr_options.h" namespace "lwr":
	cdef cppclass lwr_options:
		lwr_options() except +
		void lwr_print() const
		int dim
		bool bUseKDT
		vector[double] D
		double y_bias
		double k_bias
		int K

