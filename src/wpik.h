#ifndef wpik_H
#define wpik_H


#include "distUnitk.h"
#include <RcppArmadillo.h>

arma::sp_mat wpik(arma::mat X,
                  arma::vec pik,
                  double bound = 1.0,
                  bool tore = true,
                  bool jitter = false,
                  double toreBound = NA_REAL);


#endif
