#include <lwr/lwr_flann.h>
#include <flann/flann.hpp>

namespace lwr {

LWR_FLANN::LWR_FLANN(){
    ptr_indices=NULL;
    ptr_dists=NULL;
}

LWR_FLANN::LWR_FLANN(const arma::mat& X, int K):
LWR_FLANN(){

    set_data(X);
    this->K = K;
    build_index();

}

void LWR_FLANN::set_data(const arma::mat& X){
    dim = X.n_rows;
    double const *a = X.memptr();
    dataset = flann::Matrix<double>(const_cast<double*>(a),X.n_cols,X.n_rows);
}

void LWR_FLANN::build_index(){


    /*

        flann::AutotunedIndexParams auto_params;
        index_params["checks"] = -1;
        index_params["eps"]    = 0.9;
        index_params["max_neighbors"] = -1;
        index_params["cores"] = 4;*/
  //    index_params["algorithm"] = flann::flann_algorithm_t::FLANN_INDEX_KDTREE;
  //    index_params["trees"]     = 10;

    flann::IndexParams          index_params;
    if(dim <= 3){
        index_params = flann::KDTreeSingleIndexParams();
    }else{
        index_params = flann::KDTreeIndexParams(4);
    }
    index_params["core"] = 4;
    sptr_index =  std::shared_ptr<Index<L2<double> > >(new Index<  L2<double> >(dataset,index_params));
    sptr_index->buildIndex();

}

void LWR_FLANN::ann(const arma::mat& Xq){
    if(sptr_index != NULL){

        if(ptr_indices != NULL){
            delete[] ptr_indices;ptr_indices = NULL;
        }
        if(ptr_dists != NULL){
            delete[] ptr_dists; ptr_dists = NULL;
        }
        double *ptr_query = const_cast<double*>(Xq.memptr());

        Matrix<double>  query(ptr_query,Xq.n_cols,Xq.n_rows);

        ptr_indices = new int[query.rows*K];
        indices     = Matrix<int>(ptr_indices, query.rows, K);

        ptr_dists   = new double[query.rows*K];
        dists       = Matrix<double>(ptr_dists,query.rows, K);

        sptr_index->knnSearch(query,indices,dists,K,flann::SearchParams(128));


    }else{
        std::cout<< "ptr_index is NULL" << std::endl;
    }


}

void LWR_FLANN::get_indicies(double *ptr_indicies){
    std::size_t i = 0;
    for(std::size_t c = 0; c < indices.cols;c++){
        for(std::size_t r = 0; r < indices.rows;r++){
            ptr_indicies[i] = indices[r][c];
            i = i + 1;
        }
    }
}

}
