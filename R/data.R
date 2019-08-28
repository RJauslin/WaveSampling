#' Swiss canton boundaries
#' 
#' \code{\link[sf]{sf}} sf object that represent the boundaries of the canton of the Switzerland. 
#' 
#' @format An \code{\link[sf]{sf}} object with 26 rows and 21 variables
#' \itemize{
#'   \item{KTNR}{Anonymized Mechanical Turk Worker ID}
#'   \item{KTNAME}{Anonymized Mechanical Turk Worker ID}
#'   \item{GRNR}{Anonymized Mechanical Turk Worker ID}
#'   \item{AREA_HA}{Anonymized Mechanical Turk Worker ID}
#'   \item{X_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{X_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{X_CNTR}{hectometric coordinate x of the central coordinates according to MN03. }
#'   \item{Y_CNTR}{hectometric coordinate y of the central coordinates according to MN03.}
#'   \item{Z_MIN}{minimum elevation of the territory}
#'   \item{Z_MAX}{maximum elevation of the territory}
#'   \item{Z_AVG}{avergae elecation of the territory}
#'   \item{Z_MED}{median elevation of the territory.}
#'   \item{E_MIN}{minimum E coordinate of the territory [m] according to MN95.}
#'   \item{E_MAX}{maximum E coordinate of the territory [m] according to MN95.}
#'   \item{N_MIN}{minimum N coordinate of the territory [m] according to MN95.}
#'   \item{N_MAX}{maximum N coordinate of the territory [m] according to MN95.}
#'   \item{E_CNTR}{hectometric coordinate E of the central coordinates according to MN95.}
#'   \item{N_CNTR}{hectometric coordinate N of the central coordinates according to MN95.}
#'   \item{geometry}{Trial number, from 1..NNN}
#' }
#' @source \url{https://www.bfs.admin.ch/bfs/fr/home/services/geostat/geodonnees-statistique-federale/limites-administratives/limites-communales-generalisees.html}
#' @encoding UTF-8  
"SwissCanton"

#' Swiss country boundaries
#'
#' \code{\link[sf]{sf}} sf object that represent the boundaries of the Switzerland.
#' 
#' @format A \code{\link[sf]{sf}} object with 1 rows and 19 variables:
#' \describe{
#'   \item{CODE_ISO}{...}
#'   \item{X_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{X_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{X_CNTR}{hectometric coordinate x of the central coordinates according to MN03. }
#'   \item{Y_CNTR}{hectometric coordinate y of the central coordinates according to MN03.}
#'   \item{Z_MIN}{minimum elevation of the territory}
#'   \item{Z_MAX}{maximum elevation of the territory}
#'   \item{Z_AVG}{avergae elecation of the territory}
#'   \item{Z_MED}{median elevation of the territory.}
#'   \item{AREA_HA}{Anonymized Mechanical Turk Worker ID}
#'   \item{E_MIN}{minimum E coordinate of the territory [m] according to MN95.}
#'   \item{E_MAX}{maximum E coordinate of the territory [m] according to MN95.}
#'   \item{N_MIN}{minimum N coordinate of the territory [m] according to MN95.}
#'   \item{N_MAX}{maximum N coordinate of the territory [m] according to MN95.}
#'   \item{E_CNTR}{hectometric coordinate E of the central coordinates according to MN95.}
#'   \item{N_CNTR}{hectometric coordinate N of the central coordinates according to MN95.}
#'   \item{geometry}{Trial number, from 1..NNN}
#' }
#' 
#' @source \url{https://www.bfs.admin.ch/bfs/fr/home/services/geostat/geodonnees-statistique-federale/limites-administratives/limites-communales-generalisees.html}
#' @encoding UTF-8  
"Swiss"