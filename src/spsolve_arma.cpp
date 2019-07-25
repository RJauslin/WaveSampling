
#include <RcppArmadillo.h>

// [[Rcpp::depends(RcppArmadillo)]]
//' @export
// [[Rcpp::export]]
arma::vec spsolve_arma(arma::sp_mat A,arma::vec b) {
  arma::vec x = arma::spsolve(A, b,"lapack");
  return x;
}

/*** R


library(MASS)

A <- matrix(c(1,2,0,3,1,2,1,-2,2,4,1,1),nrow = 4,ncol = 4,byrow =TRUE)
kern <- Null(t(A))
A%*%kern[,1]
A_2 <- A[-c(1,2),-c(1,2)]
u_2 <- kern[-c(1,2),1]
b<- A_2%*%kern[-c(1,2),1]
kern_2 <- Null(t(A_2))


# works only for non-singular systems of equations
# solve(A_2, b)

spsolve_arma(as(A_2,"sparseMatrix"),b)

# M-P generalized inverse
giA<- ginv(A_2) #M-P generalized inverse 
giA 
x <- giA%*%b
A_2%*%x
tilde_u_2 <-(u_2 -x)


## TRY WITH 

N <- 25
n <- 5
X <- as.matrix(expand.grid(seq(1,sqrt(N),1),seq(1,sqrt(N),1)))
pik <- rep(n/N,N)
W <- wpik(X,pik,bound = 1,tore = TRUE,toreBound = sqrt(N))


rankMatrix()



*/