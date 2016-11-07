#include "gtest/gtest.h"
#include "lwr/lwr.h"


TEST(LWRTest,2DRegression)
{

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



}
