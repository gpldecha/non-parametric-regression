#include <iostream>
#include <lwr/lwr.h>
#include <lwr/lwr_flann.h>
#include <armadillo>
#include <boost/lexical_cast.hpp>
#include <flann/io/hdf5.h>
#include <iostream>

void simple_ann_test(){
    int nn = 3;

    Matrix<float> dataset;
    Matrix<float> query;
    load_from_file(dataset, "dataset.hdf5","dataset");
    load_from_file(query, "dataset.hdf5","query");



    Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
    Matrix<float> dists(new float[query.rows*nn], query.rows, nn);


    std::cout<< "dataset: (" << dataset.rows << " x " << dataset.cols << ")" << std::endl;
    std::cout<< "query:   (" << query.rows << " x " << query.cols << ")" << std::endl;
    std::cout<< "indices: (" << indices.rows << " x " << indices.cols << ")" << std::endl;



    // construct an randomized kd-tree index using 4 kd-trees
    Index<L2<float> > index(dataset, flann::KDTreeIndexParams(4));
    index.buildIndex();

    // do a knn search, using 128 checks
    index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));

    flann::save_to_file(indices,"result.hdf5","result");

    delete[] dataset.ptr();
    delete[] query.ptr();
    delete[] indices.ptr();
    delete[] dists.ptr();
}

void simple_ann_test2(){

    int nn = 3;

    Matrix<double> dataset;
    Matrix<double> query;
    load_from_file(dataset, "dataset.hdf5","dataset");
    load_from_file(query, "dataset.hdf5","query");



    Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
    Matrix<double> dists(new double[query.rows*nn], query.rows, nn);

    std::cout<< "dataset: (" << dataset.rows << " x " << dataset.cols << ")" << std::endl;
    std::cout<< "query:   (" << query.rows << " x " << query.cols << ")" << std::endl;
    std::cout<< "indices: (" << indices.rows << " x " << indices.cols << ")" << std::endl;

    // construct an randomized kd-tree index using 4 kd-trees
    Index<L2<double> > index(dataset, flann::KDTreeIndexParams(4));
    index.buildIndex();

    // do a knn search, using 128 checks
    index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));

    flann::save_to_file(indices,"result.hdf5","result");

    delete[] dataset.ptr();
    delete[] query.ptr();
    delete[] indices.ptr();
    delete[] dists.ptr();

}

void simple_ann_test3(){

    int nn = 3;

    int dim        = 3;
    int numSamples = 9000;
    int numQuery   = 1000;
    arma::mat    X(dim,numSamples,arma::fill::randu);
    arma::mat    Xq(dim,numQuery,arma::fill::randu);
    X   = X * 100;
    Xq  = Xq * 100;


    double *ptr_X     = X.memptr();
    double *ptr_query = Xq.memptr();

    Matrix<double> dataset(ptr_X,X.n_cols,X.n_rows);
    Matrix<double> query(ptr_query,Xq.n_cols,Xq.n_rows);
    Matrix<int>     indices(new int[query.rows*nn], query.rows, nn);
    Matrix<double>  dists(new double[query.rows*nn], query.rows, nn);

    std::cout<< "dataset: (" << dataset.rows << " x " << dataset.cols << ")" << std::endl;
    std::cout<< "query:   (" << query.rows << " x " << query.cols << ")" << std::endl;
    std::cout<< "indices: (" << indices.rows << " x " << indices.cols << ")" << std::endl;

    // construct an randomized kd-tree index using 4 kd-trees
    Index<L2<double> > index(dataset, flann::KDTreeIndexParams(4));
    index.buildIndex();

    // do a knn search, using 128 checks
    index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));

    std::cout<< "after KNN" << std::endl;

   // delete[] dataset.ptr();
  //  delete[] query.ptr();
  //  delete[] indices.ptr();
  //  delete[] dists.ptr();

}

void my_test(){

    int dim        = 2;
    int numSamples = 1000;
    int numQuery   = 10;
    arma::mat    X(dim,numSamples,arma::fill::randu);
    arma::mat    Xq(dim,numQuery,arma::fill::randu);
    arma::colvec  y(numSamples,arma::fill::randu);
    X   = X * 100;
    Xq  = Xq * 100;



    lwr::lwr_options lwr_opts;

    lwr_opts.D.resize(dim);
    for(int i = 0; i < dim;i++){
        lwr_opts.D[i] = 1*1;
    }

    lwr_opts.k_bias  = 1;
    lwr_opts.K       = 3;
    lwr_opts.bUseKDT = true;

    lwr::LWR Lwr(lwr_opts);
    Lwr.mtype = conversion::ROW_M;



    Lwr.print();

    double* ptr_y = new double[numQuery];

    for(std::size_t i=0; i < 100;i++){


        Lwr.set_X(X);
        Lwr.set_Y(y);

        Lwr.f(ptr_y,Xq);
        std::cout<< "i: " << i << std::endl;
        sleep(1);

    }


    //Lwr.lwr_flann.ann(Xq);
    std::cout<< "=== delete Lwr ===" << std::endl;



}

void f_flann_test(){

    int dim        = 2;
    int numSamples = 200;
    int numQuery   = 1;
    arma::mat     X(dim,numSamples,arma::fill::randu);
    arma::mat    Xq(dim,numQuery,arma::fill::randu);
    arma::colvec  y(numSamples,arma::fill::randu);

    X   = X  * 100;
    Xq  = Xq * 100;
    Xq(0,0) = 500;
    Xq(1,0) = 500;


    lwr::lwr_options lwr_opts;

    lwr_opts.D.resize(dim);
    for(int i = 0; i < dim;i++){
        lwr_opts.D[i] = 5*5;
    }

    lwr_opts.k_bias  = 1;
    lwr_opts.y_bias  = 0;
    lwr_opts.K       = 10;
    lwr_opts.bUseKDT = true;

    lwr::LWR Lwr(lwr_opts);
    Lwr.mtype = conversion::ROW_M;

    Lwr.set_X(X);
    Lwr.set_Y(y);

    double* ptr_y = new double[numQuery];

    Lwr.f(ptr_y,Xq);

    Lwr.lwr_flann.print();

}

void arma_test(){

    arma::mat A(3,3);

    A(0,0) = 25.0000; A(0,1) =  25.0000; A(0,2) =  -5.0000;
    A(1,0) = 25.0000; A(1,1) =  25.0000; A(1,2) =  -5.0000;
    A(2,0) = -5.0000; A(2,1) =  -5.0000; A(2,2) =    1.0000;

    A.print("A");

    pinv(A).print("pinv(A)");

}


int main(int argc, char** argv)
{

    std::cout<< "=== lwr_run ===" << std::endl;
   /* std::cout<< " test 2  " << std::endl;
    simple_ann_test2();
    std::cout<< " test 3  " << std::endl;*/
   // simple_ann_test3();
//    std::cout<< " my_test  " << std::endl;
 //   my_test();

    my_test();


  return 0;
}
