#include <RcppArmadillo.h>

// [[Rcpp::depends(RcppArmadillo)]]
//' @title Column sums on sparse matrix.
//'
//' @description
//' Same usage of the function \code{\link[Matrix]{colSums}}.
//'
//' @param x A sparse matrix of class \code{\link[Matrix]{sparseMatrix}}.
//'
//' @details
//' This function is designed to be used for other \code{RcppArmadillo} function inside of the package. Nevertheless it could be used in R.
//' It only loops on the non-zero entries of the sparseMatrix. The function \code{\link[Matrix]{colSums}} should be prefer because is 
//' a little bit faster.
//'
//' @return A numeric vector that represent the sums of the column of x. 
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @seealso
//' \code{\link[Matrix]{colSums}}, \code{\link[Matrix]{rowSums}}.
//' 
//' @examples
//' \dontrun{
//' sp <- rsparsematrix(5000,5000,density = 0.4)
//' system.time(test1 <- Matrix::colSums(sp))
//' system.time(test2 <- colSumsiter(sp))
//' }
//' @export
// [[Rcpp::export]]
arma::vec colSumsiter(const arma::sp_mat& x) {

  int N = x.n_cols;

  // initialise memory for result
  arma::vec result(N);
  result.fill(0.0);

  arma::sp_mat::const_iterator end = x.end();
  //loop only on non-zero entry to sum up the row
  for(arma::sp_mat::const_iterator it = x.begin(); it != end; ++it){
    result[it.col()] = result[it.col()] + *it;
  }
  return result;
}

// [[Rcpp::depends(RcppArmadillo)]]
//' @title Row sums on sparse matrix.
//'
//' @description
//' Same usage of the function \code{\link[Matrix]{rowSums}}.
//'
//' @param x A sparse matrix of class \code{\link[Matrix]{sparseMatrix}}.
//'
//' @details
//' This function is designed to be used for other \code{RcppArmadillo} function inside of the package. Nevertheless it could be used in R.
//' It only loops on the non-zero entries of the sparseMatrix. The function \code{\link[Matrix]{rowSums}} should be prefer because is 
//' a little bit faster.
//'
//' @return A numeric vector that represent the sums of the rows of x. 
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @seealso
//' \code{\link[Matrix]{colSums}}, \code{\link[Matrix]{rowSums}}.
//' 
//' 
//' @examples
//' \dontrun{
//' sp <- rsparsematrix(5000,5000,density = 0.4)
//' system.time(test1 <- Matrix::colSums(sp))
//' system.time(test2 <- colSumsiter(sp))
//' }
//' 
//' @export
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
sp <- rsparsematrix(5000,500,density = 0.4)
system.time(test1 <- Matrix::colSums(sp))
system.time(test2 <- colSumsiter(sp))

system.time(svd(sp))
system.time(svds(sp,NSvals = 1,which = "S"))

system.time(rowSums(sp))
system.time(rowSumsiter(sp))


*/
