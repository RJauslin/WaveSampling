
#include <RcppArmadillo.h>

#include "distUnitk.h"
#include "wpik.h"
#include "rowcolSumsiter.h"
#include "projOp.h"

using namespace std;

// [[Rcpp::depends(RcppArmadillo)]]
//' @title spreadcube implemented in RcppArmadillo
//'
//' @description
//'
//' Same as spreadcube but with RcppArmadillo implementation.
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
arma::vec wave(const arma::mat& X,
               const arma::vec& pik,
               bool tore = true,
               bool jitter = true,
               bool oneD = false,
               bool comment = false) {
  // INITIALIZE CONSTANT
  double la1 = 1e+200;
  double la2 = 1e+200;
  double la = 1e-9;
  double eps = 1e-13;
  int N = X.n_rows;
  double tb = sqrt(N);
  if(oneD == true){
    tb = N;
  }
  
  arma::mat one = arma::ones<arma::mat>(N,1);
  arma::mat Wsp(wpik(X,pik,1.0,tore,jitter,tb).t());
  
  arma::vec re(pik);
  arma::uvec i = arma::find(re > eps && re < (1-eps));
  
  unsigned int i_size = i.size();
  while(i_size > 1){
    
    
    if( comment  == true){
      if(i_size % 10 == 0){
        std::cout << i_size << std::endl;
      }
    }
    
    arma::mat Wsp_tmp(i_size,i_size);
    
    if(sum(re.elem(i)) < 1){
      //It remains only one element and the there is only one stratum
      break;
    }else{
      one = arma::ones<arma::mat>(i_size,1);
      Wsp_tmp = Wsp.submat(i,i);
      arma::mat tmp1 = diagmat(re.elem(i)/pik.elem(i));
      Wsp_tmp = tmp1*Wsp_tmp;
      arma::mat tmp2 = diagmat(1/re.elem(i));
      Wsp_tmp = tmp2*Wsp_tmp;
      Wsp_tmp.insert_cols(0,one);
    }
    
    arma::vec u(i_size);
    
    //QR DECOMPOSTION AND SVD
    arma::mat Q;
    arma::mat R;
    arma::qr(Q,R,Wsp_tmp);
    
    arma::vec di = abs(diagvec(R));
    double max_di = max(di);
    arma::uvec r = find(di >= eps*max_di);
    unsigned int rang = r.size();
    
    if(rang < Wsp_tmp.n_cols){
      // std::cout << "low rank" << std::endl;
      u =  Q.col(Q.n_cols-1);
    }else{
      arma::mat U;
      arma::vec s;
      arma::mat V;
      arma::svd(U, s, V,Wsp_tmp,"dc");
      // U = Q*U;
      u = U.col(U.n_cols - 1);
      u = u - projOp(u,one);
    }
    
    
    //SIMPLE SVD ON Wsp_tmp matrix
    // arma::mat U;
    // arma::vec s
    // arma::mat V;
    //
    // arma::svd(U, s, V, Wsp_tmp,"dc");
    // u = U.col(U.n_cols - 1);
    // u = u - projOp(u,one);
    
    
    la1 = 1e+200;
    la2 = 1e+200;
    la = 1e-9;
    
    for(unsigned int k = 0; k < i.size(); k++){
      if(u[k]> 0){
        la1 = min(la1,(1.0-re[i[k]])/u[k]);
        la2 = min(la2,re[i[k]]/u[k]);
      }
      if(u[k]< 0){
        la1 = min(la1,-re[i[k]]/u[k]);
        la2 = min(la2,(re[i[k]]-1.0)/u[k]);
      }
    }
    if(Rcpp::runif(1)[0]<la2/(la1+la2)){
      la = la1;
    }else{
      la = -la2;
    }
    for(unsigned int k = 0; k < i.size(); k++){
      re[i[k]] = re[i[k]] + la*u[k];
      if(re[i[k]] < eps){
        re[i[k]] = 0;
      }
      if(re[i[k]] > (1-eps)){
        re[i[k]] = 1;
      }
    }
    i = arma::find(re > eps && re < (1-eps));
    i_size = i.size();
  }
  return(re);
  
}



/*** R

rm(list = ls())
  N <- 30
n <- 250
x <- seq(1,N,1)
  y <- seq(1,N,1)
  X <- as.matrix(expand.grid(x,y))
  
  pik <- rep(n/(N*N),N*N)
  
  W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,jitter = T,toreBound = N))
  image(W)
  system.time(test <- spreadcubeArma(as.matrix(X),pik, tore = TRUE,jitter = T))
# utilisateur     système      écoulé
# 54.22        5.75       15.25
  system.time(test2 <- spreadcube(as.matrix(X),pik, tore = TRUE,jitter = T))
# utilisateur     système      écoulé
# 165.92       16.83       49.95
  
  plot(X)
  points(X[test ==1,],pch = 16)
  
##################################################################
  
  N <- 35
  n <- 300
  x <- seq(1,N,1)
    y <- seq(1,N,1)
    X <- as.matrix(expand.grid(x,y))
    
    pik <- rep(n/(N*N),N*N)
    
    W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,jitter = T,toreBound = N))
    image(W)
    system.time(test <- spreadcubeArma(as.matrix(X),pik, tore = TRUE,jitter = T))
    
    
###################################################################
    
    N <- 6
    n <- 13
    x <- seq(1,N,1)
      y <- seq(1,N,1)
      X <- as.matrix(expand.grid(x,y))
      
      pik <- rep(n/(N*N),N*N)
      
      W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,jitter = F,toreBound = N))
      image(W)
      system.time(test <- spreadcubeArma(as.matrix(X),pik, tore = TRUE,jitter = F))
      sum(test)
# utilisateur     système      écoulé
# 8.28        0.79        2.56
      system.time(test2 <- spreadcube(as.matrix(X),pik, tore = TRUE,jitter = F))
      sum(test2)
# utilisateur     système      écoulé
# 4.22        0.07        4.29
      
      
      plot(X)
      points(X[test==1,],pch = 16)
      
      
      W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,jitter = T,toreBound = N))
      image(W)
      W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,jitter = F,toreBound = N))
      image(W)
      
      
      
###################################################################
      
      N <- 6
      n <- 12
      x <- seq(1,N,1)
        y <- seq(1,N,1)
        X <- as.matrix(expand.grid(x,y))
        
        pik <- rep(n/(N*N),N*N)
        
        W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,jitter = F,toreBound = N))
        image(W)
        s <- spreadcubeArma(as.matrix(X),pik, tore = TRUE,jitter =F )
        plot(X)
        points(X[s ==1,],pch = 16)
        
        
        */
