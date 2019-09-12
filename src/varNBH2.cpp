#include <RcppArmadillo.h>
#include "distUnitk.h"
#include "rowcolSumsiter.h"


// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title Local mean variance estimator
//' 
//' @description
//' 
//' Calculates the varaiance estimator based on the local mean.
//' 
//' @param y vector of size n that represent the variable of interest.
//' @param pik vector of the inclusion probabilites. The length should be equal to n.
//' @param s vector of size n with elements equal to the index of the selected units.
//' @param X coordinates of the sampled units.
//' @param d number of neighbors
//' @details
//' 
//' blablalb
//' 
//' @return An integer the variance estimator
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @references 
//' 
//' Stevens, D. L. Jr. and Olsen, A. R. (2004). Spatially balanced sampling of natural resources.
//' \emph{Journal of the American Statistical Association 99, 262-278}
//' 
//' 
//' 
//' @export
// [[Rcpp::export]]
double varNBH2(arma::vec y,arma::vec pik, arma::uvec s,arma::mat X,int d){
  
  double out = 0.0;
  int n = s.size();
  
  arma::vec tmp(n,arma::fill::zeros);
  
  for(int i = 1; i <= n; i++){ // 1-based loop on the number of unit in the sample
    tmp = distUnitk(X,i,false,0.0);
    arma::vec nearest(tmp);

    // std::cout << nearest << std::endl;
    tmp(i-1) = 1e200;
    arma::uvec idx(d,arma::fill::zeros);
    for(int k = 0; k < d; k++){ // take the d closest number
      idx(k) = arma::index_min(tmp);
      tmp(idx(k)) = 1e200;
    }
    // std::cout << idx << std::endl;
    // std::cout << nearest(idx) << std::endl;
    
    //weights 
    
    
    
    
    double yD = sum(y.elem(idx))/d; // mean the neighborhood
    arma::vec w = (1/nearest(idx))/sum(1/nearest(idx)); // calculates the weights
    out = out + arma::sum(w%pow(y(idx)/pik(idx) - yD,2));
  }
  return(out);
}



/*** R

library(sampling)
library(BalancedSampling)
library(ggplot2)
library(viridis)
library(raster)
library(sampling)
library(sf)
library(spsurvey)

data("STATENT2017_NE")
data("SwissLake")
data("SwissCanton")
data("SwissCommune")



Neuch <- SwissCanton[24,]
Lac <- SwissLake[6,]
Commune <- SwissCommune[which(SwissCommune$KTNR == 24),]


# STATENT2017_NE$B1708T <- STATENT2017_NE$B1708T*0.001
# STATENT2017_NE$B1708EMPT <- STATENT2017_NE$B1708EMPT*0.001

X <- as.matrix(scale(cbind(STATENT2017_NE$E_KOORD,STATENT2017_NE$N_KOORD)))
y <- STATENT2017_NE$B1708EMPT
pik <- inclusionprobabilities(STATENT2017_NE$B1708T,10)

s <- wave(X,pik)
s_lpm1 <- lpm1(pik,X) 

w <- localmean.weight(X[which(s == 1),1],X[which(s == 1),2],pik[which(s == 1)])
localmean.var(y[which(s == 1)],w)

w <- localmean.weight(X[s_lpm1,1],X[s_lpm1,2],pik[s_lpm1])
localmean.var(y[s_lpm1],w)




varNBH2(y[which(s==1)],pik[which(s ==1)],which(s == 1),X[which(s == 1),],d = 4)
varNBH(y[which(s==1)],pik[which(s ==1)],which(s == 1),X[which(s == 1),],d = 4)


*/
