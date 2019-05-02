
#include <RcppArmadillo.h>
#include "rowcolSumsiter.h"

// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title Iterative proportional fitting procedure (IPFP) or raking ratio.
//' 
//' @description
//' Iterative proportional fitting procedure (IPFP) implemented for \code{\link[Matrix]{sparseMatrix}}.
//'
//' @param A A \code{\link[Matrix]{sparseMatrix}}.
//' @param bh A vector representing the row margin.
//' @param bi A vector representing the columm margin.
//' @param maxiter An integer indicating the maximum iterations allowed.
//' @param tol A real value that the error should reach before stoped.
//' @param comment an optional logical value, indicating some informations during the execution. Default is FALSE.
//' 
//' @return the sparse matrix A adjusted.
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @references
//' Tillé, Y. (2019). \emph{Théorie des sondages}. Dunod, 2nd édition
//' 
//' @seealso
//'  \code{\link{IPFPsym}}, \code{\link{wpik}}
//' 
//' @examples
//' \dontrun{
//' X <- as.matrix(cbind(runif(1000),runif(1000)))
//'   pik <- rep(1/5,1000)
//'   A <- wpik(X,pik,bound = 1,tore = FALSE,jitter = FALSE,toreBound = 0.0)
//'   A <- A+t(A)
//'   isSymmetric(A)
//'   
//'   A1 <- IPFP(A,bh = rep(1,nrow(A)),
//'             bi = rep(1,nrow(A)),
//'             maxiter = 1000,
//'             tol = 1e-4,
//'             comment = TRUE)
//'   A2 <- IPFPsym(A,bh = rep(1,nrow(A)),
//'             bi = rep(1,nrow(A)),
//'             maxiter = 4000,
//'             tol = 1e-4,
//'             comment = TRUE) # takes more iterations because the symmetric structure is kept.
//'   rowSums(A1)
//'   rowSums(A2)
//'   colSums(A1)
//'   colSums(A2)
//'   
//'   isSymmetric(A1) # not symmetric
//'   isSymmetric(A2) # symmetric
//' }
//' 
//' @export
// [[Rcpp::export]]
arma::sp_mat IPFP(arma::sp_mat& A,
                  arma::vec bh,
                  arma::vec bi,
                  int maxiter = 300,
                  double tol = 1e-9,
                  bool comment = false) {
  int N = A.n_cols;
  int z = 0;
  double EE = 100.0;
  
  //initalisation
  arma::sp_mat B = A;
  arma::vec bht(N);
  bht.fill(0.0);
  arma::vec bit(N);
  bit.fill(0.0);
  
  bht = rowSumsiter(A);
  
  while(EE > tol && z < maxiter){
    z = z+1;
    // std::cout << z << std::endl;
    for(arma::sp_mat::iterator it = B.begin(); it != B.end(); ++it) {
      *it = (*it)*(bh[it.row()]/bht[it.row()]);
    }
    bit = colSumsiter(B);
    for(arma::sp_mat::iterator it = B.begin(); it != B.end(); ++it) {
      *it = (*it) * (bi[it.col()]/bit[it.col()]);
    }
    bht = rowSumsiter(B);
    EE = sum(abs(bh - bht));
    // std::cout << EE << std::endl;
    
  }
  if(comment == true){
    Rcpp::Rcout << "number of iterations :" << z << std::endl;
  }
  
  return(B);
}



// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title Iterative proportional fitting procedure (IPFP) or raking ratio for symmetric sparse matrix.
//' 
//' @description
//' Iterative proportional fitting procedure (IPFP) implemented for \code{\link[Matrix]{sparseMatrix}}.
//'
//' @param A A \code{\link[Matrix]{sparseMatrix}}.
//' @param bh A vector representing the row margin.
//' @param bi A vector representing the columm margin.
//' @param maxiter An integer indicating the maximum iterations allowed.
//' @param tol A real value that the error should reach before stoped.
//' @param comment an optional logical value, indicating some informations during the execution. Default is FALSE.
//' 
//' @return the sparse matrix A adjusted.
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @references
//' Tillé, Y. (2019). \emph{Théorie des sondages}. Dunod, 2nd édition
//' 
//' @seealso
//' \code{\link{IPFP}}, \code{\link{wpik}}
//' 
//' @examples
//' \dontrun{
//'   X <- as.matrix(cbind(runif(1000),runif(1000)))
//'   pik <- rep(1/5,1000)
//'   A <- wpik(X,pik,bound = 1,tore = FALSE,jitter = FALSE,toreBound = 0.0)
//'   A <- A+t(A)
//'   isSymmetric(A)
//'   
//'   A1 <- IPFP(A,bh = rep(1,nrow(A)),
//'             bi = rep(1,nrow(A)),
//'             maxiter = 1000,
//'             tol = 1e-4,
//'             comment = TRUE)
//'   A2 <- IPFPsym(A,bh = rep(1,nrow(A)),
//'             bi = rep(1,nrow(A)),
//'             maxiter = 4000,
//'             tol = 1e-4,
//'             comment = TRUE) # takes more iterations because the symmetric structure is kept.
//'   rowSums(A1)
//'   rowSums(A2)
//'   colSums(A1)
//'   colSums(A2)
//'   
//'   isSymmetric(A1) # not symmetric
//'   isSymmetric(A2) # symmetric
//' }
//' 
//' @export
// [[Rcpp::export]]
arma::sp_mat IPFPsym(arma::sp_mat& A,
                     arma::vec bh,
                     arma::vec bi,
                     int maxiter = 300,
                     double tol = 1e-9,
                     bool comment = false) {
  int N = A.n_cols;
  int z = 0;
  double EE = 100.0;
  
  //initalisation
  arma::sp_mat B = A;
  arma::vec bht(N);
  bht.fill(0.0);
  arma::vec bit(N);
  bit.fill(0.0);
  
  bht = rowSumsiter(A);
  bit = colSumsiter(A);
  
  double total = sum(bh); // target all sum
  double total_tmp =  arma::accu(B); // current all sum
  
  while(EE > tol && z < maxiter){
    z = z+1;
    
    for(arma::sp_mat::iterator it = B.begin(); it != B.end(); ++it) {
      *it = (*it)* ( (bh[it.row()]/bht[it.row()])*(bi[it.col()]/bit[it.col()]) );
    }
    
    total_tmp = accu(B);
    
    for(arma::sp_mat::iterator it = B.begin(); it != B.end(); ++it) {
      *it = (*it) * (total/total_tmp);
    }
    bht = rowSumsiter(B);
    bit = colSumsiter(B);
    
    EE = sum(abs(bh - bht));
    // std::cout << EE << std::endl;
    
  }
  if(comment == true){
    Rcpp::Rcout << "number of iterations :" << z << std::endl;
  }
  
  return(B);
}


/*** R

X <- as.matrix(cbind(runif(1000),runif(1000)))
pik <- rep(1/5,1000)
A <- wpik(X,pik,bound = 1,tore = FALSE,jitter = FALSE,toreBound = 0.0)
A <- A+t(A)
isSymmetric(A)

A1 <- IPFP(A,bh = rep(1,nrow(A)),bi = rep(1,nrow(A)),
           maxiter = 10000,
           tol = 1e-4,
           comment = TRUE)
A2 <- IPFPsym(A,bh = rep(1,nrow(A)),
              bi = rep(1,nrow(A)),
              maxiter = 10000,
              tol = 1e-4,
              comment = TRUE) # takes more iterations because the symmetric structure is kept.
rowSums(A1)
rowSums(A2)
colSums(A1)
colSums(A2)

isSymmetric(A1) # not symmetric
isSymmetric(A2) # symmetric


*/
