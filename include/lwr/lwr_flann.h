#ifndef LWR_FLANN_H_
#define LWR_FLANN_H_

#include <flann/flann.h>
#include <flann/util/matrix.h>
#include <armadillo>
#include <memory>

namespace lwr {

class LWR_FLANN{

public:

    LWR_FLANN();

    LWR_FLANN(const arma::mat& X, int K);

    /**
     * @brief ann   : Computes Approximate Nearest Neighbour structure of X
     * @param Xq    : (D x M), D dimensional M points
     */
    void ann(const arma::mat& Xq);

    ///
    /// \brief get_indicies (C++ to matlab)
    /// \param ptr_indicies matlab's array of indicies to be filled
    ///
    void get_indicies(double *ptr_indicies);

    void print() const{
        if(sptr_index != NULL){
            IndexParams index_param = sptr_index->getParameters();
            print_params(index_param);
        }
    }

private:

    void set_data(const arma::mat& X);

    void build_index();

    template<typename T>
    void print_row(const flann::Matrix<T>& m,std::size_t r) const{
        std::cout<< "(" << r << ") = ";
        for(std::size_t i = 0; i < m.cols;i++){
            std::cout<< m[r][i] << " ";
        }
        std::cout<<std::endl;
    }


public:

     Matrix<double> query;      // (M x D)
     Matrix<int>    indices;    // (M x K)
     Matrix<double> dists;      // (M x K)


private:

     int*       ptr_indices;
     double*    ptr_dists;

    std::shared_ptr<Index<L2<double> > > sptr_index;
    Matrix<double>      dataset;
    std::size_t         ii;
    int                 K;
    int                 dim;


};


}



#endif
