#' Spatial balance for one dimension sample.
#'
#' @description 
#' 
#' This function implements the one dimension spatial balance suggested by Stevens and Olsen (2004) and implemented by Grafström et al. (2012).
#' We simply replace the Voronoï polygons by intervals.
#' 
#' @param pik vector of the inclusion probabilites. The length should be equal to N.
#' @param s vector of size N with elements equal 0 or 1. The value 1 indicates that the unit is selected while the value 0 is for non-selected unit.
#' @param all an optional logical value, it changes the return value type. Useful to have all the interval Voronoï and for check purpose.
#' @param toreBound An optional numeric value that specify the size of the grid. Default is -1.
#' @param tore an optional logical value, if we are considering the distance on a tore. See \code{\link{distUnitk}} for more details. Default is FALSE.
#'
#' @details
#' Implement the one dimension spatial balance \code{\link[BalancedSampling]{sb}}. For each intervals of the sampling units,
#' it calculates the variance between the sum of the inclusion probabilities and 1.
#' Mathematically this gives,
#' 
#' \deqn{B(s) = \frac{1}{n}\sum_{i \in s}(v_i - 1)^2}
#' where \eqn{v_i} is equal to the sum of the inclusion probabilities of all units in the \eqn{i}th intervals If there is a unit that is exactly a the same distance of two units, the inclusion probabilities is divided
#' by 2.
#' 
#' With the options \code{tore} and \code{toreBound} it is possible to specifiies if the line shoudl be seen as a circle
#'  and so the last unit is close to the first one.
#'
#' @return The one dimension spatial balance of the sample, or a list of interval with the specified inclusion probabilities depending on the option \code{all}.
#' 
#' @author Raphaël Jauslin \email{raphael.jauslin@@unine.ch}
#' 
#' @references 
#' Grafström, A., Lundström, N.L.P. and Schelin, L. (2012). Spatially balanced sampling through the Pivotal method. 
#' \emph{Biometrics}, 68(2), 514-520
#' 
#' 
#' Stevens, D. L. Jr. and Olsen, A. R. (2004). Spatially balanced sampling of natural resources.
#' \emph{Journal of the American Statistical Association 99, 262-278}
#' 
#' @seealso \code{\link[BalancedSampling]{sb}}
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
#' @encoding UTF-8
#' @import Matrix
#' @export
sb1D <- function(pik,s,all = FALSE,tore = FALSE,toreBound = -1){


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
