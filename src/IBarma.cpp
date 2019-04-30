

#include <RcppArmadillo.h>
#include "rowcolSumsiter.h"

// [[Rcpp::depends(RcppArmadillo)]]
//' @title Spatial balance based on Moran's I index
//'
//' @description
//'
//' This function implements the method from
//'
//' @param W A matrix representing the spatial weights indicating how close is the jth unit to the ith.
//' @param s A numeric vector of 0 and 1 that represent the sample.
//'
//' @return A numeric value that represent the spatial spreading measure.
//' @export
// [[Rcpp::export]]
double IBarma(const arma::sp_mat& W,const arma::vec& s){
  int N = s.size();
  arma::vec wi = rowSumsiter(W);
  // arma::rowvec wi = arma::sum(W,1);
  arma::vec sb(N);
  double tot =0.0;
  for(arma::sp_mat::const_iterator it = W.begin(); it != W.end(); ++it) {
    tot = tot + *it;
  }
  sb.fill(arma::sum(wi%s)/tot);

  arma::vec z = s-sb;
  arma::vec u(N);
  u.fill(1.0);

  arma::mat B;
  B = W.t()*diagmat(1/wi)*W - (W.t()*u)*u.t()*W/tot;

  double num = as_scalar(z.t()*W*z);
  double den1 = as_scalar(z.t()*diagmat(wi)*z);
  double den2 = as_scalar(z.t()*B*z);
  double den = sqrt(den1*den2);

  double I = num/den;
  return I;
}


/*** R


N <- 40
n <- 400
x <- seq(1,N,1)
y <- seq(1,N,1)
X <- expand.grid(x,y)
pik <- rep(n/(N*N),N*N)
W <- wpik(as.matrix(X),pik,bound = 1,tore = T,jitter = F,toreBound = N)
W <- W - diag(diag(W))

s <- spreadcubeArma(as.matrix(X),pik,tore = TRUE,jitter = FALSE,oneD = FALSE,comment = FALSE)

system.time(I1 <- IBarma(W,s))
W <- as.matrix(W)
system.time(I2 <- IB(W,s))


*/
