#' Strongly spread cube method
#'
#' Find a strongly spread sample of a given population of size N.
#'
#' @param X A matrix of size N x 2, it should represent the 2D position of the units.
#' @param pik vector of inclusion probabilites.
#' @param tore  logical, if we are considering the distance on a tore. Default is TRUE.
#' @param jitter logical, if you would use a jitter perturbation. See Details for more infomrations. Default is FALSE.
#'
#' @return A numeric vector (with elements 0 and 1) of size N, the population size. 1 if it is in the sample and 0 otherwise.
#' @export
#'
#' @examples
#' \dontrun{
#'
#'
#'
#' #### Example with 6x6 grid (36 units)
#'
#' N <- 6
#' n <- 18
#' x <- seq(1,N,1)
#' y <- seq(1,N,1)
#' X <- as.matrix(expand.grid(x,y))
#' pik <- rep(n/(N*N),N*N)
#' s <- waveR(as.matrix(X),pik,tore = TRUE,jitter = FALSE)
#' plot(X)
#' points(X[s == 1,],pch = 16)
#' }
waveR <- function(X, pik, tore = TRUE,jitter = FALSE){
  

  eps = 1e-9
  
  #### INITIALIZE toreBound
  #  specify the case where we are in
  #  1D and all the coordinates y == 0
  tb = sqrt(nrow(X))
  if(any(colSums(X) == 0)){
    tb = nrow(X)
  }
  
  tore = FALSE
  jitter = FALSE
  Wsp_begin <- Matrix::t(wpik(X,
                        pik,
                        bound = 1.0,
                        tore = tore,
                        jitter = jitter,
                        toreBound = tb))

  
  mesh <- 5
  indexmesh <- 1
  
  for(n in 1:6){
    Wsp <- Wsp_begin[,indexmesh:(indexmesh + mesh)]  
    indexmesh <- indexmesh + 6
    
    
    re  <- pik[indexmesh:(indexmesh + mesh)]
    i <- which(re > eps & re < (1-eps))
    
    while(length(i) > 1){
      
      
      if(sum(re[i])< 1){
        break;
      }else{
        
        
        #### REWEIGHTING THE ORIGINAL MATRIX TO THE CURRENT "re" INCLUSION PROBABILITIES
        Wsp_tmp <- Wsp[,i]
        Wsp_tmp <- Matrix(diag(re/pik),sparse = T)%*%Wsp_tmp
        Wsp_tmp <- Matrix(diag(1/pik),sparse = T)%*%Wsp_tmp
        Wsp_tmp <- cbind(rep(1,nrow),Wsp_tmp)
        
      }
      
      q <- base::qr(Wsp_tmp,LAPACK = FALSE)
      rang <- q$rank
      
      if(rang < ncol(Wsp_tmp)){
        
        set <- -seq_len(rang)
        u <- Matrix::qr.Q(q,complete = TRUE)[,set, drop = FALSE]
        u <- u[,ceiling(ncol(u)*0.6)]
        
        
      }else{
        
        
        # Wsp_tmp <- Wsp[i,i]
        # Wsp_tmp <- Matrix(diag(re[i]/pik[i]),sparse = T)%*%Wsp_tmp
        # Wsp_tmp <- Matrix(diag(1/re[i]),sparse = T)%*%Wsp_tmp
        
        
        u <- svd(t(Wsp_tmp))$u[,ncol(Wsp_tmp)]
        U <- rep(1,ncol(Wsp_tmp))
        u <- u - projOp(u,U)
        
      }
      
      #### REINITIALIZE TEMPORARY VALUE
      la1 = 1e+200
      la2 = 1e+200
      la = 1e-9
      
      
      # find lambda1 and lambda2
      for(k in 1:length(i)){
        if(u[k]>0){
          la1 = min(la1,(1-re[i[k]])/u[k]);
          la2 = min(la2,re[i[k]]/u[k]);
        }
        if(u[k]<0){
          la1 = min(la1,-re[i[k]]/u[k]);
          la2 = min(la2,(re[i[k]]-1)/u[k]);
        }
      }
      # random choice of p+lambda1*u and p-lambda2*u
      if(stats::runif(1) <la2/(la1+la2)){
        la = la1;
      }else{
        la = -la2;
      }
      # update prob
      for(k in 1:ncol(Wsp_tmp)){
        re[i[k]] = re[i[k]] + la * u[k];
        if(re[i[k]] < eps){ re[i[k]] = 0; }
        if(re[i[k]] > 1-eps){ re[i[k]] = 1; }
      }
      
      i <- which(re > eps & re < (1-eps))
    }
    
  }
  
  

 


  return(re)
}

