#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;
using namespace std;

// [[Rcpp::depends(RcppArmadillo)]]
//' @title Squared euclidean distances of the unit k.
//'
//' @description
//' Calculate the squared euclidean distance from the unit \eqn{k} to the other units.
//' 
//'
//' @param X matrix representing the spatial coordinates. 
//' @param k the unit index to be used.
//' @param tore an optional logical value, if we are considering the distance on a tore. See Details.
//' @param toreBound an optional numeric value that specify the length of the tore.
//'
//'
//' @details
//' 
//' Let \eqn{\mathbf{x}_k,\mathbf{x}_l} be the spatial coordinates of the unit \eqn{k,l \in U}. The classical euclidean distance is given by
//' 
//' \deqn{d^2(k,l) = (\mathbf{x}_k - \mathbf{x}_l)^\top (\mathbf{x}_k - \mathbf{x}_l). }
//' 
//' When the points are distributed on a \eqn{N_1 \times N_2} regular grid of \eqn{R^2}.
//' It is possible to consider the units like they were placed on a tore. It can be illustrated by Pac-Man passing through the wall to get away from ghosts. Specifically,
//' we could consider two units on the same column (resp. row) that are on the opposite have a small distance,
//' 
//' \deqn{ d^2_T(k,l) = min( (x_{k_1} - x_{l_1})^2,
//'                       (x_{k_1} + N_1 - x_{l_1})^2,
//'                       (x_{k_1} - N_1 - x_{l_1})^2) +}
//' \deqn{ min( (x_{k_2} - x_{l_2})^2,
//'                       (x_{k_2} + N_2 - x_{l_2})^2,
//'                       (x_{k_2} - N_2 - x_{l_2})^2).}
//'
//' The option \code{toreBound} specify the length of the tore in the case of \eqn{N_1 = N_2 = N}. 
//' It is omitted if the \code{tore} option is equal to \code{FALSE}.
//'
//' @return a vector of length \eqn{N} that contains the distances from the unit \eqn{k} to all other units.
//'
//'
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' 
//' @seealso
//' \code{\link{wpik}}, \code{\link{wave}} and \code{\link[stats]{dist}}.
//'
//' @examples
//' N <- 5
//' x <- seq(1,N,1)
//' X <- as.matrix(expand.grid(x,x))
//' distUnitk(X,k = 2,tore = TRUE,toreBound = 5)
//' distUnitk(X,k = 2,tore = FALSE,toreBound = -1)
//' @export
// [[Rcpp::export]]
arma::vec distUnitk(arma::mat X,
                    int k,
                    bool tore,
                    double toreBound){

  //intializing used variable
  int N = X.n_rows;
  // double r = sqrt(N);

  arma::vec unitkX(N);
  arma::vec unitkY(N);

  arma::vec dist(N);

  unitkX.fill(X((k-1),0));
  unitkY.fill(X((k-1),1));

  if(tore == true){

    arma::vec toreBound_vec(N);
    toreBound_vec.fill(toreBound);

    arma::vec x1 = (unitkX - X.col(0))% (unitkX - X.col(0));
    arma::vec x2 = (unitkX + toreBound_vec - X.col(0))%(unitkX + toreBound_vec - X.col(0));
    arma::vec x3 = (-unitkX + toreBound_vec + X.col(0))%(-unitkX + toreBound_vec + X.col(0));

    arma::vec y1 = (unitkY - X.col(1))%(unitkY - X.col(1));
    arma::vec y2 = (unitkY + toreBound_vec - X.col(1))%(unitkY + toreBound_vec - X.col(1));
    arma::vec y3 = (-unitkY + toreBound_vec + X.col(1))%(-unitkY + toreBound_vec + X.col(1));


    arma::vec d1(N);
    arma::vec d2(N);

    for(int i = 0;i < N; i++){
      d1(i) = min(x1(i),x2(i));
      d1(i) = min(d1(i),x3(i));
      d2(i) = min(y1(i),y2(i));
      d2(i) = min(d2(i),y3(i));
    }

    dist = d1 + d2;

  }else{
    dist = (unitkX - X.col(0))%(unitkX - X.col(0)) + (unitkY - X.col(1))%(unitkY - X.col(1));
  }

  return(dist);
}




/*** R
x <- seq(1,2,1)
y <- seq(1,2,1)
X <- as.matrix(expand.grid(x,y))
distUnitk(X,1,tore = TRUE,toreBound = NA)



N <- 5
x <- seq(1,N,1)
X <- as.matrix(expand.grid(x,x))
distUnitk(X,2,tore = TRUE,toreBound = 5)
distUnitk(X,1,tore = FALSE,toreBound = 5)






 N <- 25
 X <- as.matrix(cbind(runif(N),runif(N),runif(N)))
 distUnitk(X,2,tore = F,toreBound = -1)

*/
