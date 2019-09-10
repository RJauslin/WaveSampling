#' Variance estimated by NBH
#'
#' @param y vector of size n that represent the variable of interest.
#' @param pik vector of the inclusion probabilites. The length should be equal to n.
#' @param s vector of size n with elements equal to the index of the selected units.
#' @param X coordinates of the sampled units.
#' @param d number of neighbors
#'
#' @return variance
#' @export
#'
#' @examples
#' \dontrun{
#' y <- y[which(s==1)]
#' pik <- pik[which(s ==1)]
#' X <- X[which(s == 1),]
#' s <- which(s == 1)
#' d = 4
#' }
#' 
varNBH <- function(y,pik,s,X,d = 4){
  
  out <- 0
  eps <- 1e-13
  n <- length(s)
  Y_D <- array(rep(0,n*d),c(n,d))
  D <- array(rep(0,n*d),c(n,d))
  I_D <- array(rep(0,n*d),c(n,d))
  
  for(k in 1:n){
    tmp <- distUnitk(X,k = k,tore = FALSE,toreBound = -1)
    tmp[which(tmp < eps)] <- 1e200 # put 0 value equal to 1e200
    for(j in 1:d){
      D[k,j] <- tmp[which.min(tmp)]
      I_D[k,j] <- which.min(tmp)
      Y_D[k,j] <- y[which.min(tmp)]
      tmp[I_D[k,j]] <- 1e200
    }
  }
  
  m <- rowSums(Y_D)/d
  
  W <- 1/D
  for(l in 1:n){
    W[l,] <- W[l,]/sum(W[l,])
  }
  
  
  for(i in 1:n){
    for(j in 1:d){
      out <- out + W[i,j]*(Y_D[i,j]/pik[I_D[i,j]] - m[i])^2
    }
  }
    
  return(out)
  

}