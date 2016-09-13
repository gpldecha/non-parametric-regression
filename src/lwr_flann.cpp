#include <lwr/lwr_flann.h>
#include <flann/io/hdf5.h>
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
   // X = X.st();
  //  std::cout<< "set_data" << std::endl;
    dim = X.n_rows;
    double const *a = X.memptr();
    dataset = flann::Matrix<double>(const_cast<double*>(a),X.n_cols,X.n_rows);
   // X = X.st();
   // ptr_X  = &X;
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

   // flann::print_params(index_params);


    sptr_index->buildIndex();
  //  std::cout<< "build_index()" << std::endl;

}

void LWR_FLANN::ann(const arma::mat& Xq){
   // std::cout<< "LWR_FLANN::ann" << std::endl;
    // (D x N)
    // Xq
    if(sptr_index != NULL){


        if(ptr_indices != NULL){
            delete[] ptr_indices;ptr_indices = NULL;
        }
        if(ptr_dists != NULL){
            delete[] ptr_dists; ptr_dists = NULL;
        }

     //   int nn = 3;


      //  double *ptr_X     = X.memptr();
        double *ptr_query = const_cast<double*>(Xq.memptr());

     //   Matrix<double>  dataset(ptr_X,X.n_cols,X.n_rows);
        Matrix<double>  query(ptr_query,Xq.n_cols,Xq.n_rows);

        ptr_indices = new int[query.rows*K];
        indices     = Matrix<int>(ptr_indices, query.rows, K);

        ptr_dists   = new double[query.rows*K];
        dists       = Matrix<double>(ptr_dists,query.rows, K);
/*
        std::cout<< "dataset: (" << dataset.rows << " x " << dataset.cols << ")" << std::endl;
        std::cout<< "query:   (" << query.rows   << " x " << query.cols   << ")" << std::endl;
        std::cout<< "dists:   (" << dists.rows   << " x " << dists.cols   << ")" << std::endl;
        std::cout<< "indices: (" << indices.rows << " x " << indices.cols << ")" << std::endl;
*/

       /* Index<L2<double> > index(dataset, flann::KDTreeIndexParams(4));
        index.buildIndex();

        index.knnSearch(query, indices, dists, K, flann::SearchParams(128));*/


        sptr_index->knnSearch(query,indices,dists,K,flann::SearchParams(128));

        //Xq.print("Xq");

       /* std::cout<< "Print Query" << std::endl;
        for(int i = 0; i < query.rows; i++){
            for(int j = 0; j < query.cols; j++){
                std::cout<< "query[" <<i <<"]["<<j<<"]: " << query[i][j]  << std::endl;
            }
//        }*
       /* std::cout<< " " << std::endl;
        std::cout<< "Print dataset" << std::endl;
        for(int i = 0; i < dataset.rows; i++){
              std::cout<< "dataset("<<i<<"): ";
            for(int j = 0; j < dataset.cols; j++){
                std::cout<< dataset[i][j] << " ";
            }
            std::cout<<std::endl;
        }*/
        //ptr_X->print("ptr_X");

        // do a knn search, using 128 checks
       // sptr_index->knnSearch(query, indices, dists, K, flann::SearchParams());

       /* std::cout<< "distance" <<std::endl;
        for(int i = 0; i < dists.rows;i++){
            for(int j = 0; j < dists.cols; j++){
              std::cout<< "dists["<<i<<"]["<<j<<"]: " << dists[i][j] <<std::endl;
            }
        }*/
      /*  std::cout<< " "<< std::endl;
        std::cout<< " Indicies "<< std::endl;

        for(std::size_t i = 0; i < query.rows;i++){
            std::cout<< "Xq(" << i << ")" << std::endl;
            for(std::size_t j = 0; j < K;j++){
                print_row<double>(dataset,indices[i][j]);
            }
        }
        std::cout<< " "<< std::endl;*/

      /*  for(int i = 0; i < dataset.rows; i++){
              std::cout<< "dataset("<<i<<"): ";
            for(int j = 0; j < dataset.cols; j++){
                std::cout<< dataset[i][j] << " ";
            }
            std::cout<<std::endl;
        }
*/

    }else{
        std::cout<< "ptr_index is NULL" << std::endl;
    }

   // std::cout<< "LWR_FLANN::ann END" << std::endl;

}

void LWR_FLANN::get_indicies(double *ptr_indicies){
 //   std::cout<< "get_indicies (start)" << std::endl;
    std::size_t i = 0;
    for(std::size_t c = 0; c < indices.cols;c++){
        for(std::size_t r = 0; r < indices.rows;r++){
            ptr_indicies[i] = indices[r][c];
            i = i + 1;
        }
    }
   // std::cout<< "get_indicies (end)" << std::endl;

}

}
