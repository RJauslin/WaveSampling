#include <RcppArmadillo.h>

#include "distUnitk.h"
#include "wpik.h"
#include "rowcolSumsiter.h"
#include "projOp.h"

// [[Rcpp::depends(RcppArmadillo)]]
//' @encoding UTF-8
//' @title Weakly associated vectors sampling
//'
//' @description
//'
//' Select a spread sample from inclusion probabilities using the weakly associated vectors sampling method.  
//'
//' @param X matrix of size \eqn{N} x 2 representing the spatial coordinates. 
//' @param pik vector of the inclusion probabilites. The length should be equal to N.
//' @param bound a scalar representing the bound to reach. See Details. Default is 1.
//' @param tore an optional logical value, if we are considering the distance on a tore. See Details. Default is \code{TRUE}.
//' @param shift an optional logical value, if you would use a shift perturbation. See Details. Default is \code{FALSE}.
//' @param oneD an optional logical value, specifying if we are in one dimension. Default is \code{FALSE}.
//' @param comment an optional logical value, indicating some informations during the execution. Default is \code{FALSE}.
//'
//' @details
//' 
//' The main idea is derived from the cube method (Devill and Tillé, 2004). At each step, the inclusion probabilities vector \code{pik}
//' is randomly modified. This modification is carried out in a direction that best preserves the spreading of the sample.
//' 
//' A stratifcation matrix \eqn{\bf A} is computed from the spatial weights matrix calculated from the function \code{\link{wpik}}.
//' Depending if \eqn{\bf A} is full rank or not, the vector giving the direction is not selected in the same way.
//' 
//' If matrix \eqn{\bf A} is not full rank, a vector that is contained in the right null space is seleced:
//' \deqn{ Null(\bf A) = \{ \bf x \in R^N | \bf A\bf x = \bf 0  \}. }
//' 
//' If matrix \eqn{\bf A} is full rank, we find \eqn{\bf v}, \eqn{\bf u} and \eqn{\sigma } the singular vectors assoctiated to the 
//' smallest singular value of \eqn{\bf A} such that
//' 
//' \deqn{ \bf A\bf v = \sigma \bf u,~~~~ \bf A^\top \bf u = \sigma \bf v.}
//' 
//' Vector \eqn{ \bf v } is then centered to ensure fixed sample size. At each step, inclusion probabilities is modified and at least on component is set to 0 or 1. Matrix \eqn{\bf A } is updated 
//' from the new inclusion probabilities. The whole procedure it repeated until it remains only one component that is not equal to 0 or 1.
//' 
//' For more informations on the options \code{tore} and \code{toreBound}, see \code{\link{distUnitk}}.
//' 
//' For more informations on the option \code{shift}, see \code{\link{wpik}}.
//'
//' @return A vector of size \eqn{N} with elements equal 0 or 1. The value 1 indicates that the unit is selected while the value 0 is for non-chosen unit.
//' 
//' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
//' 
//' @references 
//' Deville, J. C. and Tillé, Y. (2004). Efficient balanced sampling: the cube method. Biometrika, 91(4), 893-912
//' 
//' 
//' @seealso
//' \code{\link{wpik}}, \code{\link{distUnitk}}.
//' 
//' 
//' @examples
//'   N <- 36 # 6 x 6 grid
//'   n <- 12 # number of unit selected
//'   x <- seq(1,sqrt(N),1)
//'   X <- as.matrix(cbind(rep(x,times = sqrt(N)),rep(x,each = sqrt(N))))
//'   pik <- rep(n/N,N)
//'   s <- wave(X,pik, tore = TRUE,shift = FALSE)
//' @export
// [[Rcpp::export]]
arma::vec wave(const arma::mat& X,
               const arma::vec& pik,
               double bound = 1.0,
               bool tore = false,
               bool shift = false,
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
  arma::vec re(pik);
  arma::uvec i = arma::find(re > eps && re < (1-eps));
  
  unsigned int i_size = i.size();
  
  
  //INITIALIZING VARIABLE 
  arma::mat U;
  arma::vec s;
  arma::mat V;
  
  while(i_size > 1){
    if(comment  == true){
      if(i_size % 1 == 0){
        // Rcpp::Rcout << i_size << std::endl;
      }
    }
    
    arma::mat A(i_size,i_size);
    
    if(sum(re.elem(i)) < 1){
      //It remains only one element and the there is only one stratum
      break;
    }else{
      one = arma::ones<arma::mat>(i_size,1);
      // Wsp_tmp = Wsp.submat(i,i);
      // arma::mat tmp1 = diagmat(re.elem(i)/pik.elem(i));
      // Wsp_tmp = tmp1*Wsp_tmp;
      // arma::mat tmp2 = diagmat(1/re.elem(i));
      // Wsp_tmp = tmp2*Wsp_tmp;
      
      // Wsp_tmp = Wsp.submat(i,i);
      // arma::mat tmp2 = diagmat(1/pik.elem(i));
      // Wsp_tmp = tmp2*Wsp_tmp;
      // Wsp_tmp.insert_cols(0,one);
      
      arma::uvec index(2);
      index(0) = 0;
      index(1) = 1;
      A = wpik(X.submat(i,index),re.elem(i),1.0,tore,shift,tb);
      arma::mat D = diagmat(1/re.elem(i));
      A = A*D;
    }
    
    
    
    
    arma::vec u(i_size);
    arma::svd_econ(U,s,V,A,"right","dc");
    // arma::svd(U,s,V,A,"dc");
    arma::uvec r = find(s >= eps);
    unsigned int rang = r.size();
    if(rang < i_size){
      // if(comment  == true){
        // std::cout << "low"<< std::endl;
      // }
        u = V.col(V.n_cols - 1);
    }else{
      // if(comment  == true){
      // std::cout << "high"<< std::endl;
      // }
        u = V.col(V.n_cols - 1);
    }
    
    u = u - projOp(u,one);
    
    la1 = 1e+200;
    la2 = 1e+200;
    la = 1e-9;
    
    for(unsigned int k = 0; k < i.size(); k++){
      if(u[k]> 0){
        la1 = std::min(la1,(1.0-re[i[k]])/u[k]);
        la2 = std::min(la2,re[i[k]]/u[k]);
      }
      if(u[k]< 0){
        la1 = std::min(la1,-re[i[k]]/u[k]);
        la2 = std::min(la2,(re[i[k]]-1.0)/u[k]);
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
  return(arma::round(re));
  
}



/*** R

############# EXAMPLE 1

N <- 36
n <- 18
x <- seq(1,sqrt(N),1)
X <- as.matrix(cbind(rep(x,times = sqrt(N)),rep(x,each = sqrt(N))))
pik <- rep(n/N,N)
s <- wave(X,pik,tore = T,shift =F,comment = TRUE)
s <- wave2(X,pik,tore = T,shift =F,comment = TRUE)
plot(X)
points(X[s == 1,],pch = 16)

X <- as.matrix(cbind(runif(N),runif(N)))
s <- wave2(X,pik,tore = F,shift =F,comment = TRUE)
plot(X)
points(X[s == 1,],pch = 16)


N <- 225
n <- 75
x <- seq(1,sqrt(N),1)
X <- as.matrix(cbind(rep(x,times = sqrt(N)),rep(x,each = sqrt(N))))
pik <- rep(n/N,N)

# W <- wpik(X,pik,bound = 1,tore = TRUE,shift = TRUE,toreBound = 15 )
s <- wave(X,pik,tore = T,shift =T,comment = TRUE)
s <- wave2(X,pik,tore = T,shift =T,comment = TRUE)
plot(X)
points(X[s == 1,],pch = 16)


N <- 225
n <- 75
x <- seq(1,sqrt(N),1)
X <- as.matrix(cbind(rep(x,times = sqrt(N)),rep(x,each = sqrt(N))))
X <- as.matrix(cbind(runif(225),runif(225)))
pik <- rep(n/N,N)
# W <- wpik(X,pik,bound = 1,tore = TRUE,shift = TRUE,toreBound = 15 )
s <- wave(X,pik,tore = T,shift =T,comment = TRUE)
s <- wave2(X,pik,tore = T,shift =T,comment = TRUE)
plot(X)
points(X[s == 1,],pch = 16)

  



N <- 25
n <- 5
x <- seq(1,sqrt(N),1)
X <- as.matrix(cbind(rep(x,times = sqrt(N)),rep(x,each = sqrt(N))))
pik <- rep(n/N,N)
s <- wave(X,pik,tore = TRUE,comment = TRUE)
s <- wave2(X,pik,tore = TRUE,comment = TRUE)
plot(X)
points(X[s == 1,],pch = 16)




rm(list = ls())
N <- 30
n <- 100
x <- seq(1,N,1)
y <- seq(1,N,1)
X <- as.matrix(expand.grid(x,y))

pik <- rep(n/(N*N),N*N)

W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,shift = T,toreBound = N))
image(W)
system.time(test <- wave(as.matrix(X),pik, tore = TRUE,shift = T))

# utilisateur     système      écoulé
# 54.22        5.75       15.25
system.time(test2 <- wave2(as.matrix(X),pik, tore = TRUE,shift = T))
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

W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,shift = T,toreBound = N))
image(W)
system.time(test <- spreadcubeArma(as.matrix(X),pik, tore = TRUE,shift = T))


###################################################################

N <- 6
n <- 13
x <- seq(1,N,1)
y <- seq(1,N,1)
X <- as.matrix(expand.grid(x,y))

pik <- rep(n/(N*N),N*N)

W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,shift = F,toreBound = N))
image(W)
system.time(test <- spreadcubeArma(as.matrix(X),pik, tore = TRUE,shift = F))
sum(test)
# utilisateur     système      écoulé
# 8.28        0.79        2.56
system.time(test2 <- spreadcube(as.matrix(X),pik, tore = TRUE,shift = F))
sum(test2)
# utilisateur     système      écoulé
# 4.22        0.07        4.29


plot(X)
points(X[test==1,],pch = 16)


W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,shift = T,toreBound = N))
image(W)
W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,shift = F,toreBound = N))
image(W)



###################################################################

N <- 12
n <- 48
x <- seq(1,N,1)
y <- seq(1,N,1)
X <- as.matrix(expand.grid(x,y))

pik <- rep(n/(N*N),N*N)

W <- t(wpik(as.matrix(X),pik,bound = 1.0,tore = TRUE,shift = F,toreBound = N))
image(W)
s <- wave(as.matrix(X),pik, tore = TRUE,shift =T )
plot(X)
points(X[s ==1,],pch = 16)


*/
