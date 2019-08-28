
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
#>            [,1]        [,2]
#>  [1,] 0.4369690 0.006418783
#>  [2,] 0.6435161 0.902777382
#>  [3,] 0.2148230 0.695752177
#>  [4,] 0.4760727 0.060653641
#>  [5,] 0.3702949 0.496840097
#>  [6,] 0.4520309 0.590789186
#>  [7,] 0.2578333 0.054030413
#>  [8,] 0.9668865 0.477932062
#>  [9,] 0.2180042 0.057213888
#> [10,] 0.2380351 0.454214565
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

## Real example

The `wave` package contains

``` r
library(sf)
#> Linking to GEOS 3.6.1, GDAL 2.2.3, PROJ 4.9.3
library(raster)
#> Loading required package: sp
data("STATENT2017")
data("SwissRegion")
data("SwissLake")
```

``` r

R1 <- SwissRegion[1,]
STATENT2017_R1 <- rasterFromXYZ(STATENT2017,
              crs = CRS("+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 +k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel +units=m +no_defs"))
STATENT2017_R1 <- mask(STATENT2017_R1,R1)
STATENT2017_R1  <-  as(STATENT2017_R1,"SpatialPixelsDataFrame")
STATENT2017_R1 <- as.data.frame(STATENT2017_R1)

ggplot() +
  geom_sf(data = R1,fill = "transparent")+
  geom_point(data = STATENT2017_R1,aes(x = x,y = y))+
  theme_light()
```

<img src="man/figures/README-unnamed-chunk-6-1.png" width="100%" />
