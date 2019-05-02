
#include <RcppArmadillo.h>
#include "distUnitk.h"

using namespace Rcpp;
using namespace arma;
using namespace std;


// [[Rcpp::depends(RcppArmadillo)]]
//' @title Weights calculated from pik
//'
//' @description
//'
//' The weights are calculated in a way that a unit represents its neighbor till their inclusion probabilities sum to 1.
//' Hence each line represent a strata centered around the unit i and that sum up to 1.
//'
//' @param X A matrix of size N x 2, it should represent the 2D position of the units.
//' @param pik vector of inclusion probabilites.
//' @param bound bound to reached before a new strata is considered. Default is 1.
//' @param tore logical, if we are considering the distance on a tore. Default is TRUE.
//' @param jitter logical, if you would use a jitter perturbation. See Details for more infomrations. Default is FALSE.
//' @param toreBound A numeric value that specify the size of the grid.
//'
//' @return A sparse matrix.
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
pik <- inclusionprobabilities(runif(25),5)
wpik(X,pik) # tore == FALSE so it works
wpik(X,pik, tore = TRUE) # tore == TRUE but no toreBound -> error
wpik(X,pik, tore = TRUE,toreBound = 5) # works
wpik(X,pik, tore = FALSE,jitter = TRUE) # warnings

*/

