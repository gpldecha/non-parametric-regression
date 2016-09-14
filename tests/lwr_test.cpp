#include <lwr/lwr.h>
#include <boost/chrono.hpp>
#include <boost/lexical_cast.hpp>

double evaluate_lwr(int dim,int num_data,int num_test){



    lwr::lwr_options lwr_opts;

    lwr_opts.D.resize(dim);
    for(int i = 0; i < dim;i++){
        lwr_opts.D[i] = 1*1;
    }

    lwr_opts.k_bias = 1;
    lwr_opts.y_bias = 0;
    lwr_opts.bUseKDT = true;

    lwr::LWR Lwr(lwr_opts);
    Lwr.mtype = conversion::ROW_M;

    // Generate data
    arma::mat    X(num_data,dim,arma::fill::randu);

    X = X.st();


    X = X * 10;
    arma::colvec y(num_data,arma::fill::randu);
    arma::mat Xtest(num_test,dim,arma::fill::randu);
    Xtest = Xtest.st();
    double *ptr_y = new double[num_test];

    Lwr.set_X(X);
    Lwr.set_Y(y);

    auto start = boost::chrono::steady_clock::now();

    Lwr.f(ptr_y,Xtest);

    auto end = boost::chrono::steady_clock::now();

    auto diff = end - start;

    return boost::chrono::duration <double, boost::milli> (diff).count() / 1000.0;

}



int main(int argc,char** argv){

    std::cout<< "=== LWR (test run) ===" << std::endl;

    std::vector<int> dims(15);
    for(std::size_t i = 0; i < dims.size();i++){
        dims[i] = i+1;
    }
    std::vector<int> num_data = {{1000,10000,100000,100000}};


    int num_runs = 10;

    arma::mat time(num_data.size(),dims.size());
    time.zeros();

    for(int r = 0; r < num_runs;r++){

        std::cout<< "run(" << r+1 << ")" << std::endl;


        for(std::size_t i = 0; i < num_data.size();i++){
            std::cout<< i << "/" << num_data.size() << std::endl;
            for(std::size_t j = 0; j < dims.size();j++){
                time(i,j) = evaluate_lwr(dims[j],num_data[i],1);
            }
        }


        time.save("time_ " + boost::lexical_cast<std::string>(r+1) + ".txt",arma::raw_ascii);

    }




    return 0;
}
