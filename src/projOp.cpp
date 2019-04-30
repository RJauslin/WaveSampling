
#include <RcppArmadillo.h>

// [[Rcpp::depends(RcppArmadillo)]]
//' @title Projection operator
//'
//' @description
//'
//' This operator projects the vector v orthogonally onto the line spanned by vector u.
//'
//'
//' @param v vector that is projected.
//' @parma u vector on which we project.
//'
//' @return The projection of the vector v onto the line spanned by the vector u.
//' @export
// [[Rcpp::export]]
arma::vec projOp(arma::vec v,arma::vec u) {
  double num = arma::as_scalar(u.t()*v);
  double den = arma::as_scalar(u.t()*u);
  arma::vec scalar(u.size());
  scalar.fill(num/den);
  return scalar%u;
}

/*** R

u = c(0,1)
v = c(1,1)
v- projOp(v,u)

v - proj_v_on_u(v,u)
*/
