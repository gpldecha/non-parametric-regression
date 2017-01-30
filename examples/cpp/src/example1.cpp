#include <iostream>
#include <lwr/lwr.h>

int main(int argc,char** argv)
{


  lwr::LWR Lwr;


  // Generate data
  int num_data          = 200;
  arma::mat         X   = 10 * arma::randu<arma::colvec>(num_data).st();
  arma::colvec      y   = sin(X).st() + 0.2 * arma::randu<arma::colvec>(num_data);


  std::cout<< "X: " << X.n_rows << " x " << X.n_cols << std::endl;

  Lwr.set_X(X);
  Lwr.set_Y(y);

  Lwr.print();

  int num_test = 50;
  arma::mat Xq = arma::linspace<arma::colvec>(0,10,num_test).st();

  arma::colvec yq(num_test);

  Lwr.f(yq.memptr(),Xq);


  yq.print("yq");


  return 0;
}
