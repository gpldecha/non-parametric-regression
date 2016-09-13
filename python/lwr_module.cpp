#include <boost/python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "lwr/lwr_options.h"
#include "lwr/lwr.h"
#include <numpy/ndarrayobject.h> // ensure you include this header
#include <boost/numpy.hpp>




using namespace boost::python;
namespace py = boost::python;
namespace bp = boost::python;
namespace bn = boost::numpy;

py::list get(const lwr::lwr_options& lwr_opts)
{
    py::object get_iter = py::iterator<std::vector<double> >();
    py::object iter = get_iter(lwr_opts.D);
    py::list l(iter);
    return l;
}

void set(lwr::lwr_options& lwr_opts,py::object o)
{
    std::vector<double>& D = lwr_opts.D;
    py::stl_input_iterator<double> begin(o);
    py::stl_input_iterator<double> end;
    D.clear();
    D.insert(D.end(), begin, end);
}


py::object stdVecToNumpyArray( std::vector<double> const& vec )
{
      npy_intp size = vec.size();

     /* const_cast is rather horrible but we need a writable pointer
        in C++11, vec.data() will do the trick
        but you will still need to const_cast
      */

      double * data = size ? const_cast<double *>(&vec[0])
        : static_cast<double *>(NULL);

    // create a PyObject * from pointer and data
      PyObject * pyObj = PyArray_SimpleNewFromData( 1, &size, NPY_DOUBLE, data );
      boost::python::handle<> handle( pyObj );
      boost::python::numeric::array arr( handle );

    /* The problem of returning arr is twofold: firstly the user can modify
      the data which will betray the const-correctness
      Secondly the lifetime of the data is managed by the C++ API and not the
      lifetime of the numpy array whatsoever. But we have a simple solution..
     */

       return arr.copy(); // copy the object. numpy owns the copy now.
  }


void lwr_set_X(lwr::LWR lwr,const py::numeric::array &a)
{

    char const * ca = py::extract<char const *>(py::str(a));
    std::cout << "Original array:\n" <<  ca << std::endl;

}


BOOST_PYTHON_MODULE(pylwr)
{
    py::numeric::array::set_module_and_type("numpy", "ndarray");
    import_array();


    class_<lwr::lwr_options>("lwr_options")
        .def("print", &lwr::lwr_options::print)
        .def_readwrite("bUseKDT",&lwr::lwr_options::bUseKDT)
        .def_readwrite("dim",&lwr::lwr_options::dim)
        .def_readwrite("K",&lwr::lwr_options::K)
        .def_readwrite("k_bias",&lwr::lwr_options::k_bias)
        .def_readwrite("y_bias",&lwr::lwr_options::y_bias)
        .add_property("D",get,set)

    ;

    class_<lwr::LWR>("LWR")
        .def(init<lwr::lwr_options>())
        .def("set_X",lwr_set_X)
    ;


}
