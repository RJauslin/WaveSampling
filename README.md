
<!-- README.md is generated from README.Rmd. Please edit that file -->
Weakly associated vectors (wave)
================================

Spatial data are generally autocorrelated, meaning that if two units selected are close to each other then it is likely that they share the same properties. For this reason, when sampling in the population it is often needed that the sample is well spread over space. We propose here a new way of estimating a sample from a population with spatial coordinates. This method is called `wave` (weakly associated vectors). It uses the less correlated vector to a spatial weights matrix **W** to update the inclusion probabilities vector into a sample **s**.

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
#>             [,1]       [,2]
#>  [1,] 0.68227912 0.66125337
#>  [2,] 0.60308064 0.26901224
#>  [3,] 0.46978951 0.58119987
#>  [4,] 0.01020176 0.37636440
#>  [5,] 0.63209839 0.46655411
#>  [6,] 0.42448259 0.54083879
#>  [7,] 0.05397579 0.03870642
#>  [8,] 0.06605696 0.22945684
#>  [9,] 0.33477765 0.35603929
#> [10,] 0.86097571 0.24232593
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
