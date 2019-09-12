#' Variance estimated by CP
#'
#' @param y vector of size n that represent the variable of interest.
#' @param pik vector of the inclusion probabilites. The length should be equal to n.
#' @param s vector of size n with elements equal to the index of the selected units.
#'
#' @return variance
#' @export
#'
#' 
varHR <- function(y,pik,s){
  n <- length(s)
  return((n/(n-1))*sum((1-pik)*(y/pik-sum(y*(1-pik)/pik)/sum(1-pik))^2));
}