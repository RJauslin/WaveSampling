#ifndef wpik2_H
#define wpik2_H


#include "distUnitk.h"
#include <RcppArmadillo.h>

arma::sp_mat wpik2(arma::mat X,
                  arma::vec pik,
                  bool tore,
                  bool jitter,
                  double toreBound);



#endif
