cdef extern from "lwr.h" namespace "lwr":
	cdef cppclass LWR:
		LWR(lwr_options)
		void f(double *, const double * const, std::size_t)

cdef class pyLWR:
	cdef LWR *thisptr
	def __cinit__(self,lwr_options):
		self.thisptr = new LWR(lwr_options)
