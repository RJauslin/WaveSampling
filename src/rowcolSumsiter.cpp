
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]


//' @title column sum on sparse matrix
//'
//' @description
//' column sum that iterate only on the non-zero entries of the matrix.
//'
//' @param x A sparse matrix
//'
//' @return column sum of the sparse matrix
//'
//' @export
//'
// [[Rcpp::export]]
arma::vec colSumsiter(const arma::sp_mat& x) {

  int N = x.n_cols;

  // initialise memory for result
  arma::vec result(N);
  result.fill(0.0);

  //loop only on non-zero entry to sum up the row
  for(arma::sp_mat::const_iterator it = x.begin(); it != x.end(); ++it) {
    result[it.col()] = result[it.col()] + *it;
  }
  return result;
}

//' @title row sum on sparse matrix
//'
//' @description
//' row sum that iterate only on the non-zero entries of the matrix.
//'
//' @param x A sparse matrix
//'
//' @return row sum of the sparse matrix
//'
//' @export
//'
// [[Rcpp::export]]
arma::vec rowSumsiter(const arma::sp_mat& x) {
  return colSumsiter(x.t());
}




/*** R
rm(list = ls())
X <- as.matrix(cbind(runif(30),runif(30)))
pik <- rep(1/5,30)
A <- wpik(X,pik,bound = 1,tore = TRUE,jitter = TRUE,toreBound = 0)
# A <- A+ t(A)
image(A)
colSumsiter(A)
colSums(A)

rowSumsiter(A)
rowSums(A)



## A tiny bit slower but we could use this in a c++ code
sp <- rsparsematrix(3000,3000,density = 0.1)
system.time(test1 <- colSums(sp))
system.time(test2 <- colSumsiter(sp))

system.time(svd(sp))
system.time(svds(sp,NSvals = 1,which = "S"))

system.time(rowSums(sp))
system.time(rowSumsiter(sp))


*/
