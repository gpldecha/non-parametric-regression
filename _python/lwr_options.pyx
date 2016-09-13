# lwr_options.pxd

cimport lwr_options


cdef class pyLwr_options:
	cdef lwr_options *thisptr
	def __cinit__(self):
		self.thisptr = new lwr_options()
	def __dealloc__(self):
		del self.thisptr

	def lwr_print(self):
		return self.lwr_print()

