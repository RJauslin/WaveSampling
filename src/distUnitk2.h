#ifndef distUnitk2_H
#define distUnitk2_H

#include <RcppArmadillo.h>


arma::vec distUnitk2(arma::mat X,
                    int k,
                    bool tore,
                    double toreBound);

#endif
