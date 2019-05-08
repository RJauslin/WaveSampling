
<!-- README.md is generated from README.Rmd. Please edit that file -->
Weakly associated vectors (wave)
================================

Spatial data are generally autocorrelated, meaning that if two units selected are close to each other then it is likely that they share the same properties. For this reason, when sampling in the population it is often needed that the sample is well spread over space. We propose here a new way of estimating a sample from a population with spatial coordinates. This method is called `wave` (weakly associated vectors). It uses the less correlated vector to a spatial weights matrix **W** to update the inclusion probabilities vector into a sample **s**.

Build
-----

[![Build Status](https://travis-ci.org/RJauslin/wave.svg?branch=dev)](https://travis-ci.org/RJauslin/wave)

Installation
------------

You can install the released version of wave from GitHub

``` r
devtools::install_github("Rjauslin/wave")
```

Example
-------

This is a basic example which shows you how to solve a common problem. Firtly we need to generate the spatial coordinates. We then create randomly uniform coordinates from the function `runif()`,

``` r
library(wave)

N <- 144
n <- 48
X <- cbind(runif(N),runif(N))
head(X,10)
#>              [,1]       [,2]
#>  [1,] 0.370233736 0.49139415
#>  [2,] 0.462476614 0.02589734
#>  [3,] 0.500601418 0.78638755
#>  [4,] 0.593611745 0.50969394
#>  [5,] 0.318807278 0.55225442
#>  [6,] 0.657361499 0.83947899
#>  [7,] 0.765701270 0.86200979
#>  [8,] 0.649310778 0.85699039
#>  [9,] 0.282119721 0.61187761
#> [10,] 0.001607468 0.28954726
```

Now we need the inclusion probabilities `pik`. Hence, we generate a vector `pik_equal` that have all the same values with the function `rep()`.

``` r
pik_equal <- rep(n/N,times = N)
```

All that is left, is to use the function `wave()`.

``` r
s_equal <- wave(X,pik_equal)
```

We can also generate a plot to see

``` r
library(ggplot2)
ggplot() +
  geom_point(data = data.frame(x = X[,1],y = X[,2]),
             aes(x = x,y = y),
             pch = 1,
             alpha = 0.2)+
  geom_point(data = data.frame(x = X[s_equal == 1,1],y = X[s_equal == 1,2]),
             aes(x,y),
             colour = "black")+
  theme_light()+
  theme(panel.grid.major = element_blank(),
        panel.grid.minor = element_blank())
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" style="display: block; margin: auto;" />
