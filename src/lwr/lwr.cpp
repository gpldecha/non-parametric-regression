#include "lwr/lwr.h"

namespace lwr {


LWR::LWR(lwr_options lwr_opts):lwr_opts(lwr_opts){
    K      = lwr_opts.K;
    y_bias = lwr_opts.y_bias;
    k_bias = 1;
    dim    = lwr_opts.D.size();
    D.set_size(dim,dim);
    D.zeros();

    for(int i = 0; i < dim;i++){
        D(i,i)      = lwr_opts.D[i];
    }

    D      = arma::inv(D);

    B.set_size(dim);
    mtype = conversion::COL_M;
    ptr_index = NULL;

    I.set_size(dim+1,dim+1);
    I.eye();
    I = I * 1e-05;
}

void LWR::clear(){
    Xq.clear();
    X.clear();
    y.clear();
    Xone.clear();
    yone.clear();

    W.clear();
    B.clear();
    Xy.clear();
    WX.clear();
}

void LWR::print() const{
    lwr_opts.print();
    D.print("D");
    std::cout<< "X:    " << "(" << X.n_rows << " x " << X.n_cols << ")" << std::endl;
    std::cout<< "Xone: " << "(" << Xone.n_rows << " x " << Xone.n_cols << ")" << std::endl;
    std::cout<< "y:    " << "(" << y.n_rows << " x " << y.n_cols << ")" << std::endl;
    std::cout<< "yone: " << "(" << yone.n_rows << " x " << yone.n_cols << ")" << std::endl;
    std::cout<< "threa: " << I(0,0) << std::endl;
}

void LWR::set_X(const arma::mat& X){
    // (D x N)
    this->X = X;
    if(lwr_opts.bUseKDT){
        lwr_flann = LWR_FLANN(this->X,lwr_opts.K);
        // (K+1 x 1)
        W.set_size(K+1);
        WX.set_size(K+1,dim+1);

        // (D+1 x K+1)
        Xone.set_size(dim+1,K+1);
        Xone.row(dim).ones();
    }else{
        // (D+1 x N+1)
        Xone.set_size(X.n_rows+1,X.n_cols+1);
        Xone.row(X.n_rows).ones();
        Xone(arma::span(0,X.n_rows-1),arma::span(0,X.n_cols-1)) = X;

        W.set_size(X.n_cols+1);
        Xy.set_size(X.n_cols+1);
        WX.set_size(X.n_cols+1,dim+1);
    }
}


void LWR::get_X(double *ptr_x){

    std::size_t index = 0;

    for(std::size_t r=0; r < X.n_rows;r++){
        for(std::size_t c=0; c < X.n_cols;c++){
            index  = r +  X.n_rows * c;
            ptr_x[index] =  X(r,c);
        }
    }


}

void LWR::get_Y(double *ptr_y){
    for(std::size_t i=0; i < y.n_elem;i++){
        ptr_y[i] = y(i);
    }
}

void LWR::set_X(const double * const ptr_X, std::size_t num_rows, std::size_t num_cols){
    // (D x N)
    X.set_size(num_rows,num_cols);
    conversion::array2mat(X,ptr_X,num_rows,num_cols,mtype);
    X.print("X");
    set_X(X);
}

void LWR::set_Y(const double * const ptr_Y, std::size_t num_rows){
    y.set_size(num_rows);
    conversion::array2colvec(y,ptr_Y,num_rows);
    set_Y(y);
}

void LWR::set_Y(const arma::colvec& y){
    this->y = y;

    if(lwr_opts.bUseKDT){
        yone.resize(K+1);
        yone.zeros();
        yone(K) = y_bias;
    }else{
        yone.resize(y.n_elem+1);
        yone.zeros();
        yone(arma::span(0,y.n_elem-1)) = y;
        yone(y.n_elem) = y_bias;
    }
}

void LWR::f(double *ptr_y, const arma::mat& Xq){

    if(check_input(Xq)){
        if(lwr_opts.bUseKDT){
            f_flann(ptr_y,Xq);
        }else{
            f_simple(ptr_y,Xq);
        }
    }
}

void LWR::f(double *ptr_y,const double * const ptr_Xq,const std::size_t num_cols){
    // (D x N)
    Xq.resize(dim,num_cols);
    conversion::array2mat(Xq,ptr_Xq,dim,num_cols,mtype);
    f(ptr_y,Xq);
}

bool LWR::check_input(const arma::mat& Xq) const{
    // X must be in format (D x M), rows are dimensions and columns are observations
    if(dim != static_cast<int>(X.n_rows)){
        std::cerr<< "(fail 1) dim != X.n_rows dim[" << dim << "] X.n_rows[" << X.n_rows << "]" << std::endl;
        return false;
    }
    if(dim != static_cast<int>(Xq.n_rows)){
        std::cerr<< "(fail 2) dim[" << dim <<"] != Xq.n_rows[" << Xq.n_rows << "]" << std::endl;
        return false;
    }
    if(lwr_opts.bUseKDT)
    {
        if(static_cast<int>((yone.n_rows)) != K+1)
        {
            std::cerr<< "(fail 3) Yone.n_rows[" << yone.n_rows << "] " << " != K+1 [" << (K+1) << "] " << std::endl;
            return false;
        }
    }
    // number of predictors should match number of inputs
    if(y.n_elem != X.n_cols){
        std::cerr<< "(fail 4) y.n_elem["<< y.n_elem <<"] != X.n_cols[" << X.n_cols << "]" << std::endl;
        return false;
    }
    return true;
}

void LWR::f_simple(double *ptr_y, const arma::mat& Xq){

    arma::mat tmp(dim+1,dim+1);
    tmp.zeros();
    B.set_size(dim+1);

    for(std::size_t i = 0; i < Xq.n_cols;i++){
        W.zeros();
        // #pragma omp parallel for
        for(std::size_t j = 0; j < X.n_cols;j++){
            // (1 x 1) = (1 x D) * (D x D) * (D x 1)
            W(j) = arma::as_scalar((Xq.col(i) - X.col(j)).st() * D * (Xq.col(i) - X.col(j)));
        }

        W = exp(-0.5 * (W % W));

        if(arma::min(W(arma::span(0,W.n_elem-2))) > 0.01){
            W(W.n_elem-1) = 0;
        }else{
            W(W.n_elem-1) = exp(-0.5 * k_bias * arma::sum(W(arma::span(0,W.n_elem-2))));
        }
        // (D+1 x N+1)
        Xone(arma::span(0,dim-1),Xone.n_cols-1) = Xq.col(i);
        for(std::size_t c=0; c < WX.n_cols;c++){
            // (N+1,:) = (N+1 x 1) .* (N+1 x 1);
            WX.col(c) =  W % Xone.row(c).st();
        }
        // (D+1 x 1) =  (D+1 x D+1) (D+1 x N+1)  (N+1 x 1)

        if(!arma::solve(B,Xone * WX + I,Xone * (W % yone))){
            B.zeros();
            B(B.n_elem-1) = 1;
        }

        ptr_y[i] = arma::as_scalar(Xq.col(i).st() * B(arma::span(0,dim-1))) + B(dim);
    }
}

void LWR::f_flann(double *ptr_y, const arma::mat& Xq){

    lwr_flann.ann(Xq);
    // (M x K)
    Matrix<int>&  indices = lwr_flann.indices;

    arma::mat tmp(dim+1,dim+1);
    tmp.zeros();
    B.set_size(dim+1);

    std::size_t num_obs = Xq.n_cols;


    // Xq : (D x M)
    for(std::size_t i = 0; i < num_obs;i++){

        W.zeros();


        for(int j = 0; j < K;j++){
            // std::cout<< "j: " << j << std::endl;
            Xone(arma::span(0,dim-1),j) = X.col(indices[i][j]);
            yone(j)                     = y(indices[i][j]);
            // (1 x 1) = (1 x D) * (D x D) * (D x 1)
            W(j) = arma::as_scalar((Xq.col(i) - X.col(indices[i][j])).st() * D * (Xq.col(i) - X.col(indices[i][j])));
        }
        Xone(arma::span(0,dim-1),K) = Xq.col(i);

        // (K x 1)
        W = exp(-0.5 * (W % W));

        if(arma::min(W(arma::span(0,W.n_elem-2))) > 0.01){
            W(W.n_elem-1) = 0;
        }else{
            W(W.n_elem-1) = exp(-0.5 * k_bias * arma::sum(W(arma::span(0,W.n_elem-2))));
        }
        // (D+1 x K+1)
        for(std::size_t c=0; c < WX.n_cols;c++){
            // (N+1,:) = (N+1 x 1) .* (N+1 x 1);
            WX.col(c) =  W % Xone.row(c).st();
        }

        /*  WX.print("WX");
        Xone.print("Xone");
        W.print("W");
        yone.print("yone");
        (W % yone).print("W*yone");
        (Xone * (W % yone)).print("Xone * (W % yone)");
        (Xone * WX).print("Xone * WX");
        arma::mat tmp = (Xone * WX);*/

        // (D+1 x 1) =  (D+1 x D+1) (D+1 x N+1)  (N+1 x 1)
        //R B = arma::pinv(Xone * WX)  * Xone * (W % yone);


        // std::cout<< "det: " << arma::det(tmp) << std::endl;

        //  I.print("I");
        //  (Xone * WX + I).print("Xone * WX + I");


        //      / arma::inv(Xone * WX + I).print("inv(Xone * WX + I)");

        // tmp = ;
        if(!arma::solve(B,Xone * WX + I,Xone * (W % yone))){
            B.zeros();
            B(B.n_elem-1) = 1;
        }

        /* if(arma::det(tmp) == 0){
            B.zeros();
            B(B.n_elem-1) = 1;
          //  B.print();

        }else{
          //  B = arma::pinv(Xone * WX)  * Xone * (W % yone);
            B = arma::solve(tmp,Xone * (W % yone));
        }*/

        ptr_y[i] = arma::as_scalar(Xq.col(i).st() * B(arma::span(0,dim-1))) + B(dim);

    }

}

void LWR::ann(double *ptr_index, const double * const ptr_Xq, const std::size_t num_cols){
    Xq.resize(dim,num_cols);
    //   std::cout<< "Xq: (" << Xq.n_rows << " x " << Xq.n_cols << ")" << std::endl;
    conversion::array2mat(Xq,ptr_Xq,dim,num_cols,mtype);
    lwr_flann.ann(Xq);
    lwr_flann.get_indicies(ptr_index);
}

void LWR::ann(const arma::mat& Xq){
    // std::cout<< "Xq: (" << Xq.n_rows << " x " << Xq.n_cols << ")" << std::endl;
    lwr_flann.ann(Xq);
}

int LWR::get_K() const{
    return K;
}

void LWR::set_regulisation(double reg){
    I.eye();
    I = I * reg;
}

}
