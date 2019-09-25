
<!-- README.md is generated from README.Rmd. Please edit that file -->

# Weakly associated vectors (wave)

Spatial data are generally autocorrelated, meaning that if two units
selected are close to each other then it is likely that they share the
same properties. For this reason, when sampling in the population it is
often needed that the sample is well spread over space. We propose here
a new way of estimating a sample from a population with spatial
coordinates. This method is called `wave` (weakly associated vectors).
It uses the less correlated vector to a spatial weights matrix **W** to
update the inclusion probabilities vector into a sample **s**.

## Build

[![Build
Status](https://travis-ci.org/RJauslin/wave.svg?branch=master)](https://travis-ci.org/RJauslin/wave)

## Installation

You can install the released version of wave from GitHub

``` r
devtools::install_github("Rjauslin/wave")
```

## Simple example

This is a basic example which shows you how to solve a common problem.
Firtly we need to generate the spatial coordinates. We then create
randomly uniform coordinates from the function `runif()`,

``` r
library(wave)
#> Loading required package: Matrix

N <- 144
n <- 48
X <- cbind(runif(N),runif(N))
head(X,10)
#>            [,1]      [,2]
#>  [1,] 0.4412080 0.9993916
#>  [2,] 0.5913552 0.7192961
#>  [3,] 0.5526881 0.7196404
#>  [4,] 0.0690092 0.6339129
#>  [5,] 0.6303978 0.7880169
#>  [6,] 0.7249935 0.7709820
#>  [7,] 0.5572982 0.6871028
#>  [8,] 0.2608775 0.1282434
#>  [9,] 0.1594454 0.4388582
#> [10,] 0.2089302 0.7922272
```

Now we need the inclusion probabilities `pik`. Hence, we generate a
vector `pik` that have all the same values with the function `rep()`.

``` r
pik <- rep(n/N,times = N)
```

All that is left, is to use the function `wave()`.

``` r
s <- wave(X,pik)
```

We can also generate a plot to see

``` r
library(ggplot2)
ggplot() +
  geom_point(data = data.frame(x = X[,1],y = X[,2]),
             aes(x = x,y = y),
             shape = 1,
             alpha = 0.2)+
  geom_point(data = data.frame(x = X[s == 1,1],y = X[s == 1,2]),
             aes(x,y),
             shape = 16,
             colour = "black")+
  theme_minimal()+
  theme(panel.grid.major = element_blank(),
        panel.grid.minor = element_blank())
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" style="display: block; margin: auto;" />
