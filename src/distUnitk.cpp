#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;
using namespace std;

// [[Rcpp::depends(RcppArmadillo)]]
//' @title Euclidean distance with tore option
//'
//' @description
//' Calculate the distance from the unit k to the other units.
//'
//'
//' @param X A matrix of size N x 2, it should represent the 2D position of the units.
//' @param k An integer value, the index of the unit.
//' @param tore logical, if we are considering the distance on a tore. Default is TRUE.
//' @param toreBound A numeric value that specify the size of the grid.
//'
//' @return A vector that represent the distance values.
//'
//'
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
distUnitk(X,2,tore = TRUE,toreBound = 7)


*/
