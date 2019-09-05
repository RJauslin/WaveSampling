
#include <RcppArmadillo.h>
#include "distUnitk.h"

using namespace Rcpp;
using namespace arma;
using namespace std;


// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title Spatial weights from inclusion probabilities
//'
//' @description
//'
//' Spatial weights calculated from inclusion probabilies taking distance between units into account.
//'  
//'
//' @param X matrix of size N x 2 representing the spatial coordinates. 
//' @param pik vector of the inclusion probabilites. The length should be equal to N.
//' @param bound a scalar representing the bound to reach. Default is 1.
//' @param tore an optional logical value, if we are considering the distance on a tore. Default is \code{FALSE}.
//' @param jitter an optional logical value, if you would use a jitter perturbation. See Details for more infomrations. Default is \code{FALSE}.
//' @param toreBound a numeric value that specify the size of the grid. Default is -1.
//' 
//' @details
//' 
//' Spatial weights indicates how the units are close from each others. Hence a large value \eqn{w_{ij}} means that the unit \eqn{i} 
//' is close to the unit \eqn{j}. This function consider that a unit represents its neighbor till their inclusion probabilities
//' sum up to 1.
//' 
//' We define \eqn{H_i} the set of the nearest neighbor of the unit \eqn{i} including \eqn{i} such that the sum of their inclusion
//' probabilities is just greater than 1. Moreover, let \eqn{h_i = card{H_i}}, the number of elements in \eqn{H_i}.
//' The matrix \eqn{\bf W} is then defined as follows,
//' 
//' \deqn{ w_{ij} = \pi_j}
//'  if unit \eqn{j} is in the set of the  \eqn{h_i - 1} nearest neighbor of \eqn{i}.
//' \deqn{ w_{ij} = g_j}
//'  if unit \eqn{j} is the \eqn{h_i} nearest neighbour of \eqn{i}.
//' \deqn{w_{ij} = 0}
//'  otherwise.
//' 
//' where \eqn{g_j = 1- (\sum_{k \in H_i} \pi_k -\pi_j)}. Hence, the \eqn{i}th row of the matrix represents
//' neighborhood or stratum of the unit such that the inclusion probabilities sum up to 1 and
//' the \eqn{i}th column the weights that unit \eqn{i} takes for each stratum. 
//' 
//' The option \code{jitter} will add a small normally distributed perturbation \code{rnorm(0,0.01)} to the coordinates
//' of the centroid of the stratum considered. This could be useful if there are many unit that have the same distances.
//' Indeed, if two units have the same distance and are the last unit before that the bound is reached, then the weights
//' of the both units is updated. If a jitter perturbation is used then all the distance are different and only one unit
//' weight is update such that the bound is reached. 
//' 
//' The jitter perturbation is generated at the beginning of the procedure such that each stratum is shifted by the same perturbation.
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
//' \code{\link{wpikInv}}, \code{\link{distUnitk}}, \code{\link{wave}}.
//' 
//' @examples
//' \dontrun{
//' N <- 5
//' x <- seq(1,N,1)
//' X <- as.matrix(expand.grid(x,x))
//' pik <- sampling::inclusionprobabilities(runif(25),5)
//' W <- wpik(X,pik) # tore == FALSE so it works
//' W <- wpik(X,pik, tore = TRUE) # tore == TRUE but no toreBound -> error
//' W <- wpik(X,pik, tore = TRUE,toreBound = 5) # works
//' W <- wpik(X,pik, tore = FALSE,jitter = TRUE) # warnings
//' }
//' 
//' 
//' @export
// [[Rcpp::export]]
arma::sp_mat wpik(arma::mat X,
                  arma::vec pik,
                  double bound = 1.0,
                  bool tore = false,
                  bool jitter = false,
                  double toreBound = -1.0){

  /*
  * Initializing variable
  */
  int N = X.n_rows;
  double eps(0.0000001); // for zero comparison
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
  if(tore == true && toreBound == -1.0){
    Rcpp::stop("You have set tore == true but you not gave a toreBound" );
  }
  if(tore == false && jitter == true){
    warning("You have set tore == false but you set jitter = TRUE. That might be an error or you know what you are doing :-)." );
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
        d = distUnitk(X,k,false,0.0); //toreBound not used in distUnitk
      }
      // std::cout << d << std::endl;

      X(k-1,0) = tmp1;
      X(k-1,1) = tmp2;
    }else{
      if(tore == true){
        d = distUnitk(X,k,true,toreBound);
      }else{
        d = distUnitk(X,k,false,0.0); //toreBound not used in distUnitk
      }
    }

    /*
    * idx is the stable sort index of the distance.
    * such that d(idx) = 0 1 1 4 4 5 5 ....
    * CAREFUL : index of the distance 0-based.
    */
    arma::uvec idx =  arma::stable_sort_index(d); // sort the distance with exact index even if we have ties
    arma::vec w(N,fill::zeros); // returned vec

    /*
    * check print
    */
    // cout << "BEGIN OF THE CALCULATION" << endl << endl << endl;
    // cout << "Matrix :" << X << endl;
    // cout << "distance" << endl << d << endl;
    // cout << "Index of the element : " << endl <<idx << endl;
    // cout << "d(idx)" << endl << d(idx) << endl;
    // cout << "pik(idx)" << endl << pik(idx) << endl;


    /*
    * calculate cumulative sum and the index
    * of the +1 nearest neighbor such that it
    * sum up to 1.
    * d(idx) == 0 1 1 1 4 4 4 4 5 5 5 5 .....
    */
    double cum = 0.0;
    int j = 0;
    do{
      cum = cum + pik(idx(j));
      j = j + 1;
    }while( (bound - cum) > eps );
    j = j-1; //j represent only the number of element added and so id(j) point to the last element added.




    /*
    * find unit that are at the same distance to the +1 neighbor
    */
    arma::uvec modif = find(d == d(idx(j)));


    /*
    * check print
    */
    // cout << "cum :" << cum << endl;
    // cout << "last added :"<< idx(j) << endl;
    // cout << " j :" << j << endl;
    // cout << "modif" << modif <<endl;

    /*
    * Possibly three things :
    *  1) the element of modif are all inside the neighbors and the bound is exactly reached. (no update)
    *  1) the element of modif are all inside the neighbors and the bound is not reached.
    *  2) the element of modif are all outise the neighbors and the bound is not reached.
    */

    /*
    *  Check if the previous element added is inside modif and that the bound is exactly reached
    */
    // if(find(modif == idx(j-1)).is_empty() == false &&  std::abs(bound - cum) < eps ){
    //
    //   for(int tt = 0;tt <= j; tt++){
    //     w(idx(tt)) = pik(idx(tt));
    //   }
    //
    // }else{

    /* LOWBOUND
    *
    * Decrease the cumulative sum by removing the elements of modif.
    *
    * EDIT : As the distance take the first geometry of the grid.
    *  Normally now there is no need to check if 0-element is inside modif. (It is never the case)
    */
    double lowbound = cum; // initialize bound to cum
    int s = j; // intilize s to j
    arma::uvec tmp = find(modif == idx(0));
    if(tmp.is_empty()==true){ // modif does not contains centroid
      tmp = find(modif == idx(s));
      while(tmp.is_empty() == false){
        lowbound = lowbound - pik(idx(s));
        s = s-1;
        tmp = find(modif == idx(s));
      }
    }
    // if(arma::find(modif == idx(0)).is_empty() == true){
    //   // cout << "idx(0) is not inside modif" << endl;
    //   while(arma::find(modif == idx(s)).is_empty() == false){
    //     lowbound = lowbound - pik(idx(s));
    //     s = s - 1;
    //   }
    // }
    // DEPRECATED
    // else{
    //   cout << "idx(0) is inside modif" << endl;
    //   s = 0;
    //   lowbound = 0.0;
    // }


    /* HIGHBOUND
    *
    * Increase the cumulative sum by adding the elements of modif.
    *
    */
    double cum2 = 0.0;
    unsigned int l = 0;
    do{
      cum2 = cum2 + pik(modif(l));
      l = l+1;
    } while (l < modif.size());
    double highbound = lowbound + cum2;


    /*
    * modif elements are update
    * set weights equal to pik.
    */
    w.elem(modif) = pik.elem(modif)/(highbound-lowbound)*(bound-lowbound);
    for(int tt = 0;tt <= s; tt++){
      w(idx(tt)) = pik(idx(tt));
    }

    /*
    * check print
    */
    // cout <<"lowbound : " <<  lowbound << endl;
    // cout <<"highbound : " << highbound << endl;
    // cout <<" s: " << s << endl;
    // cout << "w :"<< w << endl;
    // }

    /*
    * column major implementation seems to be faster to do like that instead of adding rows.
    */
    W.col(k-1) = w;
  }

  return W.t();

}

/*** R
N <- 5
x <- seq(1,N,1)
X <- as.matrix(expand.grid(x,x))
pik <- sampling::inclusionprobabilities(runif(25),5)
W <- wpik(X,pik) # tore == FALSE so it works
W <- wpik(X,pik, tore = TRUE) # tore == TRUE but no toreBound -> error
W <- wpik(X,pik, tore = TRUE,toreBound = 5) # works
W <- wpik(X,pik, tore = FALSE,jitter = TRUE) # warnings



N <- 5
x <- seq(1,N,1)
X <- as.matrix(expand.grid(x,x))
pik <- seq(from = 0.1,0.9,length.out = 25)
pik <- rep(0.2,25)
W <- wpik(X,pik, tore = TRUE,toreBound = 5) 

rankMatrix(W)



N <- 2048
X <- as.matrix(cbind(runif(N),runif(N)))
pik <- inclusionprobabilities(runif(N),100)
system.time(W <- wpik(X,pik, tore = FALSE))


*/

