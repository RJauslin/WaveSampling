#include <RcppArmadillo.h>
#include "projOp.h"

// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title QR arma used in wave
//' @param A matrix
//' @return A list
//' @export
// [[Rcpp::export]]
Rcpp::List QRarma(arma::mat A) {
  arma::mat Q;
  arma::mat R;
  
  arma::qr(Q,R,A);
  
  arma::vec u;
  u =  Q.col(Q.n_cols-1);
  return Rcpp::List::create(Rcpp::Named("u") = u,
                     Rcpp::Named("R") = R,
                     Rcpp::Named("Q") = Q);
                     
}

// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title SVD arma used in wave
//' @param A matrix
//' @return A list
//' @export
// [[Rcpp::export]]
Rcpp::List SVDarma(arma::mat A) {
  arma::mat one = arma::ones<arma::mat>(A.n_cols,1);
  
  arma::mat U;
  arma::vec s;
  arma::mat V;
  arma::svd_econ(U, s, V,A,"left","dc");
  
  return Rcpp::List::create(Rcpp::Named("U") = U);
                           
}



