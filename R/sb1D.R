#' Spatial balance for one dimension sample on a tore
#'
#' @param pik vector of inclusion probabilites.
#' @param s vector (with elements 0 and 1) that represent the sample.
#' @param all logical, change the return value. Only useful to have all the interval Voronoï.
#' @param toreBound integer value that represent the modulo grid.
#'
#' @details The toreBound used is equal to N = lenght(pik).
#'
#' @return The spatial balance.
#' @export
#'
#' @examples
#'
#' \dontrun{
#'  pik <- inclusionprobabilities(runif(40),10)
#'  s <- UPsystematic(pik)
#'
#'  X <- cbind(seq(1,40,1),rep(0,40))
#'  s_spread <- round(spreadcube(X,pik,tore = TRUE,jitter = TRUE))
#'
#'  sb1D(pik,s)
#'  sb1D(pik,s_spread)
#'  # BalancedSampling::sb(pik,X,s) # does not work properly with 1D.
#'
#'  plot(X[,1],rep(0.5,length(s)),ylim = c(-0.7,0.7))
#'  points(X[s == 1,1],rep(0.5,length(which(s==1))),pch = 16)
#'  points(X[,1],rep(-0.5,length(s)),ylim = c(-0.7,0.7))
#'  points(X[s_spread == 1,1],rep(-0.5,length(which(s_spread==1))),pch = 16)
#'  t <- 5
#'  while(t <= 40){
#'  abline(v = t,col = "grey")
#'  t = t + 5
#'  }
#'  l <- sb1D(pik,s,all = TRUE)
#'  l_spread <- sb1D(pik,s_spread,all = TRUE)
#'
#'  for(i in 1:length(l)){
#'   points(X[l[[i]][1,],1],rep(0.25,length(l[[i]][1,])) ,col =i)
#'  }
#'  for(i in 1:length(l_spread)){
#'   points(X[l_spread[[i]][1,],1],rep(-0.25,length(l_spread[[i]][1,])) ,col = i)
#'  }
#'
#'  sb1D(pik,s)
#'  sb1D(pik,s_spread)
#'
#'  # Comparison with the IB moran index
#'
#'  W <- wpik(X,pik,bound = 1,tore = TRUE,jitter = TRUE,toreBound = 40)
#'  image(W)
#'  W <- as.matrix(W)
#'  W <- W-diag(diag(W))
#'  IB(W,s)
#'  IB(W,s_spread)
#'
#'
#'  #############################################################################
#'
#'
#'  X <- cbind(seq(1,40,1),rep(0,40))
#'  pik <- inclusionprobabilities(runif(40),10)
#'  s <- round(spreadcubeArma(X,pik,tore = TRUE,jitter = TRUE,oneD = TRUE))
#'  plot(X)
#'  points(X[s == 1,], pch = 16)
#'
#'
#'  sb1D(pik,s,all = TRUE)
#'
#'
#' }
sb1D <- function(pik,s,all = FALSE,tore = TRUE,toreBound){


  s_index <- which(s == 1)
  N <- length(pik)
  if(missing(toreBound)){
    toreBound = N
  }
  di <- array(0,c(length(s_index),N))
  X <- cbind(seq(1,N,1),rep(0,N))

  for(i in 1:length(s_index)){
    if(tore == TRUE){
      di[i,] <- distUnitk(X,s_index[i],tore = TRUE,toreBound = toreBound)
    }else{
      di[i,] <- distUnitk(X,s_index[i],tore = FALSE,toreBound = toreBound)
    }
  }

  l <- list()
  sb <- 0

  for(p in 1:length(s_index)){
    l[[p]] <- numeric()
    prob <- c()
    for(j in 1:N){
      if(any(which(min(di[,j]) == di[,j]) == p)){
        l[[p]] <- c(l[[p]],j)
        dupl <- length(which(min(di[,j]) == di[,j]) == p)
        if(dupl > 1){
          prob <- c(prob,pik[j]/dupl)
        }else{
          prob <- c(prob,pik[j])
        }

      }
    }
    sb = sb + (sum(prob)-1)^2
    l[[p]] <- rbind(l[[p]],prob)
  }


  if(all == FALSE ){
    return(sb)
  }else{
    return(l)
  }

}
