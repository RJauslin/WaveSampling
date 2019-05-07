
<!-- README.md is generated from README.Rmd. Please edit that file -->
Weakly associated vectors (wave)
================================

Spatial data are generally autocorrelated, meaning that if two units selected are close to each other then it is likely that they share the same properties. For this reason, when sampling in the population it is often needed that the sample is well spread over space. We propose here a new way of estimating a sample from a population with spatial coordinates. This method is called `wave` (weakly associated vectors). It uses the less correlated vector to a spatial weights matrix **W** to update the inclusion probabilities vector into a sample **s**.

Build
-----

[![Build Status](https://travis-ci.org/RJauslin/wave.svg?branch=master)](https://travis-ci.org/RJauslin/wave)

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
#>             [,1]      [,2]
#>  [1,] 0.77272718 0.1272305
#>  [2,] 0.36064364 0.2240377
#>  [3,] 0.04141306 0.7722833
#>  [4,] 0.45914822 0.3973640
#>  [5,] 0.01196169 0.3691914
#>  [6,] 0.12213017 0.3031989
#>  [7,] 0.47400538 0.7654296
#>  [8,] 0.33051677 0.3954500
#>  [9,] 0.82434073 0.1149623
#> [10,] 0.74333753 0.8552845
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
