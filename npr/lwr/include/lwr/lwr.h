#ifndef LWRegression_H_
#define LWRegression_H_

#include <armadillo>

#include <lwr/lwr_flann.h>
#include <lwr/lwr_options.h>

#include <utils/npr_utils.h>

namespace lwr{

class LWR{

public:

    LWR(lwr_options lwr_opts=lwr_options());

    void f(double *ptr_y, const double * const ptr_Xq, std::size_t num_cols);

    /**
     * @brief f         : evaluate regressor function y = f(x)
     * @param ptr_y     : predictor y  : (M x 1)
     * @param Xq        : input X      : (M x D)
     */
    void f(double *ptr_y, const arma::mat& Xq);

    void get_X(double *ptr_x);

    void get_Y(double *ptr_y);

    void set_X(const arma::mat& X);

    void set_X(const double * const ptr_X, std::size_t num_rows, std::size_t num_cols);

    void set_Y(const double * const ptr_Y, std::size_t num_rows);

    void set_Y(const arma::colvec& y);

    void ann(double *ptr_index, const double * const ptr_Xq, const size_t num_cols);

    void ann(const arma::mat& Xq);

    void clear();

    void print() const;

    int get_K() const;

    void set_regulisation(double reg);

    conversion::major mtype;

private:

    void f_simple(double *ptr_y, const arma::mat& Xq);

    void f_flann(double *ptr_y, const arma::mat& Xq);

    bool check_input(const arma::mat &Xq) const;

public:

        LWR_FLANN    lwr_flann;
        arma::mat    X;
        arma::colvec y;
        arma::mat    D; // distance covariance


private:

    lwr_options  lwr_opts;
    arma::mat    Xq;



    double       y_bias;
    double       k_bias;
    int          K;
    int          dim;

    // helper parameters
    arma::mat Xone;
    arma::colvec yone;

    arma::colvec W;
    arma::colvec B;
    arma::colvec Xy;
    arma::mat    WX;
    arma::mat    I;

    double*      ptr_index;

};


}

#endif
