
SwissCanton <- read_sf("C:/Users/jauslinr/switchdrive/SwissDATA/ggg_2019-LV95/shp/g1k19.shp")
SwissCanton$KTNAME <- gsub("é","e",SwissCanton$KTNAME)
SwissCanton$KTNAME <- gsub("ü","u",SwissCanton$KTNAME)
SwissCanton$KTNAME <- gsub("è","e",SwissCanton$KTNAME)
SwissCanton$KTNAME <- gsub("â","a",SwissCanton$KTNAME)
SwissCanton$KTNAME <- gsub(" ","",SwissCanton$KTNAME)
usethis::use_data(SwissCanton)


Swiss <- read_sf("C:/Users/jauslinr/switchdrive/SwissDATA/ggg_2019-LV95/shp/g1l19.shp")
usethis::use_data(Swiss)


SwissCommune <- read_sf("C:/Users/jauslinr/switchdrive/SwissDATA/ggg_2019-LV95/shp/g1g19.shp")
SwissCommune$GMDNAME <- gsub("ö","o",SwissCommune$GMDNAME)
SwissCommune$GMDNAME <- gsub("ô","o",SwissCommune$GMDNAME)

SwissCommune$GMDNAME <- gsub("ü","u",SwissCommune$GMDNAME)

SwissCommune$GMDNAME <- gsub("é","e",SwissCommune$GMDNAME)
SwissCommune$GMDNAME <- gsub("è","e",SwissCommune$GMDNAME)
SwissCommune$GMDNAME <- gsub("ê","e",SwissCommune$GMDNAME)
SwissCommune$GMDNAME <- gsub("ë","e",SwissCommune$GMDNAME)

SwissCommune$GMDNAME <- gsub("â","a",SwissCommune$GMDNAME)
SwissCommune$GMDNAME <- gsub("ä","a",SwissCommune$GMDNAME)

SwissCommune$GMDNAME <- gsub(" ","",SwissCommune$GMDNAME)
# SwissCommune$GMDNAME[(grepl("[[:cntrl:]]", stringi::stri_enc_toascii(SwissCommune$GMDNAME)))]
usethis::use_data(SwissCommune)



SwissRegion <- read_sf("C:/Users/jauslinr/switchdrive/SwissDATA/ggg_2019-LV95/shp/g1r19.shp")
SwissRegion$GRNAME <- gsub("é","e",SwissRegion$GRNAME)
SwissRegion$GRNAME <- gsub("ü","u",SwissRegion$GRNAME)
# SwissRegion$GRNAME[(grepl("[[:cntrl:]]", stringi::stri_enc_toascii(SwissRegion$GRNAME)))]
usethis::use_data(SwissRegion)


SwissLake <- read_sf("C:/Users/jauslinr/switchdrive/SwissDATA/ggg_2019-LV95/shp/g1s19.shp")
SwissLake$GMDNAME <- gsub("ü","u",SwissLake$GMDNAME)
SwissLake$GMDNAME <- gsub("é","e",SwissLake$GMDNAME)
SwissLake$GMDNAME <- gsub("è","e",SwissLake$GMDNAME)
SwissLake$GMDNAME <- gsub("â","a",SwissLake$GMDNAME)
SwissLake$GMDNAME <- gsub("ä","a",SwissLake$GMDNAME)
# SwissLake$GMDNAME[(grepl("[[:cntrl:]]", stringi::stri_enc_toascii(SwissLake$GMDNAME)))]
usethis::use_data(SwissLake)



STATENT2017 <- read.csv("C:/Users/jauslinr/switchdrive/SwissDATA/STATENT2017_N08_V190822G.csv")
STATENT2017 <- STATENT2017[which(STATENT2017$B1708EMPT > 50 & STATENT2017$B1708EMPT <= 100 ),]
# STATENT2017 <- STATENT2017[,c(1:4,6,10)]
usethis::use_data(STATENT2017,overwrite = TRUE)



NE <- SwissCanton[24,]
Lac <- SwissLake[6,]
Commune <- SwissCommune[which(SwissCommune$KTNR == 24),]
STATENT2017_NE <- rasterFromXYZ(STATENT2017,
                                   crs = CRS("+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 +k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel +units=m +no_defs"))
STATENT2017_NE <- mask(STATENT2017_NE,NE)
STATENT2017_NE  <-  as(STATENT2017_NE,"SpatialPixelsDataFrame")
STATENT2017_NE <- as.data.frame(STATENT2017_NE)
colnames(STATENT2017_NE) <- c(colnames(STATENT2017)[3:29],colnames(STATENT2017)[1:2])
usethis::use_data(STATENT2017_NE)

