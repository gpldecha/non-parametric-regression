#ifndef NPR_UTILS_H_
#define NPR_UTILS_H_
#include <armadillo>


class conversion{

public:

   typedef enum{ROW_M,COL_M} major;

   static void array2mat(arma::mat& X,const double * const ptr_X, std::size_t num_rows, std::size_t num_cols,major mtype){

        std::size_t index = 0;
        std::size_t r = 0;
        std::size_t c = 0;

        if(mtype == COL_M){

            for(r=0; r < num_rows;r++){
                for(c=0; c < num_cols;c++){
                    index  = r + num_rows * c;
                    X(r,c) = ptr_X[index];
                }
            }

        }else{
            for(r=0; r < num_rows;r++){
                for(c=0; c < num_cols;c++){
                    index  = c + num_cols * r;
                    X(r,c) = ptr_X[index];
                }
            }
        }

    }

    static void array2colvec(arma::colvec& Y,const double * const ptr_Y, std::size_t num_rows){
        for(std::size_t r=0; r < num_rows;r++){
            Y(r) = ptr_Y[r];
        }
    }

};




#endif










