#ifndef wpikInv_H
#define wpikInv_H


#include "distUnitk.h"
#include <RcppArmadillo.h>

arma::sp_mat wpikInv(arma::mat X,
                  arma::vec pik,
                  bool tore,
                  bool jitter,
                  double toreBound);



#endif
