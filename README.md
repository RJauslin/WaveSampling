
<!-- README.md is generated from README.Rmd. Please edit that file -->

# Weakly Associated Vectors (WAVE) Sampling

Spatial data are generally auto-correlated, meaning that if two units
selected are close to each other, then it is likely that they share the
same properties. For this reason, when sampling in the population it is
often needed that the sample is well spread over space. A new method to
draw a sample from a population with spatial coordinates is proposed.
This method is called `wave` (weakly associated vectors) sampling. It
uses the less correlated vector to a spatial weights matrix to update
the inclusion probabilities vector into a sample. For more details see
Raphaël Jauslin and Yves Tillé (2020)
<https://doi.org/10.1007/s13253-020-00407-1>.

## Installation

### CRAN version

    install.packages("WaveSampling")

### Latest version

You can install the latest version of the package `WaveSampling` with
the following command:

``` r
# install.packages("devtools")
devtools::install_github("Rjauslin/WaveSampling")
```

## Simple example

This basic example shows you how to solve a common problem. Spatial
coordinates from the function `runif()` are firstly generated.

``` r
library(WaveSampling)
#> Le chargement a nécessité le package : Matrix

N <- 144
n <- 48
X <- cbind(runif(N),runif(N))
head(X,10)
#>             [,1]      [,2]
#>  [1,] 0.35000373 0.2557976
#>  [2,] 0.87553309 0.6370745
#>  [3,] 0.09019367 0.9000345
#>  [4,] 0.97906235 0.3576902
#>  [5,] 0.32768335 0.1444912
#>  [6,] 0.41488141 0.5468550
#>  [7,] 0.67789730 0.4799551
#>  [8,] 0.21604234 0.8712608
#>  [9,] 0.38741250 0.6283276
#> [10,] 0.78754375 0.6948966
```

Inclusion probabilities `pik` is set up all equal with the function
`rep()`.

``` r
pik <- rep(n/N,times = N)
```

It only remains to use the function `wave()`,

``` r
s <- wave(X,pik)
```

We can also generate a plot to observe the result.

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
  theme_void()
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="75%" style="display: block; margin: auto;" />
