#' hello
#'
#' @return print hello
#'
#' @useDynLib wave, .registration = TRUE
#' @importFrom Rcpp sourceCpp
hello <- function() {
  print("Hello, world!")
}
