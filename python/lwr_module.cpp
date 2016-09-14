#include <boost/python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "lwr/lwr_options.h"
#include "lwr/lwr.h"

#include "/usr/include/numpy/ndarrayobject.h"

using namespace boost::python;
namespace py = boost::python;

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

    double * data = size ? const_cast<double *>(&vec[0])
            : static_cast<double *>(NULL);

    PyObject * pyObj = PyArray_SimpleNewFromData( 1, &size, NPY_DOUBLE, data );
    boost::python::handle<> handle( pyObj );
    boost::python::numeric::array arr( handle );
    return arr.copy(); // copy the object. numpy owns the copy now.
}


void arr2mat(const py::numeric::array &a, arma::mat& X, const std::size_t D, const std::size_t N)
{
    if(X.n_elem != D * N)
    {
        X.resize(D,N);
    }

    if(D == 1){

        for(std::size_t i = 0; i < N; i++) {
            X(0,i) = extract<double>(a[i]);

        }

    }else if(D == 2){

        for(std::size_t i = 0; i < D; i++) {
            for (std::size_t j = 0; j < N; j++) {
                X(i,j) = extract<double>(a[i][j]);
            }
        }

    }else{
        std::cerr<< "lwr_modules.cpp: arr2mat: only 1D and 2D X supported!" << std::endl;
        return;
    }


}

void arr2colvec(const py::numeric::array& a, arma::colvec& y, const std::size_t rows)
{
    if(y.n_elem != rows)
    {
        y.resize(rows);
    }

    for(std::size_t i = 0; i < rows; i++) {
        y(i) = extract<double>(a[i]);
    }
}


/**
 * @brief lwr_train : sets the parameters -> data points (X,y)
 * @param lwr
 * @param arr_X     : (N x D), N: number of samples, D: number of dimensions
 * @param arr_y     : (N x 1), predictor output
 */
void lwr_train(lwr::LWR& lwr, const py::numeric::array& arr_X, const py::numeric::array& arr_y)
{
    const tuple &shape_X = extract<tuple>(arr_X.attr("shape"));
    const tuple &shape_y = extract<tuple>(arr_y.attr("shape"));

    int num_dim_X = py::len(shape_X);
    int num_dim_y = py::len(shape_y);

    std::cout<< "num_dim_X: " << num_dim_X << std::endl;
    std::cout<< "num_dim_y: " << num_dim_y << std::endl;

    if(num_dim_y != 1)
    {
        std::cout<< "y should be a one dimensional numpy array: (N,)" << std::endl;
        return;
    }

    int X_n, X_d, y_n, y_d;

    if(num_dim_X == 1){
        X_d = 1;
        X_n = extract<int>(shape_X[0]); // N
    }else if(num_dim_X == 2){
        X_d = extract<int>(shape_X[0]);
        X_n = extract<int>(shape_X[1]); // N
    }else{
        std::cout<< "numpy array X should have 2 dimensions: (N x D), currently:  " << num_dim_X << std::endl;
        return;
    }


    y_n = extract<int>(shape_y[0]); // N
    y_d = 1;

    std::cout<< "X_n: " << X_n << " x_d: " << X_d << std::endl;
    std::cout<< "y_n: " << y_n << " y_d: " << y_d << std::endl;

    if(y_d != 1)
    {
        std::cout<< "predictor y must be a column vector, currently (" << y_n << " x " << y_d << ")!" << std::endl;
        return;
    }

    if(X_n != y_n)
    {
        std::cout<< "both input X and predictor y should have the same number of samples" << std::endl;
        std::cout<< "   currently X: (" << X_n << " x " << X_d << ")  y: (" << y_n << " x " << y_d << ")!" << std::endl;
        return;
    }

    arma::mat X(X_d,X_n);
    arma::colvec y(y_n);

    arr2mat(arr_X,X,X_d,X_n);
    arr2colvec(arr_y,y,y_n);

    std::cout<< "X: (" << X.n_rows << " x " << X.n_cols << ")" << std::endl;

    lwr.set_X(X);
    lwr.set_Y(y);
}


py::object lwr_predict(lwr::LWR& lwr, const py::numeric::array& arr_X)
{

    PyObject* pyObj = NULL;

    const tuple &shape_X = extract<tuple>(arr_X.attr("shape"));
    int num_dim_X = py::len(shape_X);

    int X_n, X_d;

    if(num_dim_X == 1){
        X_d = 1;
        X_n = extract<int>(shape_X[0]); // N
    }else if(num_dim_X == 2){
        X_d = extract<int>(shape_X[0]);
        X_n = extract<int>(shape_X[1]); // N
    }else{
        std::cout<< "numpy array X should have 2 dimensions: (N x D), currently:  " << num_dim_X << std::endl;
    }

    // copy input
    arma::mat Xq(X_d,X_n);
    arr2mat(arr_X,Xq,X_d,X_n);
    // prepare outputs
    double data[X_n];


    lwr.f(data,Xq);


    npy_intp size = X_n;
    pyObj = PyArray_SimpleNewFromData( 1, &size, NPY_DOUBLE, data );


    boost::python::handle<> handle( pyObj );
    boost::python::numeric::array arr( handle );
    return arr.copy();
}


BOOST_PYTHON_MODULE(pylwr)
{
    py::numeric::array::set_module_and_type("numpy", "ndarray");
    import_array();


    class_<lwr::lwr_options>("lwr_options")
            .def("print_param", &lwr::lwr_options::print)
            .def_readwrite("bUseKDT",&lwr::lwr_options::bUseKDT)
            .def_readwrite("K",&lwr::lwr_options::K)
            .def_readwrite("k_bias",&lwr::lwr_options::k_bias)
            .def_readwrite("y_bias",&lwr::lwr_options::y_bias)
            .add_property("D",get,set)

            ;

    class_<lwr::LWR>("LWR")
            .def(init<lwr::lwr_options>())
            .def("train",lwr_train)
            .def("predict",lwr_predict)
            ;

}
