#ifndef LWR_OPTIONS_H_
#define LWR_OPTIONS_H_

#include <iostream>
#include <vector>

namespace lwr{


class lwr_options{

public:

    lwr_options(){
        bUseKDT = false;
        D.resize(1);
        D[0]    = 1;
        y_bias  = 0;
        K       = 10;
    }


    void print() const{
        std::cout<< "=== LWR options ==="  << std::endl;
        std::cout<< "dim:     " << D.size()   << std::endl;
        if(bUseKDT){
            std::cout<< "bUseKDT: True" << std::endl;
        }else{
            std::cout<< "bUseKDT: False" << std::endl;
        }
        std::cout<< "y_bias:  " << y_bias  << std::endl;
        std::cout<< "K:       " << K       << std::endl;

    }

    bool                    bUseKDT;
    std::vector<double>     D;
    double                  y_bias;
    int                     K;

};


}

#endif
