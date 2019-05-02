# testSpread.R
#
# Many different comparisons between wave
# and lcube (doubly balanced sampling)
#
# 1) One dimension
# 2) Two dimension on a grid
# 3) Two dimension with a runif dispostion


GRTS = function(p,x,y){
  N = length(p);
  n = round(sum(p));
  index = 1:N;
  s = rep(0,times=N);
  att = data.frame(x=x,y=y,mdcaty=p,ids=index);
  design = list(None=list(panel=c(Panel1=n), seltype="Continuous", caty.n=c("Caty 1"=n), over=0));
  require(spsurvey)
  res=spsurvey::grts(design, DesignID="Site", SiteBegin=1, type.frame="finite",
                     src.frame="att.frame", in.shape=NULL, sp.object=NULL, att.frame=att,
                     id=NULL, xcoord="x", ycoord="y", stratum=NULL, mdcaty="mdcaty", startlev=NULL,
                     maxlev=11, maxtry=1000, shift.grid=TRUE, do.sample=rep(TRUE, length(design)),
                     shapefile=FALSE, prjfilename=NULL, out.shape="sample");
  
  s[res$ids]=1;
  s;
}

######################################## 1D ---- (100 units) sample of 10 ########################################


LOOP_1D <- function(SIM,pik,tore = TRUE){
  
  # sb_sys <- sb_spread <- sb_lcube <- c()
  # IB_sys <- IB_spread <- IB_lcube <- c()
  sb_sys <- sb_spread <- sb_lcube <- sb_lpm1 <- sb_lpm2 <- sb_scps <- c()
  IB_sys <- IB_spread <- IB_lcube <-IB_lpm1 <- IB_lpm2 <- IB_scps <- c()
  IB2_sys <- IB2_spread <- IB2_lcube <- IB2_lpm1 <- IB2_lpm2 <- IB2_scps <-c()
  l <- list()
  for(i in 1:SIM){
    print(i)
    
    # UNEQUAL SYSTEMATIC SAMPLING
    s_sys <- UPsystematic(pik)
    
    # POSITION MATRIX
    X <- as.matrix(cbind(seq(1,N,1),rep(0,N)))
    
    # SPREADING ALGORITHM
    s_spread <- round(wave(X,pik,tore = tore,jitter = F,oneD = TRUE))
    # s_spread <- wave(X,pik,tore = TRUE,jitter = F)
    
    # LOCAL CUBE
    s_lcube_tmp <- BalancedSampling::lcube(pik,X,cbind(pik))
    s_lcube <- rep(0,N)
    s_lcube[s_lcube_tmp] <- 1
    
    # LPM1
    s_lpm1_tmp <- BalancedSampling::lpm1(pik,X)
    s_lpm1 <- rep(0,N)
    s_lpm1[s_lpm1_tmp] <- 1
    
    # LPM2
    s_lpm2_tmp <- BalancedSampling::lpm2(pik,X)
    s_lpm2 <- rep(0,N)
    s_lpm2[s_lpm2_tmp] <- 1
    
    # SCPS
    s_scps_tmp <- BalancedSampling::scps(pik,X)
    s_scps <- rep(0,N)
    s_scps[s_scps_tmp] <- 1
    
    # 1D Voronoi SEEN ON A TORE
    sb_sys[i] <- sb1D(pik,s_sys,tore = tore)
    sb_spread[i] <- sb1D(pik,s_spread,tore = tore)
    sb_lcube[i] <- sb1D(pik,s_lcube,tore = tore)
    sb_lpm1[i] <- sb1D(pik,s_lpm1,tore = tore)
    sb_lpm2[i] <- sb1D(pik,s_lpm2,tore = tore)
    sb_scps[i] <- sb1D(pik,s_scps,tore = tore)
    
    # WEIGHTS MATRIX OF POSITION (SAME FOR ALL SAMPLE)
    W <- wpik(X,pik,bound = 1,tore = tore,jitter = F,toreBound = N)
    W <- W
    W <- W- diag(diag(W))
    
    
    # CALCULATION OF THE SPREADING MEASURE MORAN INDEX
    IB_sys[i] <- IB(W,s_sys)
    IB_spread[i] <- IB(W,s_spread)
    IB_lcube[i] <- IB(W,s_lcube)
    IB_lpm1[i] <- IB(W,s_lpm1)
    IB_lpm2[i] <- IB(W,s_lpm2)
    IB_scps[i] <- IB(W,s_scps)
    
    
    # WEIGHTS MATRIX OF POSITION (SAME FOR ALL SAMPLE)
    W2 <- wpik2(X,pik,tore = tore,jitter = F,toreBound = 0)
    W2 <- W2
    
    # CALCULATION OF THE SPREADING MEASURE MORAN INDEX
    IB2_sys[i] <- IB(W2,s_sys)
    IB2_spread[i] <- IB(W2,s_spread)
    IB2_lcube[i] <- IB(W2,s_lcube)
    IB2_lpm1[i] <- IB(W2,s_lpm1)
    IB2_lpm2[i] <- IB(W2,s_lpm2)
    IB2_scps[i] <- IB(W2,s_scps)
    
    
  }
  l$sb <- c(sys = mean(sb_sys),
            spread = mean(sb_spread),
            lcube = mean(sb_lcube),
            lpm1 = mean(sb_lpm1),
            lpm2 = mean(sb_lpm2),
            scps = mean(sb_scps)
  )
  l$IB <- c(sys = mean(IB_sys),
            spread = mean(IB_spread),
            lcube = mean(IB_lcube),
            lpm1 = mean(IB_lpm1),
            lpm2 = mean(IB_lpm2),
            scps = mean(IB_scps)
  )
  l$IB2 <- c(sys = mean(IB2_sys),
             spread = mean(IB2_spread),
             lcube = mean(IB2_lcube),
             lpm1 = mean(IB2_lpm1),
             lpm2 = mean(IB2_lpm2),
             scps = mean(IB2_scps)
  )
  return(l)
}


# EQUAL INCLUSION PROBABILITIES
N <- 100
n <- 10
pik <- rep(n/N,N)
LOOP_1D(SIM = 1000, pik,tore = TRUE)
# $`sb`
# sys   spread    lcube     lpm1     lpm2     scps
# 0.000000 0.133370 0.641990 0.596385 0.627455 0.422850
#
# $IB
# sys     spread      lcube       lpm1       lpm2       scps
# -1.0000000 -0.8045771 -0.3896662 -0.4063723 -0.3922485 -0.3906255
#
# $IB2
# sys     spread      lcube       lpm1       lpm2       scps
# -1.0000000 -0.7760036 -0.3789822 -0.3949197 -0.3796609 -0.3934527

LOOP_1D(SIM = 1000, pik,tore = FALSE)
# $`sb`
# sys   spread    lcube     lpm1     lpm2     scps
# 0.000000 0.287815 0.658775 0.589840 0.651220 0.412450
#
# $IB
# sys     spread      lcube       lpm1       lpm2       scps
# -1.0000000 -0.6769257 -0.3968178 -0.4246184 -0.4023471 -0.4160222
#
# $IB2
# sys     spread      lcube       lpm1       lpm2       scps
# -1.0000000 -0.6769257 -0.3968178 -0.4246184 -0.4023471 -0.4160222



# UNEQUAL INCLUSION PROBABILITIES
N <- 100
n <- 10
pik <- inclusionprobabilities(runif(N),n)
LOOP_1D(SIM = 1000, pik,tore = TRUE)
# $`sb`
# sys    spread     lcube      lpm1      lpm2      scps
# 0.0706034 0.2803830 0.6731262 0.6128853 0.6808051 0.4108458
#
# $IB
# sys     spread      lcube       lpm1       lpm2       scps
# -0.6748999 -0.5466922 -0.3407922 -0.3621394 -0.3407112 -0.3514949
#
# $IB2
# sys      spread       lcube        lpm1        lpm2        scps
# -0.16433727 -0.14759806 -0.10047146 -0.10948592 -0.09892803 -0.09652563


N <- 100
n <- 10
pik <- inclusionprobabilities(runif(N),n)
LOOP_1D(SIM = 1000, pik,tore = FALSE)
# $`sb`
# sys    spread     lcube      lpm1      lpm2      scps
# 0.3419026 0.6425334 0.8531465 0.8314928 0.8776773 0.5357191
#
# $IB
# sys     spread      lcube       lpm1       lpm2       scps
# -0.6283003 -0.5066279 -0.3335429 -0.3429931 -0.3276795 -0.3270333
#
# $IB2
# sys      spread       lcube        lpm1        lpm2        scps
# -0.12746688 -0.12115129 -0.08407277 -0.09198434 -0.08313763 -0.06687730


######################################## LOOP_grid ########################################

LOOP_grid <- function(SIM,pik,sizeGrid){
  N <- sizeGrid
  x <- seq(1,N,1)
  X <- as.matrix(expand.grid(x,x))
  l <- list()
  sb_spread <- sb_lcube <- sb_lpm1 <- sb_lpm2 <- sb_scps <- c()
  IB_spread <- IB_lcube <-IB_lpm1 <- IB_lpm2 <- IB_scps <- c()
  IB2_spread <- IB2_lcube <- IB2_lpm1 <- IB2_lpm2 <- IB2_scps <-c()
  for(i in 1:SIM){
    print(i)
    # SPREADING ALGORITHM
    s_spread <- round(wave(X,pik,tore = TRUE,jitter = FALSE,oneD = FALSE))
    # s_spread <- wave(X,pik,tore = TRUE,jitter = T)
    s_spread_tmp <- which(s_spread == 1)
    
    # LOCAL CUBE
    s_lcube_tmp <- BalancedSampling::lcube(pik,X,cbind(pik))
    s_lcube <- rep(0,N*N)
    s_lcube[s_lcube_tmp] <- 1
    
    # LPM1
    s_lpm1_tmp <- BalancedSampling::lpm1(pik,X)
    s_lpm1 <- rep(0,N*N)
    s_lpm1[s_lpm1_tmp] <- 1
    
    # LPM2
    s_lpm2_tmp <- BalancedSampling::lpm2(pik,X)
    s_lpm2 <- rep(0,N*N)
    s_lpm2[s_lpm2_tmp] <- 1
    
    # SCPS
    s_scps_tmp <- BalancedSampling::scps(pik,X)
    s_scps <- rep(0,N*N)
    s_scps[s_scps_tmp] <- 1
    
    # 1D Voronoi SEEN ON A TORE
    sb_spread[i] <- BalancedSampling::sb(pik,X,s_spread_tmp)
    sb_lcube[i] <- BalancedSampling::sb(pik,X,s_lcube_tmp)
    sb_lpm1[i] <- BalancedSampling::sb(pik,X,s_lpm1_tmp)
    sb_lpm2[i] <- BalancedSampling::sb(pik,X,s_lpm2_tmp)
    sb_scps[i] <- BalancedSampling::sb(pik,X,s_scps_tmp)
    
    # WEIGHTS MATRIX OF POSITION (SAME FOR ALL SAMPLE)
    W <- wpik(X,pik,bound = 1,tore = TRUE,jitter = FALSE,toreBound = N)
    W <- as.matrix(W)
    W <- W- diag(diag(W))
    
    # CALCULATION OF THE SPREADING MEASURE MORAN INDEX
    IB_spread[i] <- IB(W,s_spread)
    IB_lcube[i] <- IB(W,s_lcube)
    IB_lpm1[i] <- IB(W,s_lpm1)
    IB_lpm2[i] <- IB(W,s_lpm2)
    IB_scps[i] <- IB(W,s_scps)
    
    
    # WEIGHTS MATRIX OF POSITION (SAME FOR ALL SAMPLE)
    W2 <- wpik2(X,pik,tore = TRUE,jitter = FALSE,toreBound = 0)
    W2 <- as.matrix(W2)
    
    # CALCULATION OF THE SPREADING MEASURE MORAN INDEX
    IB2_spread[i] <- IB(W2,s_spread)
    IB2_lcube[i] <- IB(W2,s_lcube)
    IB2_lpm1[i] <- IB(W2,s_lpm1)
    IB2_lpm2[i] <- IB(W2,s_lpm2)
    IB2_scps[i] <- IB(W2,s_scps)
    # IB_grts[i] <- IB(W,s_grts)
    
  }
  l$sb <- c(spread = mean(sb_spread),
            lcube = mean(sb_lcube),
            lpm1 = mean(sb_lpm1),
            lpm2 = mean(sb_lpm2),
            scps = mean(sb_scps))
  l$IB <- c(spread = mean(IB_spread),
            lcube = mean(IB_lcube),
            lpm1 = mean(IB_lpm1),
            lpm2 = mean(IB_lpm2),
            scps = mean(IB_scps))
  l$IB2 <- c(spread = mean(IB2_spread),
             lcube = mean(IB2_lcube),
             lpm1 = mean(IB2_lpm1),
             lpm2 = mean(IB2_lpm2),
             scps = mean(IB2_scps))
  return(l)
}


######################################## GRID 10 x 10 (100 units) sample of 20 ########################################

# EQUAL INCLUSION PROBABILITIES
N <- 10
n <- 20
pik <- rep(n/(N*N),N*N)
LOOP_grid(SIM = 1000,pik,sizeGrid = N)
# $`sb`
# spread      lcube       lpm1       lpm2       scps
# 0.05894818 0.07259813 0.07225354 0.07106823 0.05572078
#
# $IB
# spread      lcube       lpm1       lpm2       scps
# -0.6201205 -0.3383658 -0.3558283 -0.3377767 -0.3938824
#
# $IB2
# spread      lcube       lpm1       lpm2       scps
# -0.6043018 -0.3797972 -0.3991265 -0.3782748 -0.4450558



# UNEQUAL INCLUSION PROBABILITIES
pik <- inclusionprobabilities(runif(N*N),n)
LOOP_grid(SIM = 1000,pik,sizeGrid = N)
# $`sb`
# spread      lcube       lpm1       lpm2       scps
# 0.09658961 0.09025470 0.08761871 0.08906088 0.07153184
#
# $IB
# spread      lcube       lpm1       lpm2       scps
# -0.4875544 -0.3010615 -0.3175753 -0.3021268 -0.3474502
#
# $IB2
# spread       lcube        lpm1        lpm2        scps
# -0.05276424 -0.01490079 -0.01423765 -0.01228553 -0.02700876




######################################## GRID 30 x 30 (900 units) sample of 300 ########################################

# EQUAL INCLUSION PROBABILITIES
N <- 30
n <- 300


pik <- rep(n/(N*N),N*N)
LOOP_grid(SIM = 100,pik,sizeGrid = N)
# $`sb`
# spread      lcube
# 0.01417681 0.05613535
#
# $IB
# spread      lcube
# -0.6451824 -0.2878935

# UNEQUAL INCLUSION PROBABILITIES
pik <- inclusionprobabilities(runif(N*N),n)
LOOP_grid(SIM = 10,pik,sizeGrid = N)
#
# TOO LONG TO DO THIS SIMULATION
#



######################################## LOOP_runif ########################################

LOOP_runif <- function(SIM,pik,sizePop){
  N <- sizePop
  X <- as.matrix(cbind(runif(N),runif(N)))
  l <- list()
  sb_spread <- sb_lcube <- sb_lpm1 <- sb_lpm2 <- sb_scps <-  c()
  IB_spread <- IB_lcube <- IB_lpm1 <- IB_lpm2 <- IB_scps <- c()
  IB2_spread <- IB2_lcube <- IB2_lpm1 <- IB2_lpm2 <- IB2_scps <- c()
  for(i in 1:SIM){
    
    print(i)
    
    # SPREADING ALGORITHM
    s_spread <- round(wave(X,pik,tore = FALSE,jitter = FALSE,oneD = F))
    # s_spread <- wave(X,pik,tore = FALSE,jitter = FALSE)
    s_spread_tmp <- which(s_spread == 1)
    
    #GRTS
    # s_grts <- GRTS(pik,x = X[,1],y = X[,2])
    # S_grts_tmp <- which(s_grts == 1)
    
    # LOCAL CUBE
    s_lcube_tmp <- BalancedSampling::lcube(pik,X,cbind(pik))
    s_lcube <- rep(0,N)
    s_lcube[s_lcube_tmp] <- 1
    
    # LPM1
    s_lpm1_tmp <- BalancedSampling::lpm1(pik,X)
    s_lpm1 <- rep(0,N)
    s_lpm1[s_lpm1_tmp] <- 1
    
    # LPM2
    s_lpm2_tmp <- BalancedSampling::lpm2(pik,X)
    s_lpm2 <- rep(0,N)
    s_lpm2[s_lpm2_tmp] <- 1
    
    # SCPS
    s_scps_tmp <- BalancedSampling::scps(pik,X)
    s_scps <- rep(0,N)
    s_scps[s_scps_tmp] <- 1
    
    
    # 1D Voronoi SEEN ON A TORE
    sb_spread[i] <- BalancedSampling::sb(pik,X,s_spread_tmp)
    sb_lcube[i] <- BalancedSampling::sb(pik,X,s_lcube_tmp)
    sb_lpm1[i] <- BalancedSampling::sb(pik,X,s_lpm1_tmp)
    sb_lpm2[i] <- BalancedSampling::sb(pik,X,s_lpm2_tmp)
    sb_scps[i] <- BalancedSampling::sb(pik,X,s_scps_tmp)
    # sb_grts[i] <- BalancedSampling::sb(pik,X,S_grts_tmp)
    
    # WEIGHTS MATRIX OF POSITION (SAME FOR ALL SAMPLE)
    W <- wpik(X,pik,bound = 1,tore = FALSE,jitter = FALSE,toreBound = 0)
    W <- as.matrix(W)
    W <- W- diag(diag(W))
    
    
    # CALCULATION OF THE SPREADING MEASURE MORAN INDEX
    IB_spread[i] <- IB(W,s_spread)
    IB_lcube[i] <- IB(W,s_lcube)
    IB_lpm1[i] <- IB(W,s_lpm1)
    IB_lpm2[i] <- IB(W,s_lpm2)
    IB_scps[i] <- IB(W,s_scps)
    # IB_grts[i] <- IB(W,s_grts)
    
    # WEIGHTS MATRIX OF POSITION (SAME FOR ALL SAMPLE)
    W2 <- wpik2(X,pik,tore = FALSE,jitter = FALSE,toreBound = 0)
    W2 <- as.matrix(W2)
    
    # CALCULATION OF THE SPREADING MEASURE MORAN INDEX
    IB2_spread[i] <- IB(W2,s_spread)
    IB2_lcube[i] <- IB(W2,s_lcube)
    IB2_lpm1[i] <- IB(W2,s_lpm1)
    IB2_lpm2[i] <- IB(W2,s_lpm2)
    IB2_scps[i] <- IB(W2,s_scps)
    # IB_grts[i] <- IB(W,s_grts)
    
  }
  l$sb <- c(spread = mean(sb_spread),
            lcube = mean(sb_lcube),
            lpm1 = mean(sb_lpm1),
            lpm2 = mean(sb_lpm2),
            scps = mean(sb_scps)
            # grts = mean(sb_grts)
  )
  l$var_sb <- c(spread = sqrt(var(sb_spread))/sqrt(SIM),
                lcube = sqrt(var(sb_lcube))/sqrt(SIM),
                lpm1 = sqrt(var(sb_lpm1))/sqrt(SIM),
                lpm2 = sqrt(var(sb_lpm2))/sqrt(SIM),
                scps = sqrt(var(sb_scps))/sqrt(SIM)
                # grts = mean(sb_grts)
  )
  l$IB <- c(spread = mean(IB_spread),
            lcube = mean(IB_lcube),
            lpm1 = mean(IB_lpm1),
            lpm2 = mean(IB_lpm2),
            scps = mean(IB_scps)
            # grts = mean(IB_grts)
  )
  l$var_IB <- c(spread = var(IB_spread),
                lcube = var(IB_lcube),
                lpm1 = var(IB_lpm1),
                lpm2 = var(IB_lpm2),
                scps = var(IB_scps)
                # grts = mean(IB_grts)
  )
  l$IB2 <- c(spread = mean(IB2_spread),
             lcube = mean(IB2_lcube),
             lpm1 = mean(IB2_lpm1),
             lpm2 = mean(IB2_lpm2),
             scps = mean(IB2_scps)
             # grts = mean(IB_grts)
  )
  l$var_IB2 <- c(spread = mean(IB2_spread),
                 lcube = mean(IB2_lcube),
                 lpm1 = mean(IB2_lpm1),
                 lpm2 = mean(IB2_lpm2),
                 scps = mean(IB2_scps)
                 # grts = mean(IB_grts)
  )
  return(l)
}

######################################## runif (100 units) sample of 20 ########################################

# EQUAL INCLUSION PROBABILITIES
N <- 100
n <- 20
pik <- rep(n/N,N)
LOOP_runif(SIM = 1000,pik,sizePop = N)
# $`sb`
# spread     lcube      lpm1      lpm2      scps
# 0.1139518 0.1332560 0.1237640 0.1328800 0.1322480
#
# $IB
# spread      lcube       lpm1       lpm2       scps
# -0.7165830 -0.4294721 -0.4815187 -0.4351687 -0.4760176
#
# $IB2
# spread      lcube       lpm1       lpm2       scps
# -0.7165830 -0.4294721 -0.4815187 -0.4351687 -0.4760176


# UNEQUAL INCLUSION PROBABILITIES
pik <- inclusionprobabilities(runif(N),n)
LOOP_runif(SIM = 1000,pik,sizePop = N)
# $`sb`
# spread     lcube      lpm1      lpm2      scps
# 0.1633540 0.1522634 0.1491801 0.1481121 0.1503101
#
# $IB
# spread      lcube       lpm1       lpm2       scps
# -0.5858295 -0.3812833 -0.4259018 -0.3874532 -0.3565567
#
# $IB2
# spread      lcube       lpm1       lpm2       scps
# -0.3266465 -0.2488519 -0.2787695 -0.2578710 -0.2295059


######################################## runif 1600 units ########################################

# EQUAL INCLUSION PROBABILITIES
N <- 900
n <- 30
pik <- rep(n/N,N)
LOOP_runif(SIM = 100,pik,sizePop = N)
# $`sb`
# spread     lcube
# 0.1326097 0.1372320
#
# $IB
# spread      lcube
# -0.6911855 -0.4174210

# unequal pik











