#' hello
#'
#' @return print hello
#' @export
#'
#' @useDynLib wave, .registration = TRUE
#' @importFrom Rcpp sourceCpp
hello <- function() {
  print("Hello, world!")
}
