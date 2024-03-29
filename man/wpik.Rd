% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\encoding{UTF-8}
\name{wpik}
\alias{wpik}
\title{Stratification matrix from inclusion probabilities}
\usage{
wpik(X, pik, bound = 1, tore = FALSE, shift = FALSE, toreBound = -1)
}
\arguments{
\item{X}{matrix representing the spatial coordinates.}

\item{pik}{vector of the inclusion probabilities. The length should be equal to \eqn{N}.}

\item{bound}{a scalar representing the bound to reach. Default is 1.}

\item{tore}{an optional logical value, if we are considering the distance on a tore. Default is \code{FALSE}.}

\item{shift}{an optional logical value, if you would use a shift perturbation. See Details for more informations. Default is \code{FALSE}.}

\item{toreBound}{a numeric value that specify the size of the grid. Default is -1.}
}
\value{
A sparse matrix representing the spatial weights.
}
\description{
The stratification matrix is calculated from the inclusion probabilities. It takes the distances between units into account. See Details.
}
\details{
Entries of the stratification matrix indicates how the units are close from each others. Hence a large value \eqn{w_{kl}} means that the unit \eqn{k} 
is close to the unit \eqn{l}. This function considers that a unit represents its neighbor till their inclusion probabilities
sum up to \code{bound}.

We define \eqn{G_k} the set of the nearest neighbor of the unit \eqn{k} including \eqn{k} such that the sum of their inclusion
probabilities is just greater than \code{bound}. Moreover, let \eqn{g_k = \#{G_k}}, the number of elements in \eqn{G_k}.
The matrix \eqn{\bf W} is then defined as follows,
\itemize{
  \item \eqn{ w_{kl} = \pi_l} if unit \eqn{l} is in the set of the  \eqn{g_k - 1} nearest neighbor of \eqn{k}.
  \item \eqn{ w_{kl} = \pi_l + 1 - (\sum_{t \in G_k} \pi_t)} if unit \eqn{l} is the \eqn{g_k} nearest neighbour of \eqn{k}.
  \item \eqn{w_{kl} = 0} otherwise.
}


Hence, the \eqn{k}th row of the matrix represents
neighborhood or stratum of the unit such that the inclusion probabilities sum up to 1 and
the \eqn{k}th column the weights that unit \eqn{k} takes for each stratum. 

The option \code{shift} add a small normally distributed perturbation \code{rnorm(0,0.01)} to the coordinates
of the centroid of the stratum considered. This could be useful if there are many unit that have the same distances.
Indeed, if two units have the same distance and are the last unit before that the bound is reached, then the weights
of the both units is updated. If a shift perturbation is used then all the distances are differents and only one unit
weight is update such that the bound is reached. 

The shift perturbation is generated at the beginning of the procedure such that each stratum is shifted by the same perturbation.
}
\examples{

N <- 25
n <- 5
X <- as.matrix(cbind(runif(N),runif(N)))
pik <- rep(n/N,N)
W <- wpik(X,pik)

}
\seealso{
\code{\link{wpikInv}}, \code{\link{distUnitk}}, \code{\link{wave}}.
}
\author{
Raphaël Jauslin \email{raphael.jauslin@unine.ch}
}
