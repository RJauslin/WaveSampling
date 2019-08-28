
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

