#' Swiss canton boundaries
#' 
#' \code{\link[sf]{sf}} sf object that represent the boundaries of the canton of the Switzerland. 
#' 
#' @format An \code{\link[sf]{sf}} object with 26 rows and 21 variables
#' \itemize{
#'   \item{KTNR}{Canton number.}
#'   \item{KTNAME}{Canton name.}
#'   \item{GRNR}{Region number.}
#'   \item{AREA_HA}{Area of the considered territory.}
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
#'   \item{geometry}{geometry considered}
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
#'   \item{CODE_ISO}{National identification}
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
#'   \item{AREA_HA}{Area of the considered territory.}
#'   \item{E_MIN}{minimum E coordinate of the territory [m] according to MN95.}
#'   \item{E_MAX}{maximum E coordinate of the territory [m] according to MN95.}
#'   \item{N_MIN}{minimum N coordinate of the territory [m] according to MN95.}
#'   \item{N_MAX}{maximum N coordinate of the territory [m] according to MN95.}
#'   \item{E_CNTR}{hectometric coordinate E of the central coordinates according to MN95.}
#'   \item{N_CNTR}{hectometric coordinate N of the central coordinates according to MN95.}
#'   \item{geometry}{geometry considered}
#' }
#' 
#' @source \url{https://www.bfs.admin.ch/bfs/fr/home/services/geostat/geodonnees-statistique-federale/limites-administratives/limites-communales-generalisees.html}
#' @encoding UTF-8  
"Swiss"


#' Swiss commune boundaries
#'
#' \code{\link[sf]{sf}} sf object that represent the boundaries of the Switzerland.
#' 
#' @format A \code{\link[sf]{sf}} object with 2215 rows and 26 variables:
#' \describe{
#'   \item{GMDHISTID}{Identification number of the commune.}
#'   \item{GMDNR}{Commune number.}
#'   \item{GMDNAME}{Commune name.}
#'   \item{BZHISTID}{Identifaction number of the district.}
#'   \item{BZNR}{District number.}
#'   \item{KTNR}{Canton number.}
#'   \item{GRNR}{Region number.}
#'   \item{AREA_HA}{Area of the considered territory.}
#'   \item{E_MIN}{minimum E coordinate of the territory [m] according to MN95.}
#'   \item{E_MAX}{maximum E coordinate of the territory [m] according to MN95.}
#'   \item{N_MIN}{minimum N coordinate of the territory [m] according to MN95.}
#'   \item{N_MAX}{maximum N coordinate of the territory [m] according to MN95.}
#'   \item{E_CNTR}{hectometric coordinate E of the central coordinates according to MN95.}
#'   \item{N_CNTR}{hectometric coordinate N of the central coordinates according to MN95.}  
#'   \item{Z_MIN}{minimum elevation of the territory}
#'   \item{Z_MAX}{maximum elevation of the territory}
#'   \item{Z_AVG}{avergae elecation of the territory}
#'   \item{Z_MED}{median elevation of the territory.}
#'   \item{Z_CNTR}{median elevation of the territory.}
#'   \item{X_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{X_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{X_CNTR}{hectometric coordinate x of the central coordinates according to MN03. }
#'   \item{Y_CNTR}{hectometric coordinate y of the central coordinates according to MN03.}
#'   \item{geometry}{geometry considered}
#' }
#' 
#' @source \url{https://www.bfs.admin.ch/bfs/fr/home/services/geostat/geodonnees-statistique-federale/limites-administratives/limites-communales-generalisees.html}
#' @encoding UTF-8  
"SwissCommune"



#' Swiss region boundaries
#'
#' \code{\link[sf]{sf}} sf object that represent the boundaries of the Switzerland.
#' 
#' @format A \code{\link[sf]{sf}} object with 7 rows and 20 variables:
#' \describe{
#'   \item{GRNR}{Region number.}
#'   \item{GRNAME}{Region name.}
#'   \item{AREA_HA}{Area of the considered territory.}
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
#'   \item{geometry}{geometry considered}
#' }
#' 
#' @source \url{https://www.bfs.admin.ch/bfs/fr/home/services/geostat/geodonnees-statistique-federale/limites-administratives/limites-communales-generalisees.html}
#' @encoding UTF-8  
"SwissRegion"



#' Swiss lakes boundaries
#'
#' \code{\link[sf]{sf}} sf object that represent the boundaries of the Switzerland.
#' 
#' @format A \code{\link[sf]{sf}} object with 23 rows and 16 variables:
#' \describe{
#'   \item{GMDNR}{Commune number.}
#'   \item{GMDNAME}{Commune name.}
#'   \item{SEE_HA}{Area of the lake.}
#'   \item{X_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{X_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MIN}{minimum x coordinate of the territory [m] according to MN03.}
#'   \item{Y_MAX}{maximum x coordinate of the territory [m] according to MN03.}
#'   \item{X_CNTR}{hectometric coordinate x of the central coordinates according to MN03. }
#'   \item{Y_CNTR}{hectometric coordinate y of the central coordinates according to MN03.}
#'   \item{E_MIN}{minimum E coordinate of the territory [m] according to MN95.}
#'   \item{E_MAX}{maximum E coordinate of the territory [m] according to MN95.}
#'   \item{N_MIN}{minimum N coordinate of the territory [m] according to MN95.}
#'   \item{N_MAX}{maximum N coordinate of the territory [m] according to MN95.}
#'   \item{E_CNTR}{hectometric coordinate E of the central coordinates according to MN95.}
#'   \item{N_CNTR}{hectometric coordinate N of the central coordinates according to MN95.}  
#'   \item{geometry}{geometry consiered}
#' }
#' 
#' @source \url{https://www.bfs.admin.ch/bfs/fr/home/services/geostat/geodonnees-statistique-federale/limites-administratives/limites-communales-generalisees.html}
#' @encoding UTF-8  
"SwissLake"




#' Structural statistics of Swiss enterprises
#'
#' 
#' Only Swiss enterprises that have a total employement between 50 and 100.
#' 
#' 
#' @format A data.frame with 9657 rows and 29 variables:
#' \describe{
#'   \item{E_KOORD}{coordinates E according to MN95.}
#'   \item{N_KOORD}{coordinates N according to MN95.}
#'   \item{X_KOORD}{coordinates x according to MN03.}
#'   \item{Y_KOORD}{coordinates y according to MN03.}
#'   \item{RELI}{...}
#'   \item{B1708T}{Total establishement.}
#'   \item{B1708S1}{establishement of sector 1.}
#'   \item{B1708S2}{establishement of sector 2.}
#'   \item{B1708S3}{establishement of sector 3.}
#'   \item{B1708EMPT}{Total employement.}
#'   \item{B1708EMPTS1}{employement of sector 1.}
#'   \item{B1708EMPFS1}{women employee of sector 1.}
#'   \item{B1708EMPMS1}{men employee of sector 1.}
#'   \item{B1708EMPTS2}{employemment of sector 2.}
#'   \item{B1708EMPFS2}{women employee of sector 2.}
#'   \item{B1708EMPMS2}{men employee o sector 2.}
#'   \item{B1708EMPTS3}{employement of sector 3.}
#'   \item{B1708EMPFS3}{women employee of sector 3.}   
#'   \item{B1708EMPMS3}{men employee of sector 3.}
#'   \item{B1708VZAT}{Total equivalent full time employement.}
#'   \item{B1708VZATS1}{equivalent full time employee of sector 1.}
#'   \item{B1708VZAFS1}{equivalent full time women employee of sector 1.}
#'   \item{B1708VZAMS1}{equivalent full time men employee of sector 1.}
#'   \item{B1708VZATS2}{equivalent full time employee of sector 2.}
#'   \item{B1708VZAFS2}{equivalent full time women employee of sector 2.}
#'   \item{B1708VZAMS2}{equivalent full time men employee of sector 2.}
#'   \item{B1708VZATS3}{equivalent full time employee of sector 3.}
#'   \item{B1708VZAFS3}{equivalent full time women employee of sector 3.}
#'   \item{B1708VZAMS3}{equivalent full time men employee of sector 3.}
#' }
#' 
#' @source \url{https://www.bfs.admin.ch/bfs/fr/home/services/geostat/geodonnees-statistique-federale/etablissements-emplois/statistique-structurel-entreprises-statent-depuis-2011.html}
#' @encoding UTF-8  
"STATENT2017"



