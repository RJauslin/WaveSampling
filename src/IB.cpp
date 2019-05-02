#include <RcppArmadillo.h>
#include "rowcolSumsiter.h"

// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title Spatial balance based on Moran's I index
//'
//' @description
//'
//' This function implements the spatial balanced based on Moran's I index.
//'
//' @param W A \code{\link[Matrix]{sparseMatrix}} representing the spatial weights. See \code{\link{wpik}}.
//' @param s A numeric vector of 0 and 1 that represent the sample.
//'
//' @return A numeric value that represent the spatial spreading measure. It could be any real value between -1 (spread) and 1 (clustered). 
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @references
//' Tillé, Y., Dickson, M.M., Espa, G., and Guiliani, D. (2018). Measuring the spatial balance of a sample: A new measure based on Moran's I index.
//' \emph{Spatial Statistics}, 23, 182-192. \url{https://doi.org/10.1016/j.spasta.2018.02.001}
//' 
//' @seealso
//' \code{\link{wpik}}
//' 
//' @examples
//' \dontrun{
//'   N <- 100
//'   n <- 20
//'   x <- seq(1,sqrt(N),1)
//'   X <- expand.grid(x,x)
//'   pik <- rep(n/N,N)
//'   W <- wpik(as.matrix(X),pik,bound = 1,tore = TRUE,jitter = FALSE,toreBound = sqrt(N))
//'   W <- W - diag(diag(W))
//'   s <- round(wave(as.matrix(X),pik,tore = TRUE,jitter = TRUE,comment = TRUE))
//'   system.time(I1 <- IB(W,s))
//' 
//'   plot(X)
//'   points(X[s == 1,],pch = 16)
//' }
//' 
//' @export
// [[Rcpp::export]]
double IB(const arma::sp_mat& W,const arma::vec& s){
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


N <- 100
n <- 20
x <- seq(1,sqrt(N),1)
X <- expand.grid(x,x)
pik <- rep(n/N,N)
W <- wpik(as.matrix(X),pik,bound = 1,tore = TRUE,jitter = FALSE,toreBound = sqrt(N))
W <- W - diag(diag(W))
s <- round(wave(as.matrix(X),pik,tore = TRUE,jitter = TRUE,comment = TRUE))

system.time(I1 <- IB(W,s))
plot(X)
points(X[s == 1,],pch = 16)

*/
