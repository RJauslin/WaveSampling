#' Variance estimated by independant random sampling
#'
#' @param y vector of size N that represent the variable of interest.
#' @param pik vector of the inclusion probabilites. The length should be equal to N.
#' @param s vector of size N with elements equal 0 or 1. The value 1 indicates that the unit is selected while the value 0 is for non-chosen unit.
#'
#' @return variance
#' @export
#'
#' @examples
#' \dontrun{
#' 
#' data("STATENT2017")
#' pik <- sampling::inclusionprobabilities(STATENT2017$B1708T,10)
#' y <- STATENT2017$B1708EMPT
#' X <- as.matrix(scale(STATENT2017[,1:2]))
#' s <- rep(0,length(pik))
#'  s[BalancedSampling::lpm1(pik,X)] <- 1
#' varIRS(y,pik,s)
#' 
#' }
#' 
varIRS <- function(y,pik,s){
  n <- length(s)
  m <- mean(y/pik)
  return((n/(n-1))*sum((y/pik - m)^2))
}