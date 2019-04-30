#' hello
#'
#' @return print hello
#' @export
#'
#' @useDynLib Rutilsfunc, .registration = TRUE
#' @importFrom Rcpp sourceCpp
hello <- function() {
  print("Hello, world!")
}
