
#include <RcppArmadillo.h>
#include "distUnitk.h"

using namespace Rcpp;
using namespace arma;
using namespace std;


// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title Spatial weights from pik
//'
//' @description
//'
//' Spatial weights calculated from inclusion probabilies taking distance between units into account. It is a direct
//' implementation of the spatial weights specified in [Tillé et al., 2018].
//'
//' @param X matrix of size N x 2 representing the spatial coordinates. 
//' @param pik vector of the inclusion probabilites. The length should be equal to N.
//' @param tore an optional logical value, if we are considering the distance on a tore. See \code{\link{distUnitk}}. Default is TRUE.
//' @param jitter an optional logical value, if you would use a jitter perturbation. See Details for more infomrations. Default is FALSE.
//' @param toreBound A numeric value that specify the size of the grid.
//' 
//' @details
//' 
//' Spatial weights indicates how close the units are frome each others. Hence a large value \eqn{w_{ij}} means that the unit \eqn{i} 
//' is close to the unit \eqn{j}. This function consider that if \eqn{i} were selected in the sample drawn from the population then
//' \eqn{i} would represent \eqn{1/\pi_i} units in the population and, as a consequence, it would onl be natural to consider
//' that \eqn{i} has \eqn{k_i = (1/\pi_i -1 )} neighbours in the population. The \eqn{k_i} neighbours can be the nearest 
//' neighbours of \eqn{i} according to the distance. The weights are so calculated as follows,
//' 
//' \deqn{ w_{ij} = 1}
//'  if unit \eqn{j \in N_{\lfloor k_i \rfloor}}.
//' \deqn{ w_{ij} = k_i - \lfloor k_i \rfloor}
//'  if unit j is the \eqn{\lceil k_i \rceil} the nearest neighbour of i.
//' \deqn{w_{ij} = 0}
//'  otherwise.
//' 
//' where \eqn{ \lfloor k_i \rfloor} and \eqn{\lceil k_i \rceil} bet he inferior and the superior integers of \eqn{k_i}.
//' 
//' @return A sparse matrix representing the spatial weights.
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @references 
//' Tillé, Y., Dickson, M.M., Espa, G., and Guiliani, D. (2018). Measuring the spatial balance of a sample: A new measure based on Moran's I index.
//' \emph{Spatial Statistics}, 23, 182-192. \url{https://doi.org/10.1016/j.spasta.2018.02.001}
//' 
//' @seealso
//' \code{\link{wpik2}}, \code{\link{distUnitk}}, \code{\link{wave}}.
//' 
//' @export
// [[Rcpp::export]]
arma::sp_mat wpik2(arma::mat X,
                  arma::vec pik,
                  bool tore,
                  bool jitter,
                  double toreBound){

  /*
  * Initializing variable
  */
  int N = X.n_rows;
  arma::sp_mat W = arma::sp_mat(N,N);

  /*
  * If jiiter is is equal true then we
  *  add a perturbation on the central element of each strata
  *  specified here because we need to ensure that we add the
  *  same perturbation to each points.
  */
  double tb1(0.0);
  double tb2(0.0);
  if(jitter == true){
    tb1 = R::rnorm(0.0, 0.01);
    tb2 = R::rnorm(0.0, 0.01);
  }
  /*
  * Main loop on the row of the Matrix X
  */
  for(int k = 1; k <= N; k++){
    arma::vec d(N);

    /*
    * Choose between the distance
    * -----------------------a tore.
    * --------------- add a jiter.
    */

    if(jitter == true){
      double tmp1 = X(k-1,0);
      double tmp2 = X(k-1,1);
      X(k-1,0) = X(k-1,0) + tb1;
      X(k-1,1) = X(k-1,1) + tb2;
      if(tore == true){
        d = distUnitk(X,k,true,toreBound);
      }else{
        d = distUnitk(X,k,false,toreBound);
      }

      X(k-1,0) = tmp1;
      X(k-1,1) = tmp2;
    }else{
      if(tore == true){
        d = distUnitk(X,k,true,toreBound);
      }else{
        d = distUnitk(X,k,false,toreBound);
      }
    }

    
    /*
    * idx is the stable sort index of the distance.
    * such that d(idx) = 0 1 1 4 4 5 5 ....
    * CAREFUL : index of the distance 0-based.
    */
    // arma::uvec idx =  arma::stable_sort_index(d); // sort the distance with exact index even if we have ties

    arma::uvec d_unique = find_unique(d,true);
    arma::vec d_unique_sorted  = sort(d.elem(d_unique));
    arma::vec w(N,fill::zeros); // returned vec

    double k_i = 1/pik[k-1];
    int k_i_floor = floor(1/pik[k-1]);
    // int k_i_ceil = ceil(1/pik[k-1]);

    arma::uvec modif;
    arma::vec w_tmp(N);
    int tt = 0;
    int nbr_element = 0;
    do{
      w_tmp.fill(0.0);
      // modif = find(d == d[d_unique[tt]]);
      modif = find(d == d_unique_sorted[tt]);
      w.elem(modif) += 1.0;
      w_tmp.elem(modif) +=1.0;
      tt = tt + 1;
      nbr_element += modif.size();
    } while (nbr_element <= k_i_floor && nbr_element < N);

    double modif_value = (k_i-sum(w-w_tmp))/sum(w_tmp);

    w.elem(modif) -= 1.0;
    w.elem(modif) += modif_value;
    w[k-1] = 0.0;

    /*
    * column major implementation seems to be faster to do like that instead of adding rows.
    */
    W.col(k-1) = w;
  }
  return W.t();
}

/*** R

rm(list = ls())

wpik2R <- function(d,pik)
{
  N=length(pik)
  w=array(0,c(N,N))
  for(i in 1:N)
  {
    rr=rank(d[i,],ties.method="min")
    ww=as.integer(rr<=min(ceiling(1/pik[i]),N))
    dec=as.integer(rr==max(rr*ww))
    if(sum(dec)>0)  ww[dec==1]=ww[dec==1]*(1/pik[i]-sum(ww-dec))/sum(dec)
    w[i,]=ww
    diag(w)=0
  }
  w
}

x <- seq(1,5,1)
y <- seq(1,5,1)
X <- as.matrix(expand.grid(x,y))
pik <- rep(0.1352345,25)
d <- array(rep(0,5*5),c(25,25))
for(i in 1:25){
  d[i,] <- distUnitk(X,k =i,tore = TRUE,toreBound = 5)
}

as(wpik2R(d,pik),"sparseMatrix") == wpik2(X,pik = pik,tore = TRUE,jitter = FALSE,toreBound = 5)


X <- cbind(runif(25),runif(25))
pik <- inclusionprobabilities(runif(25),5)
pik[1] <- 0.015345
d <- array(rep(0,5*5),c(25,25))
for(i in 1:25){
  d[i,] <- distUnitk(X,k =i,tore = FALSE,toreBound = 0)
}

as(wpik2R(d,pik), "sparseMatrix") == wpik2(X,pik = pik,tore = FALSE,jitter = FALSE,toreBound = 0)
image(wpik2(X,pik = pik,tore = FALSE,jitter = FALSE,toreBound = 0))




### time

X <- cbind(runif(1000),runif(1000))
pik <- inclusionprobabilities(runif(1000),100)
d <- array(rep(0,1000*1000),c(1000,1000))
for(i in 1:25){
  d[i,] <- distUnitk(X,k =i,tore = FALSE,toreBound = 0)
}
system.time(as(wpik2R(d,pik), "sparseMatrix"))
system.time(wpik2R(d,pik))
system.time(wpik2(X,pik = pik,tore = FALSE,jitter = FALSE,toreBound =0))







*/

